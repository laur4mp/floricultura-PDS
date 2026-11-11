#include "cardHistorico.h"
#include "ui_cardHistorico.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>

CardHistorico::CardHistorico(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardHistorico)
{
    ui->setupUi(this);

    aplicarFonteDestaque(ui->nomeProdutoHistorico);
    aplicarFonteDescricao(ui->descricaoProdutoHistorico);
    aplicarFonteDescricao(ui->descricaoTotalProdutoHistorico);
    aplicarFonteDestaque(ui->totalProdutoHistorico);

    aplicarEstiloCard(this);

    int avaliacao = 0;

    QList<QPushButton*> estrelas = {
        ui->btnEstrela1, ui->btnEstrela2, ui->btnEstrela3,
        ui->btnEstrela4, ui->btnEstrela5
    };

    for (int i = 0; i < estrelas.size(); i++) {
        connect(estrelas[i], &QPushButton::clicked, this, [&, i]() {
            avaliacao = i + 1;

            for (int j = 0; j < estrelas.size(); j++) {
                estrelas[j]->setText(j < avaliacao ? "⭐" : "☆");
            }
        });
    }
}

CardHistorico::~CardHistorico()
{
    delete ui;
}
