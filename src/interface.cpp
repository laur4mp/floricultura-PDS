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

    aplicarEstiloBotaoTransparente(ui->btnFazerCadastro);

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

