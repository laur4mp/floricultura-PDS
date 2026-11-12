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

#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QPixmap>

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

void Interface::carregarProdutos(){
    for(const Produto& produto : sistema.getProdutos()){

    }
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
        ui->mainContent->setCurrentWidget(ui->paginaEntrega);
    });

    connect(ui->btnCriarConta, &QPushButton::clicked, this, [this]() {

    criarConta();

});

    connect(ui->btnEntrar, &QPushButton::clicked, this, [this]() { 
        
        fazerLogin();

    });

    connect(ui->btnPagPagamento, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPagamento);
        ui->stackPagamento->setCurrentWidget(ui->paginaResumoFinal);
    });

    connect(ui->btnFazerPedido, &QPushButton::clicked, this, [this]() {
        ui->stackPagamento->setCurrentWidget(ui->paginaFinal);
    });

    connect(ui->tableProdutos, &QTableWidget::cellClicked, this, [this](int linha, int) { 
        preencherFormularioProduto(linha); 
    });

    connect(ui->btnNovo, &QPushButton::clicked, this, [this]() { 
        limparFormularioProduto(); 
    });

    connect(ui->btnSalvar, &QPushButton::clicked, this, [this]() { 
        salvarProduto(); 
    });

    connect(ui->btnImagemProduto, &QPushButton::clicked, this, [this]() { 
        escolherImagemProduto(); 
    });

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

        atualizarTabelaProdutos();
        
        limparFormularioProduto();

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

void Interface::atualizarTabelaProdutos() { 

    const std::vector<Produto>& produtos = sistema.getProdutos();

    ui->tableProdutos->setRowCount(static_cast<int>(produtos.size()));

    for (int i = 0; i < static_cast<int>(produtos.size()); i++) {

        const Produto& p = produtos[i];

        QStringList colunas = {
            QString::number(p.getIdProduto()),
            QString::fromStdString(p.getNome()),
            QString::fromStdString(p.getDescricao()),
            QString::number(p.getPreco(), 'f', 2),
            QString::fromStdString(p.getCategoria()),
            QString::number(p.getQuantidadeEstoque())
        };

        for (int c = 0; c < colunas.size(); c++) {

            QTableWidgetItem* item = new QTableWidgetItem(colunas[c]);

            if (p.verificarEstoqueMinimo()){

                item->setForeground(Qt::red);   // alerta de estoque baixo
            
            } 
            ui->tableProdutos->setItem(i, c, item);

        }
    }
}


void Interface::preencherFormularioProduto(int linha) {

    int id = ui->tableProdutos->item(linha, 0)->text().toInt();

    const Produto* p = sistema.buscarProduto(id);

    if (p == nullptr) return;

    idProdutoSelecionado = id;
    imagemEscolhida.clear();
    ui->boxNomeDoProduto->setText(QString::fromStdString(p->getNome()));
    ui->boxDescricaoProduto->setText(QString::fromStdString(p->getDescricao()));
    ui->boxPrecoProduto->setText(QString::number(p->getPreco(), 'f', 2));
    ui->boxCategoriaProduto->setText(QString::fromStdString(p->getCategoria()));
    ui->spinBoxEstoqueMinimo->setValue(p->getQuantidadeMinima());
    ui->spinBoxEstoque->setValue(p->getQuantidadeEstoque());
    ui->labelImagemProduto->setPixmap(
        QPixmap(QString::fromStdString(p->getEnderecoImagem())).scaled(120, 120, Qt::KeepAspectRatio));
}


void Interface::limparFormularioProduto() {
    idProdutoSelecionado = 0;
    imagemEscolhida.clear();
    ui->tableProdutos->clearSelection();
    ui->boxNomeDoProduto->clear();
    ui->boxDescricaoProduto->clear();
    ui->boxPrecoProduto->clear();
    ui->boxCategoriaProduto->clear();
    ui->spinBoxEstoqueMinimo->setValue(0);
    ui->spinBoxEstoque->setValue(0);
    ui->labelImagemProduto->clear();
}


void Interface::escolherImagemProduto() {

    QString arquivo = QFileDialog::getOpenFileName(this, "Escolher imagem do produto",
                                                   QString(), "Imagens (*.png *.jpg *.jpeg)");
    if (arquivo.isEmpty()){

        return;

    }
    imagemEscolhida = arquivo;

    ui->labelImagemProduto->setPixmap(QPixmap(arquivo).scaled(120, 120, Qt::KeepAspectRatio));
}


void Interface::salvarProduto() {

    if (gerenteLogado() == nullptr){

        return;

    }

    QString textoPreco = ui->boxPrecoProduto->text().trimmed();
    textoPreco.replace(',', '.');
    bool precoOk = false;
    double preco = textoPreco.toDouble(&precoOk);

    if (!precoOk) {

        QMessageBox::warning(this, "Produto", "Preço inválido.");
        return;

    }


    std::string nome = ui->boxNomeDoProduto->text().trimmed().toStdString();
    std::string descricao = ui->boxDescricaoProduto->text().trimmed().toStdString();
    std::string categoria = ui->boxCategoriaProduto->text().trimmed().toStdString();
    int estoque = ui->spinBoxEstoque->value();
    int minimo = ui->spinBoxEstoqueMinimo->value();

    try {

        bool novo = (idProdutoSelecionado == 0);
        int id = novo ? sistema.proximoIdProduto() : idProdutoSelecionado;

        if (novo) {
            sistema.adicionarProduto(gerenteLogado()->cadastrarProduto(
                id, nome, descricao, categoria, preco, "", estoque, minimo));
        
            } else {
            Produto* p = sistema.buscarProduto(id);
            gerenteLogado()->editarProduto(*p, nome, descricao, preco, categoria);
            gerenteLogado()->definirEstoqueMinimoProduto(*p, minimo);
            gerenteLogado()->ajustarEstoqueProduto(*p, estoque);
        
        }

        if (!imagemEscolhida.isEmpty()) {

            QDir().mkpath("data/imagens");
            QString destino = QString("data/imagens/produto_%1.%2")
                                  .arg(id).arg(QFileInfo(imagemEscolhida).suffix().toLower());
            if (QFileInfo(imagemEscolhida) != QFileInfo(destino)) {
                QFile::remove(destino);
                if (!QFile::copy(imagemEscolhida, destino))
                    throw std::runtime_error("Nao foi possivel copiar a imagem.");
            
                }
            sistema.buscarProduto(id)->setEnderecoImagem(destino.toStdString());
        }

        salvarTudo();

        atualizarTabelaProdutos();

        limparFormularioProduto();

    } catch (const std::exception& e) {

        QMessageBox::warning(this, "Produto", e.what());

    }

}





Interface::~Interface()
{
    delete ui;
}

