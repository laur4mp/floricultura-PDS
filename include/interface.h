#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "Sistema.hpp"
#include "ProdutoRepositorio.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Interface;
}
QT_END_NAMESPACE

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface() override;

private:
    Ui::Interface *ui;
    Sistema sistema;
    ProdutoRepositorio produtoRepositorio;

    void carregarProdutos();
    void configurarTabelaProdutos();
    void configurarTabelaPedidos();
    void configurarTabelaCupons();
};

#endif // INTERFACE_H