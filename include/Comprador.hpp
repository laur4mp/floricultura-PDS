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
        //ainda nao sei sobre avaliacao


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
         * @brief Destrutor da classe Comprador. 
         */
        ~Comprador();

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
         * @brief Exibe os detalhes de um produto. 
         * 
         * @param produto Produto cujos detalhes serão exibidos. 
         */
        void verDetalhesProduto(const Produto& produto) const;

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
         * @brief Permite selecionar um endereço cadastrado para a entrega. 
         *
          * @return Endereço escolhido pelo comprador. 
         */
        Endereco selecionarEndereco() const;

        /** 
         * @brief Realiza um pedido com os itens selecionados. 
         * 
         * @param itens Itens que farão parte do pedido. 
         * @return Venda correspondente ao pedido realizado. 
         */
        Venda fazerPedido(const std::vector<ItemPedido>& itens);

        /** 
         * @brief Permite escolher o método de pagamento de uma venda. 
         * 
         * @param venda Venda à qual será associado o método de pagamento. 
         */
        void escolherMetodoPagamento(Venda& venda);

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

        //falta avaliar pedido
};
#endif 