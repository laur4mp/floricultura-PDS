#ifndef CARDCARRINHO_H
#define CARDCARRINHO_H

#include <QWidget>

namespace Ui {
class cardCarrinho;
}

class cardCarrinho : public QWidget
{
    Q_OBJECT

public:
    explicit cardCarrinho(QWidget *parent = nullptr);
    ~cardCarrinho();

private:
    Ui::cardCarrinho *ui;
};

#endif // CARDCARRINHO_H
