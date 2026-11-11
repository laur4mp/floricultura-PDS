#include "estilos.hpp"

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