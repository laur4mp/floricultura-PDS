#ifndef CARDHISTORICO_H
#define CARDHISTORICO_H

#include <QWidget>

namespace Ui {
class CardHistorico;
}

class CardHistorico : public QWidget
{
    Q_OBJECT

public:
    explicit CardHistorico(QWidget *parent = nullptr);
    ~CardHistorico();

private:
    Ui::CardHistorico *ui;
};

#endif // CARDHISTORICO_H
