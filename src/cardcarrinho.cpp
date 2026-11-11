#include "cardcarrinho.h"
#include "ui_cardcarrinho.h"

cardCarrinho::cardCarrinho(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::cardCarrinho)
{
    ui->setupUi(this);
}

cardCarrinho::~cardCarrinho()
{
    delete ui;
}
