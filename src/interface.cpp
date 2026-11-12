#include "interface.h"
#include "./ui_interface.h"
#include "Estilos.hpp"
#include <QMessageBox>

#include <QIcon>
#include <QFontDatabase>
#include <QFont>
#include <QApplication>

#include <QDir> //manipula diretorios 
#include <QDate> //vai usar na data de validade 
#include <QLocale> // numero padrao br 
#include <QColor> // cor no status da table 
#include <QStringList> //  texto em listas
#include <QSignalBlocker> //sem sinal ao atualizar coisa nababela
#include <QTableWidgetItem> //mexer na tabela
#include <stdexcept> //exeções

//função para ler um número do qt, pega vigula ou . como decimal
static bool lerNumero(const QString& texto, double& valor){
    QString t = texto.trimmed();
    t.replace(',', '.');
    bool ok = false;
    valor = t.toDouble(&ok);
    return ok;
}


// formatação brasileira para a tela
static const QLocale& localeBR(){
    static const QLocale br(QLocale::Portuguese, QLocale::Brazil);
    return br;
}


QString Interface::textoStatus(StatusVenda s){ //so converte o enum pra ficar mais bonitin
    switch (s) {
    case StatusVenda::PROCESSAMENTO: return "Em Processamento";
    case StatusVenda::ENVIADO:       return "Enviado";
    case StatusVenda::ENTREGUE:      return "Entregue";
    case StatusVenda::CANCELADO:     return "Cancelado";
    }
    return "";
}

int Interface::idPedidoSelecionado() const { //retornar id do produto selecionado na tabela de pedidos
    const QList<QTableWidgetItem*> sel = ui->tablePedidos->selectedItems();

    if (sel.isEmpty())
        return 0;

    QTableWidgetItem* itemId =
        ui->tablePedidos->item(sel.first()->row(), 0);

    return itemId ? itemId->data(Qt::UserRole).toInt() : 0;
}

