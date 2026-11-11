/**
 * @file Sistema.hpp
 * @brief Guarda os dados do sistema (usuarios, produtos e cupons) e faz o login.
 */
#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Desconto.hpp"
#include "Venda.hpp"
#include "Endereco.hpp"
#include "Comprador.hpp"


/**
 * @class Sistema
 * @brief Central de dados da floricultura.
 *
 * Os usuarios sao guardados como ponteiros (Pessoa*) para preservar o tipo
 * real de cada um (Gerente ou Comprador). O Sistema eh o dono desses objetos
 * e os apaga no destrutor.
 */
class Sistema {
private:
    std::vector<Pessoa*> _usuarios; 
    std::vector<Produto> _produtos;
    std::vector<Desconto> _cupons;
    std::vector<Venda> _vendas;

public:
    Sistema();
    ~Sistema();

    /** Um sistema nao pode ser copiado - shallow copy. */
    Sistema(const Sistema&) = delete;
    Sistema& operator=(const Sistema&) = delete;

    // --- usuarios e login ---

    /** @brief Cadastra um usuario; o Sistema passa a ser o dono do objeto.
     *  @throw std::invalid_argument se for nulo ou se o e-mail ja existir. */
    void adicionarUsuario(Pessoa* usuario);

    /** @brief Confere e-mail e senha. @return o usuario, ou nullptr se nao conferir. */
    Pessoa* autenticar(const std::string& email, const std::string& senha) const;

    // --- produtos ---

    /** @throw std::invalid_argument se ja existir produto com o mesmo id. */
    void adicionarProduto(const Produto& produto);

    /** @return o produto com esse id, ou nullptr. (Use na hora; nao guarde o ponteiro.) */
    Produto* buscarProduto(int idProduto);

    const std::vector<Produto>& getProdutos() const;

    // --- cupons ---

    /** @throw std::invalid_argument se o codigo for vazio ou ja existir. */
    void adicionarCupom(const Desconto& cupom);

    /** @return o cupom com esse codigo, ou nullptr. */
    const Desconto* buscarCupom(const std::string& codigo) const;

    const std::vector<Desconto>& getCupons() const;

    std::vector<Venda>& getVendas();
    const std::vector<Venda>& getVendas() const;
    Venda* buscarVenda(int idVenda);
    void adicionarVenda(const Venda& v);
    int proximoIdVenda() const;
    void devolverEstoque(const Venda& venda);

    Venda finalizarPedido(
    Comprador& c,
    const Endereco& end,
    MetodoPagamento metodo,
    const Desconto* cupom
    );
};
#endif