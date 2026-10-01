#ifndef GERENTE_HPP
#define GERENTE_HPP

#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Venda.hpp"
#include "Desconto.hpp"

class Gerente : public Pessoa {
public:
    Gerente();
    Gerente(int idPessoa, const std::string& nome, const std::string& cpf, 
            const std::string& email, const std::string& telefone, const std::string& senha);
    ~Gerente() override;

    // produtos e estoques
    void cadastrarProduto(Produto& produto);
    void editarProduto(Produto& produto, const std::string& nome, const std::string& descricao, double preco, const std::string& categoria);
    void adicionarEstoqueProduto(Produto& produto, int quantidade);
    bool removerEstoqueProduto(Produto& produto, int quantidade);
    void definirEstoqueMinimoProduto(Produto& produto, int quantidadeMinima);

    // vendas
    void atualizarStatusVenda(Venda& venda, StatusVenda novoStatus);
    void atualizarStatusPagamento(Venda& venda, StatusPagamento novoStatus);

    // cupons
    Desconto cadastrarCupom(const std::string& codigo, double porcentagem, const std::string& dataValidade);
    void aplicarCupomVenda(Venda& venda, const Desconto& cupom);
};

#endif