void Interface::atualizarTabelaPedidos(int idParaSelecionar){ //serve para atualizar a tabela de pedidos
    QTableWidget* t = ui->tablePedidos;

    {
        QSignalBlocker bloqueio(t);
        t->setSortingEnabled(false);
        t->clearContents();

        const std::vector<Venda>& vendas = sistema.getVendas();
        t->setRowCount(static_cast<int>(vendas.size()));

        for (int i = 0; i < static_cast<int>(vendas.size()); i++) {

            // Mais recente no topo
            const Venda& v =vendas[vendas.size() - 1 - static_cast<std::size_t>(i)];

            // idVenda
            auto* itemId = new QTableWidgetItem(QString::number(v.getIdVenda()));

            itemId->setData(Qt::UserRole, v.getIdVenda());
            itemId->setTextAlignment(Qt::AlignCenter);

            // cliente e destinatário
            Pessoa* cliente = sistema.buscarUsuario(v.getIdPessoa());

            QString textoCliente = cliente ? QString::fromStdString(cliente->getNome()) : QString("Cliente #%1").arg(v.getIdPessoa()); // se n achar o id exibe um padrão "Cliente #id"
            textoCliente += "\n" + QString::fromStdString(v.getEnderecoEntrega().getCidade() + " - " + v.getEnderecoEntrega().getBairro());

            // Itens
            QStringList itens;

            for (const ItemPedido& item : v.getItens()) {
                itens << QString::fromStdString(item.informarDados());
            }
            // Total e cupom
            QString textoTotal = localeBR().toString(v.getValorTotal(), 'f', 2);

            const Desconto& d = v.getDescontoAplicado();

            if (!d.getCupom().empty()) { //ve se venda tem cumpom associado
                textoTotal += QString("\n(cupom %1 - %2%)")
                    .arg(QString::fromStdString(d.getCupom()))
                    .arg(localeBR().toString(d.getPercentual(), 'g', 4));
            }

            auto* itemTotal = new QTableWidgetItem(textoTotal);
            itemTotal->setTextAlignment(Qt::AlignCenter);

            // Status e pagamento
            QString textoSt = textoStatus(v.getStatusVenda());

            if (v.getStatusVenda() != StatusVenda::CANCELADO) { // se venda n for cancelada, mostra o status do pagamento
                textoSt += (v.getStatusPagamento() == StatusPagamento::PAGO)
                    ? "\nPago"
                    : "\nAguardando pagamento";
            }

            auto* itemStatus = new QTableWidgetItem(textoSt);
            itemStatus->setTextAlignment(Qt::AlignCenter);

            //cor de acordo com o status da venda
            switch (v.getStatusVenda()) {
            case StatusVenda::PROCESSAMENTO:
                itemStatus->setBackground(QColor("#FFF4D6"));
                itemStatus->setForeground(QColor("#8A6100"));
                break;

            case StatusVenda::ENVIADO:
                itemStatus->setBackground(QColor("#E3EEF9"));
                itemStatus->setForeground(QColor("#2B5C8A"));
                break;

            case StatusVenda::ENTREGUE:
                itemStatus->setBackground(QColor("#E2EFE6"));
                itemStatus->setForeground(QColor("#24352C"));
                break;

            case StatusVenda::CANCELADO:
                itemStatus->setBackground(QColor("#F6E1E1"));
                itemStatus->setForeground(QColor("#9B5252"));
                break;
            }

            // Preenche a tabela
            t->setItem(i, 0, itemId);
            t->setItem(i, 1, new QTableWidgetItem(textoCliente));
            t->setItem(i, 2, new QTableWidgetItem(itens.join("\n")));
            t->setItem(i, 3, itemTotal);
            t->setItem(i, 4, itemStatus);
        }

        t->resizeRowsToContents(); //ajusta tudo automatico
    }
    
    // mantém selecionado o pedido anterior q o adm selecionou, se ainda existir depois de atualizar a tabela
    if (idParaSelecionar != 0) {
        for (int i = 0; i < t->rowCount(); i++) {
            if (t->item(i, 0)->data(Qt::UserRole).toInt()
                == idParaSelecionar) {

                t->selectRow(i);
                break;
            }
        }
    }
}
//adm controla o status pedido
void Interface::atualizarStatusPedido(){
    Gerente* g = gerenteLogado();

    if (g == nullptr) {
        QMessageBox::warning(this, "Pedidos", "Nenhum gerente cadastrado no sistema.");
        return;
    }
    const int idVenda = idPedidoSelecionado(); //ve pedido selecionado na tabela
    Venda* v = sistema.buscarVenda(idVenda);

    if (v == nullptr) { //sem venda ou sem pedido selecionado, sai
        QMessageBox::warning(this, "Pedidos", "Selecione um pedido na tabela.");
        return;
    }

    // A ordem do comboBox é a mesma do enum StatusVenda
    const StatusVenda novo = static_cast<StatusVenda>(ui->comboBoxStatus->currentIndex());
    //verificações a depender do novo estado
    if (novo == v->getStatusVenda()) {
        QMessageBox::information(this, "Pedidos",
                                 "O pedido já está com esse status.");
        return;
    }

    if (novo == StatusVenda::CANCELADO) {
        auto resp = QMessageBox::question(
            this,
            "Cancelar pedido",
            QString("Cancelar o pedido #%1? Os itens voltam para o estoque.")
                .arg(idVenda)
        );

        if (resp != QMessageBox::Yes)
            return;
    }

    try {
        g->atualizarStatusVenda(*v, novo);

        if (novo == StatusVenda::CANCELADO)
            sistema.devolverEstoque(*v); //volta pro estoque os itens do pedido cancelado

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Pedidos", e.what());

        ui->comboBoxStatus->setCurrentIndex(
            static_cast<int>(v->getStatusVenda())
        );

        return;
    }

    if (!salvarComAviso())
        return;

    atualizarTabelaPedidos(idVenda);

    QMessageBox::information(
        this,
        "Pedidos",
        QString("Pedido #%1 agora está: %2")
            .arg(idVenda)
            .arg(textoStatus(novo))
    );
}

