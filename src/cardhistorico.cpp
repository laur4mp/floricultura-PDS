#include "cardHistorico.h"
#include "ui_cardHistorico.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>

CardHistorico::CardHistorico(const Venda& v, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardHistorico)
{
    ui->setupUi(this);

    aplicarFonteDestaque(ui->nomeProdutoHistorico);
    aplicarFonteDescricao(ui->descricaoProdutoHistorico);
    aplicarFonteDescricao(ui->descricaoTotalProdutoHistorico);
    aplicarFonteDestaque(ui->totalProdutoHistorico);
    aplicarEstiloBotaoTransparente(ui->btnCancelar);

    aplicarEstiloCard(this);

    switch (v.getStatusVenda()) {
    case StatusVenda::PROCESSAMENTO:
        ui->statusProdutoHistorico->setText("Em preparação");
        break;

    case StatusVenda::ENVIADO:
        ui->statusProdutoHistorico->setText("Em trânsito");
        break;

    case StatusVenda::ENTREGUE:
        ui->statusProdutoHistorico->setText("Entregue");
        break;

    case StatusVenda::CANCELADO:
        ui->statusProdutoHistorico->setText("Cancelado");
        break;
    }

    aplicarEstiloStatusProduto(ui->statusProdutoHistorico, v.getStatusVenda());

    QList<QPushButton*> estrelas = {
        ui->btnEstrela1, ui->btnEstrela2, ui->btnEstrela3,
        ui->btnEstrela4, ui->btnEstrela5
    };

    auto mudar = [estrelas](int nota) {
        for (int j = 0; j < estrelas.size(); j++)
            estrelas[j]->setText(j < nota ? "★" : "☆");
    };
    mudar(v.getAvaliacao());

    bool podeAvaliar = (v.getStatusVenda() == StatusVenda::ENTREGUE);
    int idVenda = v.getIdVenda();

    for (int i = 0; i < estrelas.size(); i++) {
        estrelas[i]->setEnabled(podeAvaliar);
        connect(estrelas[i], &QPushButton::clicked, this, [this, mudar, idVenda, i] {
            mudar(i + 1);
            emit avaliado(idVenda, i + 1);
        });
    }

    ui->btnCancelar->setVisible(v.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    connect(ui->btnCancelar, &QPushButton::clicked, this, [this, idVenda] { emit cancelarCompra(idVenda); });
}

CardHistorico::~CardHistorico()
{
    delete ui;
}
