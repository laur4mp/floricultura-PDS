#ifndef CARDCARRINHO_H
#define CARDCARRINHO_H

#include <QWidget>
#include "ItemPedido.hpp"

namespace Ui {
class cardCarrinho;
}

class cardCarrinho : public QWidget
{
    Q_OBJECT

public:
    explicit cardCarrinho(const ItemPedido& item, QWidget* parent = nullptr);
    ~cardCarrinho();

signals:
    void quantidadeAumentada();
    void quantidadeDiminuida();

private:
    Ui::cardCarrinho *ui;
};

#endif // CARDCARRINHO_H