Gerente* Interface::gerenteLogado() const {
    for (Pessoa* p : sistema.getUsuarios()) {
        if (auto* g = dynamic_cast<Gerente*>(p)) return g;
    }
    return nullptr;
}
//tabela de cupons
void Interface::atualizarTabelaCupons(){

    QTableWidget* t = ui->tableCupons;
    t->setSortingEnabled(false);
    t->clearContents();

    const std::vector<Desconto>& cupons = sistema.getCupons();
    t->setRowCount(static_cast<int>(cupons.size()));

    for (int i = 0; i < static_cast<int>(cupons.size()); i++) {
        const Desconto& d = cupons[i];

        QDate validade = QDate::fromString(
            QString::fromStdString(d.getDataValidade()),
            "yyyy-MM-dd"
        );

        QString texto = QString("%1% - válido até %2")
            .arg(localeBR().toString(d.getPercentual(), 'g', 4))
            .arg(validade.toString("dd/MM/yyyy"));

        auto* itemCodigo =
            new QTableWidgetItem(QString::fromStdString(d.getCupom()));

        auto* itemDesconto = new QTableWidgetItem(texto);

        itemCodigo->setTextAlignment(Qt::AlignCenter);
        itemDesconto->setTextAlignment(Qt::AlignCenter);

        if (!d.ehValido()) {
            itemDesconto->setText(texto + " (expirado)");

            itemCodigo->setForeground(QColor("#999999"));
            itemDesconto->setForeground(QColor("#999999"));
        }

        t->setItem(i, 0, itemCodigo);
        t->setItem(i, 1, itemDesconto);
    }
}

void Interface::criarCupom(){
    Gerente* g = gerenteLogado();
    if (g == nullptr) {
        QMessageBox::warning(this, "Cupons", "Nenhum gerente cadastrado no sistema.");
        return;
    }

    const std::string codigo = ui->boxCodigoCupom->text().trimmed().toUpper().toStdString();
    if (codigo.empty()) {
        QMessageBox::warning(this, "Cupons", "Informe o código do cupom.");
        return;
    }
    if (codigo.find_first_of(" |") != std::string::npos) {
        QMessageBox::warning(this, "Cupons", "O código do cupom não pode ter espaços nem '|'.");
        return;
    }

    double porcentagem = 0.0;
    if (!lerNumero(ui->boxPorcentagem->text(), porcentagem) || porcentagem <= 0.0 || porcentagem > 100.0) {
        QMessageBox::warning(this, "Cupons", "A porcentagem deve ser maior que 0 e no máximo 100.");
        return;
    }

    const std::string validade = ui->dataValidade->date().toString("yyyy-MM-dd").toStdString();

    try {
        Desconto cupom = g->cadastrarCupom(codigo, porcentagem, validade);
        sistema.adicionarCupom(cupom);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Cupons", e.what());
        return;
    }

    if (!salvarComAviso()) return;

    atualizarTabelaCupons();
    ui->boxCodigoCupom->clear();
    ui->boxPorcentagem->clear();
    ui->dataValidade->setDate(QDate::currentDate().addMonths(1));
    QMessageBox::information(this, "Cupons", "Cupom criado com sucesso!");
}

static void limparLayout(QLayout* layout) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* w = item->widget()) w->deleteLater();
        delete item;
    }
}

