/**
 * @file Comprador.hpp 
 * @brief Declaração da classe Comprador. 
 */
#ifndef COMPRADOR_HPP
#define COMPRADOR_HPP

#include <string>
#include <vector>
#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Venda.hpp"
#include "ItemPedido.hpp"
#include "Endereco.hpp"
#include "Desconto.hpp"

/** 
 * @class Comprador 
 * @brief Representa um comprador do sistema. 
 * 
 * Classe derivada de Pessoa que representa um usuário capaz de 
 * pesquisar e favroitar produtos, realizar pedidos, acompanhar 
 * suas compras e consultar seu historico de pedidos. 
 */

class Comprador : public Pessoa{
    private:
        std::vector<Produto> _produtosFavoritos;
        std::vector<Venda> _historicoPedidos;
        std::vector<ItemPedido> _carrinho;


    public:
        /** 
         * @brief Constrói um comprador com seus dados pessoais. 
         * 
         * @param idPessoa Identificador único da pessoa. 
         * @param nome Nome completo do comprador. 
         * @param cpf CPF do comprador. 
         * @param email E-mail do comprador. 
         * @param telefone Telefone de contato. 
         * @param senha Senha de acesso ao sistema. 
         */     
    
        Comprador(int idPessoa, const std::string& nome, const std::string& cpf,
          const std::string& email, const std::string& telefone,
          const std::string& senha)
            : Pessoa(idPessoa, nome, cpf, email, telefone, senha) {}

        /** 
         * @brief Pesquisa produtos pelo nome. 
         * 
         * @param produtos Catálogo de produtos a ser pesquisado. 
         * @param nome Nome ou termo utilizado na pesquisa. 
         * @return Vetor contendo os produtos encontrados. 
         */
        std::vector<Produto> pesquisarProdutos(
            const std::vector<Produto>& produtos,
            const std::string& nome
        ) const;

        /** 
         * @brief Filtra produtos por categoria. 
         * 
         * @param produtos Catálogo de produtos a ser filtrado. 
         * @param categoria Categoria utilizada como filtro. 
         * @return Vetor contendo os produtos pertencentes à categoria. 
         */
        std::vector<Produto> filtrarProdutos(
            const std::vector<Produto>& produtos,
            const std::string& categoria
        ) const;

        /** 
         * @brief Adiciona um produto à lista de favoritos. 
         * 
         * @param produto Produto que será favoritado. 
         */
        void favoritarProduto(const Produto& produto);

        /**
         * @brief Remove um produto da lista de favoritos. 
         * 
         * @param produto Produto que será removido dos favoritos. 
         */
        void desfavoritarProduto(const Produto& produto);


        /** 
         * @brief Realiza um pedido com os itens selecionados. 
         * 
         * @param itens Itens que farão parte do pedido. 
         * @param idVenda id da venda que será criada.
         * @param enderecoEntrega Endereço no qual o pedido será entregado.
         * @return Venda correspondente ao pedido realizado. 
         */
        Venda fazerPedido(
            int idVenda,
            const Endereco& enderecoEntrega
        );

        /** 
         * @brief Consulta o status de uma venda. 
         * 
         * @param venda Venda que será acompanhada. 
         * @return Status atual da venda. 
         */
        StatusVenda acompanharPedido(const Venda& venda) const;

        /**
         * @brief Cancela uma venda.
          * 
          * @param venda Venda que será cancelada. 
          */
        void cancelarPedido(Venda& venda);

        /**
         * @brief Consulta o histórico de compras do comprador. 
         * 
         * @return Referência constante ao vetor de vendas realizadas. 
         */
        const std::vector<Venda>& consultarHistoricoCompras() const;

        /**
        * @brief Consulta os produtos favoritos do comprador.
        *
        * @return Referência constante ao vetor de produtos favoritos.
        */
        const std::vector<Produto>& consultarProdutosFavoritos() const;

        /**
        * @brief Aplica um cupom de desconto a uma venda.
        * @param venda Venda que receberá o desconto.
        * @param cupom Cupom a ser aplicado.
        */
        void aplicarCupomVenda(Venda& venda, const Desconto& cupom);

        void adicionarAoCarrinho(const ItemPedido& item);

        const std::vector<ItemPedido>& consultarCarrinho() const;
        
        void limparCarrinho();
        
};
#endif 