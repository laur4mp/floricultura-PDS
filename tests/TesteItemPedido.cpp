#include "doctest.h"
#include "ItemPedido.hpp"

//construtor
TEST_CASE("Construtor de ItemPedido") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 3);

    CHECK(item.getQuantidade() == 3);
    CHECK(item.getProduto().getNome() == "Rosa");
}

//calcularPrecoTotal
TEST_CASE("Calcular preco total com uma unidade") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 1);

    CHECK(item.calcularPrecoTotal() == 5.0);
}

TEST_CASE("Calcular preco total com varias unidades") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 3);

    CHECK(item.calcularPrecoTotal() == 15.0);
}

TEST_CASE("Calcular preco total com preco decimal") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.5, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 3);

    CHECK(item.calcularPrecoTotal() == 16.5);
}

//calcularFrete
//ainda nao decidimos a regra para os fretes de diferentes regioes
//Qtd de produtos tambem influencia

TEST_CASE("Nao permite quantidade zero") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    CHECK_THROWS(ItemPedido(rosa, 0));
}

TEST_CASE("Nao permite quantidade negativa") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    CHECK_THROWS(ItemPedido(rosa, -1));
}