void Interface::configurarTabelaProdutos(){
    ui->tableProdutos->setWordWrap(true);

    ui->tableProdutos->setColumnWidth(0, 50);   // ID
    ui->tableProdutos->setColumnWidth(1, 150);  // Nome
    ui->tableProdutos->setColumnWidth(2, 200);  // Descrição
    ui->tableProdutos->setColumnWidth(3, 90);   // Preço
    ui->tableProdutos->setColumnWidth(4, 110);  // Categoria
    ui->tableProdutos->setColumnWidth(5, 60);   // Qnt

    //Com o for, o programa não estava rodando. Manter assim
    ui->tableProdutos->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    ui->tableProdutos->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
    ui->tableProdutos->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignCenter);
    ui->tableProdutos->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignCenter);
    ui->tableProdutos->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignCenter);
    ui->tableProdutos->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignCenter);
}

void Interface::configurarTabelaPedidos(){
    ui->tablePedidos->setWordWrap(true);

    ui->tablePedidos->setColumnWidth(0, 100);  // ID Pedido
    ui->tablePedidos->setColumnWidth(1, 280);  // Cliente
    ui->tablePedidos->setColumnWidth(2, 450);  // Itens
    ui->tablePedidos->setColumnWidth(3, 180);  // Total (R$)
    ui->tablePedidos->setColumnWidth(4, 382);  // Status

    //Com o for, o programa não estava rodando. Manter assim
    ui->tablePedidos->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    ui->tablePedidos->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
    ui->tablePedidos->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignCenter);
    ui->tablePedidos->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignCenter);
    ui->tablePedidos->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignCenter);
}

void Interface::configurarTabelaCupons(){
    ui->tableCupons->setWordWrap(true);

    ui->tableCupons->setColumnWidth(0, 685);  // Código
    ui->tableCupons->setColumnWidth(1, 685);  // Desconto

    ui->tableCupons->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    ui->tableCupons->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
}

Comprador* Interface::comprador() const {
    return dynamic_cast<Comprador*>(usuarioLogado);   // nullptr sem login ou se for o gerente
}

void Interface::carregarProdutos() {
    limparLayout(ui->gridProdutos->layout());
    cardsProdutos.clear();
    QGridLayout* grid = static_cast<QGridLayout*>(ui->gridProdutos->layout());

    int i = 0;
    for (const Produto& p : sistema.getProdutos()) {
        CardProduto* card = new CardProduto(p, ui->gridProdutos);
        if (comprador()) card->setFavorito(comprador()->ehFavorito(p.getIdProduto()));

        connect(card, &CardProduto::adicionarAoCarrinho, this, [this](int id) {
            Produto* prod = sistema.buscarProduto(id);
            if (!comprador() || !prod) return;
            try {
                comprador()->adicionarAoCarrinho(ItemPedido(*prod, 1));
                atualizarCarrinho();
            } catch (const std::exception& e) {
                QMessageBox::warning(this, "Carrinho", e.what());
            }
        });

        connect(card, &CardProduto::favoritoAlterado, this, [this](int id, bool favoritado) {
            Produto* prod = sistema.buscarProduto(id);
            if (!comprador() || !prod) return;
            if (favoritado) comprador()->favoritarProduto(*prod);
            else            comprador()->desfavoritarProduto(*prod);
            salvarComAviso();
        });

        grid->addWidget(card, i / 3, i % 3);   // 3 cards por linha
        cardsProdutos[p.getIdProduto()] = card;
        i++;
    }
}

void Interface::buscar() {
    for (auto& [id, card] : cardsProdutos) card->setDestaque(false);   // apaga a busca anterior

    std::string termo = ui->inputBusca->text().trimmed().toStdString();
    if (termo.empty() || !comprador()) return;

    std::vector<Produto> achados = comprador()->pesquisarProdutos(sistema.getProdutos(), termo);
    if (achados.empty()) {
        QMessageBox::information(this, "Busca", "Nenhum produto encontrado.");
        return;
    }

    for (const Produto& p : achados)
        cardsProdutos[p.getIdProduto()]->setDestaque(true);

    ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
    ui->scrollAreaPrincipal->ensureWidgetVisible(cardsProdutos[achados.front().getIdProduto()]);
}

