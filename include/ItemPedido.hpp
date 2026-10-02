/**
 * @file ItemPedido.hpp 
 * @brief Declaraçâo da classe responsável por representar os items de uma venda.
  */

#ifndef ITEMPEDIDO_HPP
#define ITEMPEDIDO_HPP

#include "Produto.hpp"
#include "Endereco.hpp"

/**
 * @class ItemPedido
  * @brief Representa um produto e sua quantidade dentro de um pedido.
  *
  * A classe permite calcular o preço total do item e o frete de acordo
  * com a região do endereço de entrega.
  */

class ItemPedido {
    private:
        Produto _produtoPedido;
        int _quantidadePedida;

    public:
    
        /** 
         * @brief Construtor de um item de pedido.
         *
         * @param produto Produto que será incluído no pedido. 
         * @param quantidade Quantidade de unidades do produto. 
         */

        ItemPedido(const Produto& produto, int quantidade)
            : _produtoPedido(produto), _quantidadePedida(quantidade) {}

        /** 
         * @brief Destrutor da classe ItemPedido. 
         */ 
        ~ItemPedido();

        /**
         * @brief Calcula o preço total dos items pedidos.
         * @return Preço total do item.
        */
        double calcularPrecoTotal() const;

        /**
         * @brief Informa os dados do item do pedido.
        */
        void informarDados() const;

        /**
         * @brief Calcula o valor do frete dos itens.
         * O valor do frete depende da região do Brasil correspondente ao endereço de entrega.
         * @return Valor do frete.
        */
        double calcularFrete(const Endereco& endereco) const;
};

#endif 