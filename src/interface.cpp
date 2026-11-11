#include "interface.h"
#include "./ui_interface.h"
#include "Estilos.hpp"

#include <QIcon>
#include <QFontDatabase>
#include <QFont>
#include <QApplication>

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

Interface::Interface(QWidget *parent)
    : QMainWindow(parent),
    produtoRepositorio("data/produtos.txt"),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    std::vector<Produto> produtos = produtoRepositorio.carregar();

    for (const Produto& produto : produtos){
        sistema.adicionarProduto(produto);
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

    for (QLabel *label : {ui->tituloCard, ui->tituloProdutos, ui->tituloSobreNos, ui->tituloLogin, ui->tituloCadastro,
                          ui->tituloCarrinho, ui->precoProduto, ui->valorTotal, ui->tituloEntrega, ui->tituloPagamento,
                          ui->valorTotalFinal, ui->tituloFinal, ui->tituloHistorico}) {
        aplicarFonteTitulo(label);
    }

    for (QLabel *label : {ui->descricaoProdutos, ui->descricaoSobreNos, ui->descricaoLogin, ui->descricaoCriarConta,
                          ui->descricaoCadastro, ui->descricaoVoltarLogin, ui->labelSubtotal, ui->valorSubtotal, ui->descricaoEntrega,
                          ui->descricaoInicial, ui->descricaoPagamento, ui->labelSubtotalFinal, ui->valorSubtotalFinal,
                          ui->labelTotalFinal, ui->labelFrete, ui->valorFrete, ui->descricaoFinal}) {
        aplicarFonteDescricao(label);
    }

    for (QLabel *label : {ui->destaqueEmail, ui->destaqueSenha, ui->destaqueNome, ui->destaqueCPF, ui->destaqueAdicionarEmail,
                          ui->destaqueTelefone, ui->destaqueCriarSenha, ui->destaqueCarrinho, ui->nomeProduto, ui->labelTotal,
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

    aplicarEstiloCardCarrinho(ui->cardCarrinho);
    aplicarEstiloSeletor(ui->btnDiminuir, ui->labelQuantidade, ui->btnAumentar);

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
        ui->stackDivisao->setCurrentWidget(ui->paginaLoja);
        ui->mainContent->setCurrentWidget(ui->paginaPrincipal);
    });

    connect(ui->btnEntrar, &QPushButton::clicked, this, [this]() {
        ui->stackDivisao->setCurrentWidget(ui->paginaAdministrador);

    });

    connect(ui->btnPagPagamento, &QPushButton::clicked, this, [this]() {
        ui->mainContent->setCurrentWidget(ui->paginaPagamento);
        ui->stackPagamento->setCurrentWidget(ui->paginaResumoFinal);
    });

    connect(ui->btnFazerPedido, &QPushButton::clicked, this, [this]() {
        ui->stackPagamento->setCurrentWidget(ui->paginaFinal);
    });
}

Interface::~Interface()
{
    delete ui;
}