void Interface::atualizarCarrinho() {
    QLayout* lista = ui->listaProdutos->layout();
    limparLayout(lista);

    double subtotal = 0.0;
    if (comprador()) {
        for (const ItemPedido& item : comprador()->consultarCarrinho()) {
            int id = item.getProduto().getIdProduto();
            int qtd = item.getQuantidade();
            cardCarrinho* card = new cardCarrinho(item, ui->listaProdutos);

            connect(card, &cardCarrinho::quantidadeAumentada, this, [this, id, qtd] {
                Produto* prod = sistema.buscarProduto(id);
                if (prod && qtd + 1 > prod->getQuantidadeEstoque()) {
                    QMessageBox::information(this, "Carrinho", "Quantidade maxima em estoque.");
                    return;
                }
                comprador()->alterarQuantidadeCarrinho(id, qtd + 1);
                atualizarCarrinho();
            });
            connect(card, &cardCarrinho::quantidadeDiminuida, this, [this, id, qtd] {
                comprador()->alterarQuantidadeCarrinho(id, qtd - 1);   // em 0, o item sai
                atualizarCarrinho();
            });
            lista->addWidget(card);
        }
        subtotal = comprador()->subtotalCarrinho();
    }
    ui->valorSubtotal->setText(localeBR().toCurrencyString(subtotal));
    ui->valorTotal->setText(localeBR().toCurrencyString(subtotal));
}

void Interface::irParaEntrega() {
    if (!comprador() || comprador()->consultarCarrinho().empty()) {
        QMessageBox::information(this, "Carrinho", "Seu carrinho esta vazio.");
        return;
    }
    ui->mainContent->setCurrentWidget(ui->paginaEntrega);
}

void Interface::irParaPagamento() {
    try {
        enderecoAtual = Endereco(
            ui->inputNomeDest->text().toStdString(), ui->inputCEP->text().toStdString(),
            ui->inputRua->text().toStdString(),      ui->inputNumero->text().toStdString(),
            ui->inputBairro->text().toStdString(),   ui->inputComplemento->text().toStdString(),
            ui->inputCidade->text().toStdString(),
            ui->inputEstado->text().trimmed().toUpper().toStdString());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Endereco", e.what());
        return;
    }

    double subtotal = comprador()->subtotalCarrinho();
    double frete = comprador()->consultarCarrinho().front().calcularFrete(enderecoAtual);

    ui->valorSubtotalFinal->setText(localeBR().toCurrencyString(subtotal));
    ui->valorFrete->setText(localeBR().toCurrencyString(frete));
    ui->valorTotalFinal->setText(localeBR().toCurrencyString(subtotal + frete));

    ui->mainContent->setCurrentWidget(ui->paginaPagamento);
    ui->stackPagamento->setCurrentWidget(ui->paginaResumoFinal);
}

void Interface::carregarDados() {

    sistema.adicionarUsuario(new Gerente(0, "Administrador", "00000000000",
                                         "admin@tell.com", "00000000000", "admin"));

    for(const Produto& p : produtoRepositorio.carregar()){
        sistema.adicionarProduto(p);
    }

    std::vector<PessoaRepositorio::Favorito> favs;
    for (const Pessoa& p : pessoaRepositorio.carregar(favs)) {
        Comprador* c = new Comprador(p.getIdPessoa(), p.getNome(), p.getCpf(),
                                     p.getEmail(), p.getTelefone(), p.getSenha());
        for (const Endereco& e : p.getEnderecos()) c->adicionarEndereco(e);
        sistema.adicionarUsuario(c);
    }

    for (const auto& f : favs) {
        Comprador* c = dynamic_cast<Comprador*>(sistema.buscarUsuario(f.first));
        Produto* prod = sistema.buscarProduto(f.second);
        if (c && prod) c->favoritarProduto(*prod);
    }

    for (const Venda& v : vendaRepositorio.carregar())
        sistema.adicionarVenda(v);
    for (const Desconto& d : descontoRepositorio.carregar())
        sistema.adicionarCupom(d);

   


}

