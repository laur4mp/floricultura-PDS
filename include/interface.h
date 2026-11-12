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
#include <map>
#include "cardProduto.h"
#include "cardCarrinho.h"
#include "cardHistorico.h"

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

    QString imagemEscolhida;       // imagem escolhida e ainda não salva

    Pessoa* usuarioLogado = nullptr;
    int idProdutoSelecionado = 0;

    void carregarProdutos();
    void configurarTabelaProdutos();
    void configurarTabelaPedidos();
    void configurarTabelaCupons();
    void carregarDados();
    void salvarTudo();
    bool salvarComAviso();


    QWidget* criarCardProduto(const Produto& p);

    void fazerLogin();
    

    Gerente* gerenteLogado() const;


    void atualizarTabelaProdutos();
    void preencherFormularioProduto(int idProduto);
    void limparFormularioProduto();
    void salvarProduto();

    void atualizarTabelaPedidos(int idParaSelecionar = 0);
    int idPedidoSelecionado() const;
    void atualizarTabelaCupons();
    void atualizarStatusPedido();
    void criarCupom();


    //void fazerLogin(); //ja tem
    void criarConta();
    //void sair(); //ja tem
    // void atualizarTabelaProdutos();
    // void preencherFormularioProduto(int linha);
    // void limparFormularioProduto();
    // void salvarProduto();
    void escolherImagemProduto();


    static QString textoStatus(StatusVenda s); //função que pertence a classe

    // ---- loja ----
    std::map<int, CardProduto*> cardsProdutos;
    Endereco enderecoAtual;
    Comprador* comprador() const; 
    void buscar();
    void limparDestaques();
    void atualizarCarrinho();
    void irParaEntrega();
    void irParaPagamento();
};

#endif // INTERFACE_H
