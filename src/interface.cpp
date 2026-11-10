#include "interface.h"
#include "./ui_interface.h"
#include <QIcon>
#include <QFontDatabase>
#include <QFont>
#include <QApplication>

void aplicarFonteTitulo(QLabel *label){
    QFont fonte("Montserrat");
    fonte.setPointSize(24);
    fonte.setWeight(QFont::Bold);

    label->setFont(fonte);
}

void aplicarFonteDescricao(QLabel *label){
    QFont fonte("Montserrat");
    fonte.setPointSize(13);
    fonte.setWeight(QFont::Medium);

    label->setFont(fonte);
}

void aplicarFonteDestaque(QLabel *label){
    QFont fonte("Montserrat");
    fonte.setPointSize(12);
    fonte.setWeight(QFont::DemiBold);

    label->setFont(fonte);
}

void aplicarFonteBotaoMenu(QPushButton *btn){
    QFont fonte("Montserrat");
    fonte.setPointSize(12);
    fonte.setWeight(QFont::Medium);

    btn->setFont(fonte);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            color: #24352C;
            border: none;
            padding: 10px 16px;
        }

        QPushButton:hover {
            color: #9B5252;
        }
    )");
}

void aplicarFonteBotaoConta(QPushButton *btn){
    QFont fonte("Montserrat");
    fonte.setPointSize(12);
    fonte.setWeight(QFont::DemiBold);

    btn->setFont(fonte);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            color: #9B5252;
            border: none;
            padding: 10px 16px;
        }

        QPushButton:hover {
            color: #813F3F;
        }
    )");
}

void aplicarEstiloBotaoRosa(QPushButton *btn){
    QFont fonte("Montserrat");
    fonte.setPointSize(12);
    fonte.setWeight(QFont::DemiBold);
    btn->setFont(fonte);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: #9B5252;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 12px 20px;
        }

        QPushButton:hover {
            background-color: #813F3F;
        }
    )");

    btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    btn->adjustSize();
}

void aplicarEstiloBotaoTransparente(QPushButton *btn){
    QFont fonte("Montserrat");
    fonte.setPointSize(12);
    fonte.setWeight(QFont::DemiBold);
    btn->setFont(fonte);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            color: #9B5252;
            border: 1px solid #9B5252;
            border-radius: 8px;
            padding: 12px 20px;
        }

        QPushButton:hover {
            background-color: #9B5252;
            color: #FFE7F0;
        }
    )");

    btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    btn->adjustSize();
}

void aplicarEstiloBotaoVerde(QPushButton *btn){
    QFont fonte("Montserrat");
    fonte.setPointSize(11);
    fonte.setWeight(QFont::Bold);
    btn->setFont(fonte);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: #24352C;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px;
        }

        QPushButton:hover {
            background-color: #3B5948;
        }
    )");
}

void aplicarEstiloCard(QFrame *card) {
    card->setStyleSheet(R"(
        #cardWidget {
            background-color: #FFE7F0;
            border-radius: 8px;
        }
    )");
}

void aplicarEstiloInput(QLineEdit *input){
    QFont fonte("Montserrat");
    fonte.setPointSize(11);
    fonte.setWeight(QFont::Normal);
    input->setFont(fonte);

    input->setStyleSheet(R"(
        QLineEdit {
            background-color: #FFFFFF;
            color: #9B5252;
            border: 1px solid #9B5252;
            border-radius: 6px;
            padding: 8px;
        }

        QLineEdit:hover {
            border: 1px solid #813F3F;
            background-color: #FFF8FA;
        }

        QLineEdit:focus {
            border: 2px solid #9B5252;
            background-color: #FFFFFF;
        }
    )");
}

void aplicarEstiloCardCarrinho(QFrame *card) {
    card->setStyleSheet(R"(
        QFrame#cardCarrinho {
            background-color: #FFFFFF;
            border: 1px solid #D8C9CE;
            border-radius: 8px;
        }

        QFrame#cardCarrinho:hover {
            border: 1px solid #9B5252;
        }
    )");
}

void aplicarEstiloCardResumo(QWidget *card) {
    card->setStyleSheet(R"(
        QWidget#resumoCompra {
            background-color: #FFFFFF;
            border: 1px solid #D8C9CE;
            border-radius: 8px;
        }
    )");
}

void aplicarEstiloBotaoQuantidade(QPushButton *btn) {
    QFont fonte("Montserrat");
    fonte.setPointSize(14);
    fonte.setWeight(QFont::Medium);

    btn->setFont(fonte);
    btn->setFixedSize(32, 32);

    btn->setStyleSheet(R"(
        QPushButton {
            background-color: #FFFFFF;
            color: #24352C;
            border: 1px solid #D8C9CE;
            border-radius: 4px;
        }

        QPushButton:hover {
            background-color: #FFE7F0;
            border-color: #9B5252;
        }
    )");
}

