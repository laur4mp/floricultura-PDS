#include "Estilos.hpp"

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

void aplicarEstiloCard(QWidget *card){
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(R"(
        QWidget {
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

void aplicarEstiloCardCarrinho(QWidget *card){
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(R"(
        QWidget#cardCarrinho {
            background-color: #FFFFFF;
            border: 1px solid #D8C9CE;
            border-radius: 8px;
        }

        QWidget#cardCarrinho:hover {
            border: 1px solid #9B5252;
        }
    )");
}

void aplicarEstiloCardHistorico(QWidget *card){
    card->setAttribute(Qt::WA_StyledBackground, true);
    card->setStyleSheet(R"(
        QWidget#cardHistorico {
            background-color: #FFFFFF;
            border: 1px solid #D8C9CE;
            border-radius: 8px;
        }
    )");
}

void aplicarEstiloCardResumo(QWidget *card){
    card->setStyleSheet(R"(
        QWidget#resumoCompra {
            background-color: #FFFFFF;
            border: 1px solid #D8C9CE;
            border-radius: 8px;
        }
    )");
}

void aplicarEstiloBotaoQuantidade(QPushButton *btn){
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

void aplicarEstiloQuantidade(QLabel *label){
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

void aplicarEstiloSeletor(QPushButton *diminuir, QLabel *quantidade, QPushButton *aumentar){
    aplicarEstiloBotaoQuantidade(diminuir);
    aplicarEstiloQuantidade(quantidade);
    aplicarEstiloBotaoQuantidade(aumentar);
}

void aplicarEstiloStatusProduto(QLabel *label, StatusVenda status){
    QString fundo, texto;
    switch (status) {
    case StatusVenda::PROCESSAMENTO: fundo = "#FFF4D6"; texto = "#8A6100"; break;
    case StatusVenda::ENVIADO:       fundo = "#E3EEF9"; texto = "#2B5C8A"; break;
    case StatusVenda::ENTREGUE:      fundo = "#E2EFE6"; texto = "#24352C"; break;
    case StatusVenda::CANCELADO:     fundo = "#F6E1E1"; texto = "#9B5252"; break;
    }
    QFont fonte("Montserrat");
    fonte.setPointSize(10);
    fonte.setWeight(QFont::DemiBold);
    label->setFont(fonte);
    label->setStyleSheet(QString("QLabel { background-color: %1; color: %2; border-radius: 10px; padding: 4px 12px; }").arg(fundo, texto));
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
}