void Interface::salvarTudo() {
    produtoRepositorio.gravar(sistema.getProdutos());

    std::vector<Pessoa> pessoas;
    std::vector<PessoaRepositorio::Favorito> favs;
    for (Pessoa* p : sistema.getUsuarios()) {
        if (auto* c = dynamic_cast<Comprador*>(p)) {
            pessoas.push_back(*c);
            for (const Produto& prod : c->getProdutosFavoritos())
                favs.push_back({ c->getIdPessoa(), prod.getIdProduto() });
        }
    }
    pessoaRepositorio.gravar(pessoas, favs);

    vendaRepositorio.gravar(sistema.getVendas());
    descontoRepositorio.gravar(sistema.getCupons());
}
//salvar tudo e erro se der erro
bool Interface::salvarComAviso(){
    try {
        salvarTudo();
        return true;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Erro ao salvar", e.what());
        return false;
    }
}

Gerente* Interface::gerenteLogado() const {

    return dynamic_cast<Gerente*>(usuarioLogado);
   
}

Interface::Interface(QWidget *parent)
    : QMainWindow(parent),
    produtoRepositorio("data/produtos.txt"),
    pessoaRepositorio("data/pessoas.txt"),
    vendaRepositorio("data/vendas.txt"),
    descontoRepositorio("data/cupons.txt"),
    ui(new Ui::Interface)
{



    ui->setupUi(this);
    QDir().mkpath("data"); //para garantir que a pasta exista, caso não exista, cria

    try{
        carregarDados();
    }catch (const std::exception& e){
        QMessageBox::warning(this, "Erro ao carregar dados", e.what());
    }
    carregarProdutos();

    configurarTabelaProdutos();
    configurarTabelaPedidos();
    configurarTabelaCupons();


    QFontDatabase::addApplicationFont(":/fonts/Montserrat-VariableFont_wght.ttf");
    QFont fonte("Montserrat");
    ui->paginaLoja->setFont(fonte);
    ui->paginaAcesso->setFont(fonte);

    for (QPushButton *btn : {ui->btnFazerCadastro, ui->btnSairAdm}) {
        aplicarEstiloBotaoTransparente(btn);
    }

    for (QPushButton *btn : {ui->btnProdutos, ui->btnSobreNos, ui->btnCarrinho, ui->btnMinhasCompras,
                             ui->btnContinuarComprando}) {
        aplicarFonteBotaoMenu(btn);
    }

    for (QPushButton *btn : {ui->btnFazerLogin, ui->btnChamada, ui->btnEntrar, ui->btnCriarConta, ui->btnPagPagamento,
                             ui->btnFazerPedido, ui->btnCupom, ui->btnBuscar}) {
        aplicarEstiloBotaoRosa(btn);
    }

    aplicarEstiloBotaoVerde(ui->btnFinalizar);

    for (QLabel *label : {ui->tituloCardInicial, ui->tituloProdutos, ui->tituloSobreNos, ui->tituloLogin, ui->tituloCadastro,
                          ui->tituloCarrinho, ui->tituloFinal, ui->tituloHistorico, ui->valorTotal, ui->valorTotalFinal,
                          ui->tituloPagamento, ui->tituloEntrega}) {
        aplicarFonteTitulo(label);
    }

    for (QLabel *label : {ui->descricaoProdutos, ui->descricaoSobreNos, ui->descricaoLogin, ui->descricaoCriarConta,
                          ui->descricaoCadastro, ui->descricaoVoltarLogin, ui->labelSubtotal, ui->valorSubtotal, ui->descricaoEntrega,
                          ui->descricaoInicial, ui->descricaoPagamento, ui->labelSubtotalFinal, ui->valorSubtotalFinal,
                          ui->labelTotalFinal, ui->labelFrete, ui->valorFrete, ui->descricaoFinal, ui->descricaoCardInicial}) {
        aplicarFonteDescricao(label);
    }

    for (QLabel *label : {ui->destaqueEmail, ui->destaqueSenha, ui->destaqueNome, ui->destaqueCPF, ui->destaqueAdicionarEmail,
                          ui->destaqueTelefone, ui->destaqueCriarSenha, ui->destaqueCarrinho, ui->labelTotal,
                          ui->labelResumo, ui->destaqueRua, ui->destaqueNumero, ui->destaqueNomeDest, ui->destaqueEstado,
                          ui->destaqueComplemento, ui->destaqueCidade, ui->destaqueCEP, ui->destaqueBairro, ui->labelResumoFinal,
                          ui->destaqueHistorico}) {
        aplicarFonteDestaque(label);
    }

    for (QPushButton *btn : {ui->btnPagCriarConta, ui->btnVoltarLogin}) {
        aplicarFonteBotaoConta(btn);
    }

    aplicarEstiloCard(ui->cardWidget);

    for (QLineEdit *input : {ui->inputEmail, ui->inputSenha, ui->inputNome, ui->inputCPF, ui->inputTelefone,
                             ui->inputAdicionarEmail, ui->inputCriarSenha, ui->inputRua, ui->inputNumero, ui->inputNomeDest,
                             ui->inputEstado, ui->inputComplemento, ui->inputCidade, ui->inputCEP, ui->inputBairro,
                             ui->inputCupom, ui->inputBusca}) {
        aplicarEstiloInput(input);
    }

    aplicarEstiloCardResumo(ui->resumoCompra);

    this->setMinimumSize(0, 0);
    ui->centralWidget->setMinimumSize(0, 0);

    ui->btnCarrinho->setIcon(QIcon(":/images/cart.svg"));
    ui->btnCarrinho->setIconSize(QSize(32, 32));

    QFont underline = ui->btnContinuarComprando->font();
    underline.setUnderline(true);
    ui->btnContinuarComprando->setFont(underline);

    connect(ui->btnVerCriarSenha, &QPushButton::toggled, this, [this](bool marcado) {
        ui->inputCriarSenha->setEchoMode(
            marcado ? QLineEdit::Normal : QLineEdit::Password);
        marcado ? ui->btnVerCriarSenha->setText("💤") : ui->btnVerCriarSenha->setText("👁");
    });

    connect(ui->btnVerSenha, &QPushButton::toggled, this, [this](bool marcado) {
        ui->inputSenha->setEchoMode(
            marcado ? QLineEdit::Normal : QLineEdit::Password);
        marcado ? ui->btnVerSenha->setText("💤") : ui->btnVerSenha->setText("👁");
    });

    connect(ui->btnFazerLogin, &QPushButton::clicked, this, [this]() {
        ui->stackAcesso->setCurrentWidget(ui->paginaEntrar);
    });

    connect(ui->btnVoltarLogin, &QPushButton::clicked, this, [this]() {
        ui->stackAcesso->setCurrentWidget(ui->paginaEntrar);
    });

    connect(ui->btnFazerCadastro, &QPushButton::clicked, this, [this]() {
        ui->stackAcesso->setCurrentWidget(ui->paginaCadastro);
    });

    connect(ui->btnPagCriarConta, &QPushButton::clicked, this, [this]() {
        ui->stackAcesso->setCurrentWidget(ui->paginaCadastro);
    });

    connect(ui->btnProdutos, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
        ui->scrollAreaPrincipal->ensureWidgetVisible(ui->secaoProdutos);
    });

    connect(ui->btnSobreNos, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
        ui->scrollAreaPrincipal->ensureWidgetVisible(ui->secaoSobreNos);
    });

    connect(ui->btnCarrinho, &QPushButton::clicked, this, [this]() {
        atualizarCarrinho();
        ui->mainContent->setCurrentWidget(ui->paginaCarrinho);
    });

    connect(ui->btnMinhasCompras, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaHistorico);
    });

    connect(ui->btnChamada, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
        ui->scrollAreaPrincipal->ensureWidgetVisible(ui->secaoProdutos);
    });

    connect(ui->btnContinuarComprando, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
        ui->scrollAreaPrincipal->ensureWidgetVisible(ui->secaoProdutos);
    });

    connect(ui->btnFinalizar, &QPushButton::clicked, this, [this]() {
        irParaEntrega();
    });

    connect(ui->btnCriarConta, &QPushButton::clicked, this, [this]() {

  connect(ui->btnEntrar, &QPushButton::clicked, this, [this]() {
        atualizarTabelaPedidos();
        atualizarTabelaCupons();
        ui->tabWidget->setCurrentWidget(ui->tabPedidos);
        ui->stackDivisao->setCurrentWidget(ui->paginaAdministrador);
    criarConta();

});

    connect(ui->btnEntrar, &QPushButton::clicked, this, [this]() { 
        
        fazerLogin();

    });

    connect(ui->btnPagPagamento, &QPushButton::clicked, this, [this]() {
        irParaPagamento();
    });

    connect(ui->btnFazerPedido, &QPushButton::clicked, this, [this]() {
        ui->stackPagamento->setCurrentWidget(ui->paginaFinal);
    });
    connect(ui->btnAtualizarStatus, &QPushButton::clicked, this, &Interface::atualizarStatusPedido);
    connect(ui->btnCriarCupom, &QPushButton::clicked, this, &Interface::criarCupom);

    // combo mostra o status do pedido selecionado
connect(ui->tablePedidos, &QTableWidget::itemSelectionChanged, this, [this]() {
    Venda* v = sistema.buscarVenda(idPedidoSelecionado());
    if (v) ui->comboBoxStatus->setCurrentIndex(static_cast<int>(v->getStatusVenda()));
});

// campo de validade do cupom
ui->dataValidade->setDisplayFormat("dd/MM/yyyy");
ui->dataValidade->setMinimumDate(QDate::currentDate());
ui->dataValidade->setDate(QDate::currentDate().addMonths(1));

    connect(ui->btnBuscar, &QPushButton::clicked, this, [this]() { buscar(); });
    connect(ui->inputBusca, &QLineEdit::returnPressed, this, [this]() { buscar(); });

}



void Interface::fazerLogin() {

    Pessoa* usuario = sistema.autenticar(ui->inputEmail->text().trimmed().toStdString(),
                                         ui->inputSenha->text().toStdString());
    if (usuario == nullptr) {

        QMessageBox::warning(this, "Login", "E-mail ou senha incorretos.");
        
        return;

    }

    ui->inputEmail->clear();

    ui->inputSenha->clear();


    usuarioLogado = usuario; 


    if (gerenteLogado() != nullptr) {

        ui->tabWidget->setCurrentWidget(ui->tabProdutos);
        
        ui->stackDivisao->setCurrentWidget(ui->paginaAdministrador);
    
    }

    else {

        carregarProdutos();     
        atualizarCarrinho();
        ui->inputBusca->clear();
        
        ui->stackDivisao->setCurrentWidget(ui->paginaLoja);
        
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
    
    }

}



void Interface::criarConta() {

    try {

        Comprador* novo = new Comprador(sistema.proximoIdUsusario(),
            ui->inputNome->text().trimmed().toStdString(),
            ui->inputCPF->text().trimmed().toStdString(),
            ui->inputAdicionarEmail->text().trimmed().toStdString(),
            ui->inputTelefone->text().trimmed().toStdString(),
            ui->inputCriarSenha->text().toStdString());

        sistema.adicionarUsuario(novo);   // e-mail repetido: o Sistema apaga o objeto e lança
        
        salvarTudo();
        
        usuarioLogado = novo;
        carregarProdutos();
        atualizarCarrinho();
        
        ui->stackDivisao->setCurrentWidget(ui->paginaLoja);
        
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
    
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Cadastro", e.what());
    
    }

}





Interface::~Interface()
{
    delete ui;
}

