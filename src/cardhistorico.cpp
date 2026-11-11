#include "cardhistorico.h"
#include "ui_cardhistorico.h"

CardHistorico::CardHistorico(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CardHistorico)
{
    ui->setupUi(this);
}

CardHistorico::~CardHistorico()
{
    delete ui;
}
