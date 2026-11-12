#include "cardCarrinho.h"
#include "ui_cardCarrinho.h"
#include "Estilos.hpp"

#include <QLocale>
#include <QPixmap>

cardCarrinho::cardCarrinho(const ItemPedido& item, QWidget* parent) : QWidget(parent), ui(new Ui::cardCarrinho)
{
    ui->setupUi(this);
    aplicarEstiloCardCarrinho(this);

    aplicarFonteTitulo(ui->precoProdutoCarrinho);
    aplicarFonteDescricao(ui->descricaoProdutoCarrinho);
    aplicarFonteDestaque(ui->nomeProdutoCarrinho);
    aplicarEstiloSeletor(ui->btnDiminuirCarrinho, ui->labelQuantidadeCarrinho, ui->btnAumentarCarrinho);

    const Produto& produto = item.getProduto();

    ui->nomeProdutoCarrinho->setText(QString::fromStdString(produto.getNome()));
    ui->descricaoProdutoCarrinho->setText(QString::fromStdString(produto.getDescricao()));
    ui->precoProdutoCarrinho->setText(QLocale(QLocale::Portuguese, QLocale::Brazil).toCurrencyString(produto.getPreco()));
    ui->fotoProdutoCarrinho->setPixmap(QPixmap(QString::fromStdString(produto.getEnderecoImagem())).scaled(120, 120, Qt::KeepAspectRatio));
    ui->labelQuantidadeCarrinho->setText(QString::number(item.getQuantidade()));

    connect(ui->btnAumentarCarrinho, &QPushButton::clicked, this, [this]() {
        emit quantidadeAumentada();
    });

    connect(ui->btnDiminuirCarrinho, &QPushButton::clicked, this, [this]() {
        emit quantidadeDiminuida();
    });
}

cardCarrinho::~cardCarrinho()
{
    delete ui;
}
