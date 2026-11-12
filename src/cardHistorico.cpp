#include "cardHistorico.h"
#include "ui_cardHistorico.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>
#include <QStringList>

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

    aplicarEstiloCardHistorico(this);

        ui->nomeProdutoHistorico->setText(QString("Pedido #%1").arg(v.getIdVenda()));

    QStringList itens;
    for (const ItemPedido& item : v.getItens())
        itens << QString::fromStdString(item.informarDados());
    if (!v.getDataEntrega().empty())
        itens << "Previsão de entrega: " + QString::fromStdString(v.getDataEntrega());
    ui->descricaoProdutoHistorico->setText(itens.join("\n"));

    ui->totalProdutoHistorico->setText(
        QLocale(QLocale::Portuguese, QLocale::Brazil).toCurrencyString(v.getValorTotal()));

    if (!v.getItens().empty())
        ui->fotoProdutoHistorico->setPixmap(
            QPixmap(QString::fromStdString(v.getItens().front().getProduto().getEnderecoImagem()))
                .scaled(120, 120, Qt::KeepAspectRatio));

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

        aplicarEstiloBotaoTransparente(estrelas[i]);
        estrelas[i]->setCursor(podeAvaliar ? Qt::PointingHandCursor : Qt::ArrowCursor);
        estrelas[i]->setToolTip(podeAvaliar ? QString("Dar nota %1").arg(i + 1)
                                            : "Disponível depois da entrega");

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
