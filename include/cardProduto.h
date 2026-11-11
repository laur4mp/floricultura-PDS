#ifndef CARDPRODUTO_H
#define CARDPRODUTO_H

#include <QWidget>
#include "Produto.hpp"

namespace Ui {
class CardProduto;
}

class CardProduto : public QWidget
{
    Q_OBJECT

public:
    explicit CardProduto(const Produto& p, QWidget* parent = nullptr);
    ~CardProduto();

signals:
    void adicionarAoCarrinho(int idProduto);

private:
    Ui::CardProduto *ui;
};

#endif // CARDPRODUTO_H
