#include "cardProduto.h"
#include "ui_cardProduto.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>

CardProduto::CardProduto(const Produto& p, QWidget* parent) : QWidget(parent), ui(new Ui::CardProduto)
{
    ui->setupUi(this);

    aplicarFonteTitulo(ui->precoProduto);
    aplicarFonteDescricao(ui->descricaoProduto);
    aplicarFonteDestaque(ui->nomeProduto);
    aplicarEstiloBotaoTransparente(ui->btnFavoritar);
    aplicarEstiloBotaoVerde(ui->btnAdicionar);

    aplicarEstiloCard(this);

    ui->nomeProduto->setText(QString::fromStdString(p.getNome()));
    ui->descricaoProduto->setText(QString::fromStdString(p.getDescricao()));
    ui->precoProduto->setText(QLocale(QLocale::Portuguese, QLocale::Brazil).toCurrencyString(p.getPreco()));
    ui->fotoProduto->setPixmap(QPixmap(QString::fromStdString(p.getEnderecoImagem())).scaled(280, 280, Qt::KeepAspectRatio));

    if(p.getQuantidadeEstoque() <=0){
        ui->btnAdicionar->setEnabled(false);
        ui->btnAdicionar->setText("Esgotado");
    }

    int id = p.getIdProduto();

    connect(ui->btnAdicionar, &QPushButton::clicked, this, [this, id]{
        emit adicionarAoCarrinho(id);
    });

    connect(ui->btnFavoritar, &QPushButton::toggled, this, [this](bool marcado) {
            marcado ? ui->btnFavoritar->setText("❤") : ui->btnFavoritar->setText("♡");
    });
}

CardProduto::~CardProduto()
{
    delete ui;
}
