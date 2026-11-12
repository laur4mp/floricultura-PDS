#include "doctest.h"
#include "Produto.hpp"
#include <stdexcept>


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

TEST_CASE("Produto: construtor padrao") {
    Produto p;
    CHECK(p.getIdProduto() == 0);
    CHECK(p.getNome().empty());
    CHECK(p.getPreco() == doctest::Approx(0.0));
    CHECK(p.getQuantidadeEstoque() == 0);
    CHECK(p.getQuantidadeMinima() == 0);
}

TEST_CASE("Produto: construtor rejeita dados invalidos") {
    CHECK_THROWS_AS(Produto(0, "Rosa", "", "Flores", 15.0, "", 10, 2),  std::invalid_argument);  // id
    CHECK_THROWS_AS(Produto(-1, "Rosa", "", "Flores", 15.0, "", 10, 2), std::invalid_argument);
    CHECK_THROWS_AS(Produto(1, "", "", "Flores", 15.0, "", 10, 2),      std::invalid_argument);  // nome
    CHECK_THROWS_AS(Produto(1, "Rosa", "", "", 15.0, "", 10, 2),        std::invalid_argument);  // categoria
    CHECK_THROWS_AS(Produto(1, "Rosa", "", "Flores", -0.01, "", 10, 2), std::invalid_argument);  // preco
    CHECK_THROWS_AS(Produto(1, "Rosa", "", "Flores", 15.0, "", -1, 2),  std::invalid_argument);  // estoque
    CHECK_THROWS_AS(Produto(1, "Rosa", "", "Flores", 15.0, "", 10, -1), std::invalid_argument);  // minimo
    CHECK_NOTHROW(Produto(1, "Rosa", "", "Flores", 0.0, "", 0, 0));  // zeros e textos opcionais vazios
}

TEST_CASE("Produto: setters invalidos lancam excecao e mantem o valor") {
    Produto p(1, "Rosas", "Rosa", "Flores", 15.0, "img/rosa.png", 50, 10);

    CHECK_THROWS_AS(p.setNome(""), std::invalid_argument);
    CHECK_THROWS_AS(p.setCategoria(""), std::invalid_argument);
    CHECK_THROWS_AS(p.setPreco(-1.0), std::invalid_argument);
    CHECK_THROWS_AS(p.setQuantidadeMinima(-1), std::invalid_argument);

    CHECK(p.getNome() == "Rosas");
    CHECK(p.getCategoria() == "Flores");
    CHECK(p.getPreco() == doctest::Approx(15.0));
    CHECK(p.getQuantidadeMinima() == 10);

    CHECK_NOTHROW(p.setPreco(0.0));
    CHECK_NOTHROW(p.setQuantidadeMinima(0));
    CHECK_NOTHROW(p.setDescricao(""));
}

TEST_CASE("Produto: quantidades invalidas no estoque") {
    Produto p(1, "Rosas", "Rosa", "Flores", 15.0, "img/rosa.png", 10, 3);

    CHECK_THROWS_AS(p.adicionarEstoque(0), std::invalid_argument);
    CHECK_THROWS_AS(p.adicionarEstoque(-5), std::invalid_argument);
    CHECK_THROWS_AS(p.removerEstoque(0), std::invalid_argument);
    CHECK_THROWS_AS(p.removerEstoque(-5), std::invalid_argument);
    CHECK(p.getQuantidadeEstoque() == 10);
}

TEST_CASE("Produto: limites do estoque") {
    Produto p(1, "Rosas", "Rosa", "Flores", 15.0, "img/rosa.png", 10, 3);

    CHECK(p.removerEstoque(7) == true);          
    CHECK(p.verificarEstoqueMinimo() == true);
    CHECK(p.removerEstoque(3) == true);        
    CHECK(p.getQuantidadeEstoque() == 0);
    CHECK(p.removerEstoque(1) == false);        
    p.adicionarEstoque(4);                       
    CHECK(p.verificarEstoqueMinimo() == false);
}

