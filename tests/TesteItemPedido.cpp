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

TEST_CASE("Frete por regiao") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    ItemPedido item(rosa, 1);

    CHECK(item.calcularFrete(Endereco("Ana", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG")) == 13.0);
    CHECK(item.calcularFrete(Endereco("Ana", "90000000", "Rua A", "10", "Centro", "", "Porto Alegre", "RS")) == 22.0);
    CHECK(item.calcularFrete(Endereco("Ana", "70000000", "Rua A", "10", "Centro", "", "Brasilia", "DF")) == 25.0);
    CHECK(item.calcularFrete(Endereco("Ana", "40000000", "Rua A", "10", "Centro", "", "Salvador", "BA")) == 30.0);
    CHECK(item.calcularFrete(Endereco("Ana", "69000000", "Rua A", "10", "Centro", "", "Manaus", "AM")) == 40.0);
}


TEST_CASE("Frete de endereco vazio eh zero") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    ItemPedido item(rosa, 1);

    CHECK(item.calcularFrete(Endereco()) == 0.0);
}

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

//setQuantidade
TEST_CASE("setQuantidade altera a quantidade") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    ItemPedido item(rosa, 1);

    item.setQuantidade(4);

    CHECK(item.getQuantidade() == 4);
    CHECK(item.calcularPrecoTotal() == 20.0);
}

TEST_CASE("setQuantidade nao aceita zero ou negativo") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    ItemPedido item(rosa, 2);

    CHECK_THROWS(item.setQuantidade(0));
    CHECK_THROWS(item.setQuantidade(-3));
    CHECK(item.getQuantidade() == 2);   // nao mudou
}

//informarDados
TEST_CASE("informarDados mostra quantidade, nome e total") {
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    ItemPedido item(rosa, 3);

    CHECK(item.informarDados() == "3 x Rosa (R$ 15.00)");
}