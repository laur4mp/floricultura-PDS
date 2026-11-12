#include "cardProduto.h"
#include "ui_cardProduto.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QSignalBlocker>
#include <QColor>

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

    connect(ui->btnFavoritar, &QPushButton::toggled, this, [this, id](bool marcado) {
    ui->btnFavoritar->setText(marcado ? "❤" : "♡");
    emit favoritoAlterado(id, marcado);
    });

}

CardProduto::~CardProduto()
{
    delete ui;
}

void CardProduto::setFavorito(bool favoritado) {
    QSignalBlocker bloqueio(ui->btnFavoritar);   
    ui->btnFavoritar->setChecked(favoritado);
    ui->btnFavoritar->setText(favoritado ? "❤" : "♡");
}

void CardProduto::setDestaque(bool destacado) {
    if (destacado) {
        auto* brilho = new QGraphicsDropShadowEffect(this);
        brilho->setColor(QColor("#D62828"));   
        brilho->setBlurRadius(30);
        brilho->setOffset(0, 0);
        setGraphicsEffect(brilho);
    } else {
        setGraphicsEffect(nullptr);            
    }
}