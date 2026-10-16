#include "doctest.h"
#include "Produto.hpp"
TEST_CASE("teste de inicialização getters, setters do produto"){
    Produto p(1, "Rosas", "Rosa linda para buques", "Flores", 15.00, "img/rosa.png", 50, 10);
    //getters
    CHECK(p.getIdProduto() == 1);
    CHECK(p.getNome() == "Rosas");
    CHECK(p.getDescricao() == "Rosa linda para buques");
    CHECK(p.getCategoria() == "Flores");
    CHECK(p.getPreco() == 15.00);
    CHECK(p.getEnderecoImagem() == "img/rosa.png");
    CHECK(p.getQuantidadeEstoque() == 50);
    CHECK(p.getQuantidadeMinima() == 10);
    //setters
    p.setNome("Orquídea");
    p.setPreco(30.0);
    p.setCategoria("Exóticas");
    p.setDescricao("Orquídea roxa");
    p.setEnderecoImagem("img/orquidea.png");
    p.setQuantidadeMinima(5);
    CHECK(p.getNome() == "Orquídea");
    CHECK(p.getPreco() == 30.0);
    CHECK(p.getCategoria() == "Exóticas");
    CHECK(p.getDescricao() == "Orquídea roxa");
    CHECK(p.getEnderecoImagem() == "img/orquidea.png");
    CHECK(p.getQuantidadeMinima() == 5);

}

TEST_CASE("Testando o controle de estoque do produto") {
    Produto p(2, "Margarida", "Margarida branca", "Flores", 5.0, "img/margarida.png", 20, 5);
    p.adicionarEstoque(10);
    CHECK(p.getQuantidadeEstoque() == 30);
    bool removeu = p.removerEstoque(15);
    CHECK(removeu == true);
    CHECK(p.getQuantidadeEstoque() == 15);
    //remove mais
    bool removeuExcess = p.removerEstoque(50);
    CHECK(removeuExcess == false);
    CHECK(p.getQuantidadeEstoque() == 15); 
    CHECK(p.verificarEstoqueMinimo() == false);

    //abaixo do min
    p.removerEstoque(12); 
    CHECK(p.getQuantidadeEstoque() == 3);
    CHECK(p.verificarEstoqueMinimo() == true);
}