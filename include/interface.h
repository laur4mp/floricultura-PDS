#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QWidget>
#include <vector>

#include "Sistema.hpp"
#include "ProdutoRepositorio.hpp"
#include "PessoaRepositorio.hpp"
#include "VendaRepositorio.hpp"
#include "DescontoRepositorio.hpp"
#include "Comprador.hpp"
#include "Gerente.hpp"

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
    PessoaRepositorio pessoaRepositorio;       
    VendaRepositorio vendaRepositorio;         
    DescontoRepositorio descontoRepositorio;

    void carregarProdutos();
    void configurarTabelaProdutos();
    void configurarTabelaPedidos();
    void configurarTabelaCupons();
    void carregarDados();
    void salvarTudo();

    QWidget* criarCardProduto(const Produto& p);
};

#endif // INTERFACE_H