void aplicarEstiloQuantidade(QLabel *label) {
    QFont fonte("Montserrat");
    fonte.setPointSize(11);
    fonte.setWeight(QFont::DemiBold);

    label->setFont(fonte);
    label->setAlignment(Qt::AlignCenter);
    label->setFixedSize(35, 32);
    label->setStyleSheet(R"(
        QLabel {
            background-color: #FFFFFF;
            color: #24352C;
            border: 1px solid #D8C9CE;
            border-radius: 4px;
        }
    )");
}

void aplicarEstiloSeletor(QPushButton *diminuir, QLabel *quantidade, QPushButton *aumentar) {
    aplicarEstiloBotaoQuantidade(diminuir);
    aplicarEstiloQuantidade(quantidade);
    aplicarEstiloBotaoQuantidade(aumentar);
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

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);

    configurarTabelaProdutos();
    configurarTabelaPedidos();
    configurarTabelaCupons();

    aplicarEstiloBotaoTransparente(ui->btnFazerCadastro);

    QFontDatabase::addApplicationFont(":/fonts/Montserrat-VariableFont_wght.ttf");
    QFont fonte("Montserrat");
    ui->paginaLoja->setFont(fonte);
    ui->paginaAcesso->setFont(fonte);

    for (QPushButton *btn : {ui->btnProdutos, ui->btnSobreNos, ui->btnCarrinho, ui->btnContinuarComprando}) {
        aplicarFonteBotaoMenu(btn);
    }

    for (QPushButton *btn : {ui->btnFazerLogin, ui->btnChamada, ui->btnEntrar, ui->btnCriarConta, ui->btnPagPagamento,
                             ui->btnFazerPedido, ui->btnCupom}) {
        aplicarEstiloBotaoRosa(btn);
    }

    for (QPushButton *btn : {ui->btnAdicionar1, ui->btnAdicionar2, ui->btnAdicionar3, ui->btnFinalizar}) {
        aplicarEstiloBotaoVerde(btn);
    }

    for (QLabel *label : {ui->tituloCard, ui->tituloProdutos, ui->tituloSobreNos, ui->tituloLogin, ui->tituloCadastro,
                          ui->tituloCarrinho, ui->precoProduto, ui->valorTotal, ui->tituloEntrega, ui->tituloPagamento,
                          ui->valorTotalFinal, ui->tituloFinal}) {
        aplicarFonteTitulo(label);
    }

    for (QLabel *label : {ui->descricaoProdutos, ui->descricaoProduto1, ui->descricaoProduto2, ui->descricaoProduto3,
                          ui->descricaoSobreNos, ui->descricaoLogin, ui->descricaoCriarConta, ui->descricaoCadastro,
                          ui->descricaoVoltarLogin, ui->labelSubtotal, ui->valorSubtotal, ui->descricaoEntrega,
                          ui->descricaoInicial, ui->descricaoPagamento, ui->labelSubtotalFinal, ui->valorSubtotalFinal,
                          ui->labelTotalFinal, ui->labelFrete, ui->valorFrete, ui->descricaoFinal}) {
        aplicarFonteDescricao(label);
    }

    for (QLabel *label : {ui->destaqueProduto1, ui->destaqueProduto2, ui->destaqueProduto3, ui->destaqueEmail,
                          ui->destaqueSenha, ui->destaqueNome, ui->destaqueCPF, ui->destaqueAdicionarEmail,
                          ui->destaqueTelefone, ui->destaqueCriarSenha, ui->destaqueCarrinho, ui->nomeProduto, ui->labelTotal,
                          ui->labelResumo, ui->destaqueRua, ui->destaqueNumero, ui->destaqueNomeDest, ui->destaqueEstado,
                          ui->destaqueComplemento, ui->destaqueCidade, ui->destaqueCEP, ui->destaqueBairro, ui->labelResumoFinal}) {
        aplicarFonteDestaque(label);
    }

    for (QPushButton *btn : {ui->btnPagCriarConta, ui->btnVoltarLogin}) {
        aplicarFonteBotaoConta(btn);
    }

    aplicarEstiloCard(ui->cardWidget);

    for (QLineEdit *input : {ui->inputEmail, ui->inputSenha, ui->inputNome, ui->inputCPF, ui->inputTelefone,
                             ui->inputAdicionarEmail, ui->inputCriarSenha, ui->inputRua, ui->inputNumero, ui->inputNomeDest,
                             ui->inputEstado, ui->inputComplemento, ui->inputCidade, ui->inputCEP, ui->inputBairro,
                             ui->inputCupom}) {
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