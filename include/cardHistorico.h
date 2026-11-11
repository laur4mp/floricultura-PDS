#ifndef CARDHISTORICO_H
#define CARDHISTORICO_H
#include "Venda.hpp"

#include <QWidget>

namespace Ui {
class CardHistorico;
}

class CardHistorico : public QWidget
{
    Q_OBJECT

public:
    explicit CardHistorico(const Venda& v, QWidget *parent = nullptr);
    ~CardHistorico();

signals:
    void avaliado(int idVenda, int nota);
    void cancelarCompra(int idVenda);

private:
    Ui::CardHistorico *ui;
};

#endif // CARDHISTORICO_H
