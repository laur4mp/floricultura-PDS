#include "doctest.h"
#include "Comprador.hpp"
#include "Produto.hpp"
#include "Pessoa.hpp"

#include <string>
#include <vector>

//Construtor
TEST_CASE("Construtor de Comprador inicializa dados pessoais") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    CHECK(comprador.getIdPessoa() == 1);
    CHECK(comprador.getNome() == "Tomas");
    CHECK(comprador.getCpf() == "12345678900");
    CHECK(comprador.getEmail() == "tomas@email.com");
    CHECK(comprador.getTelefone() == "11999999999");
    CHECK(comprador.getSenha() == "senha");
}

//pesquisarProdutos
TEST_CASE("Comprador pesquisa produtos pelo nome") {
    Comprador comprador(1, "Tomas", "12345678900",
                    "tomas@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
             10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
               15.0, "tulipa.jpg", 10, 3);

    Produto buque(3, "Buque", "Buque de Rosas", "Buque",
             25.0, "buque.jpg", 8, 2);

    std::vector<Produto> catalogo = {rosa, tulipa, buque};

    std::vector<Produto> resultado =
        comprador.pesquisarProdutos(catalogo, "Rosa");
       
    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Rosa");
}

TEST_CASE("Comprador nao encontra produto inexistente") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
             10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
               15.0, "tulipa.jpg", 10, 3);

    Produto buque(3, "Buque", "Buque de Rosas", "Buque",
             25.0, "buque.jpg", 8, 2);

    std::vector<Produto> catalogo = {rosa, tulipa, buque};

    std::vector<Produto> resultado =
        comprador.pesquisarProdutos(catalogo, "Orquidea");

    CHECK(resultado.empty());
}

TEST_CASE("Comprador pesquisa em catalogo vazio") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    std::vector<Produto> catalogo;

    std::vector<Produto> resultado =
        comprador.pesquisarProdutos(catalogo, "Rosa");

    CHECK(resultado.empty());
}

TEST_CASE("Comprador encontra varios produtos por busca parcial") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
                   15.0, "tulipa.jpg", 10, 3);

    Produto buque(3, "Buque", "Buque de Rosas", "Buque",
                  25.0, "buque.jpg", 8, 2);

    std::vector<Produto> catalogo = {rosa, tulipa, buque};

    std::vector<Produto> resultado =
        comprador.pesquisarProdutos(catalogo, "Rosa");

    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0].getNome() == "Rosa");
    CHECK(resultado[1].getNome() == "Buque de Rosas");
}

//filtrarProdutos
TEST_CASE("Comprador filtra categoria com um unico produto") {
    Comprador comprador(1, "Olivia Rodrigo", "12345678900",
                        "olivia@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto vaso(2, "Vaso", "Vaso de ceramica", "Decoracao",
                 30.0, "vaso.jpg", 10, 2);

    std::vector<Produto> catalogo = {rosa, vaso};

    std::vector<Produto> resultado =
        comprador.filtrarProdutos(catalogo, "Flores");

    REQUIRE(resultado.size() == 1);
    CHECK(resultado[0].getNome() == "Rosa");
} 

TEST_CASE("Comprador filtra varios produtos por categoria") {
    Comprador comprador(1, "Chappell Roan", "12345678900",
                        "lesbica@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
                   15.0, "tulipa.jpg", 10, 3);

    Produto buque(3, "Buque", "Buque de Rosas", "Buque",
                  25.0, "buque.jpg", 8, 2);

    std::vector<Produto> catalogo = {rosa, tulipa, buque};

    std::vector<Produto> resultado =
        comprador.filtrarProdutos(catalogo, "Flores");

    REQUIRE(resultado.size() == 2);
    CHECK(resultado[0].getNome() == "Rosa");
    CHECK(resultado[1].getNome() == "Tulipa");
}

TEST_CASE("Comprador nao encontra produtos na categoria filtrada") {
    Comprador comprador(1, "Taylor Swift", "12345678900",
                        "tswift@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    std::vector<Produto> catalogo = {rosa};

    std::vector<Produto> resultado =
        comprador.filtrarProdutos(catalogo, "Albuns");

    CHECK(resultado.empty());
}

TEST_CASE("Comprador filtra catalogo vazio") {
    Comprador comprador(1, "Lorde", "12345678900",
                        "lorde@email.com", "11999999999", "senha");

    std::vector<Produto> catalogo;

    std::vector<Produto> resultado =
        comprador.filtrarProdutos(catalogo, "Flores");

    CHECK(resultado.empty());
}

//favoritarProduto
TEST_CASE("Comprador favorita um produto") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    comprador.favoritarProduto(rosa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Rosa");
}

TEST_CASE("Comprador favorita dois produtos"){
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
                   15.0, "tulipa.jpg", 10, 3);
    comprador.favoritarProduto(rosa);
    comprador.favoritarProduto(tulipa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 2);
    CHECK(favoritos[0].getNome() == "Rosa");
    CHECK(favoritos[1].getNome() == "Tulipa");
}

TEST_CASE("Comprador tenta favoritar um produto duas vezes") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    comprador.favoritarProduto(rosa);
    comprador.favoritarProduto(rosa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Rosa");
}

//desfavoritarProduto
TEST_CASE("Comprador desfavorita um produto") {
    Comprador comprador(1, "Taylor Swift", "12345678900",
                        "taylor@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    comprador.favoritarProduto(rosa);
    comprador.desfavoritarProduto(rosa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    CHECK(favoritos.empty());
}

TEST_CASE("Comprador desfavorita produto que nao esta nos favoritos") {
    Comprador comprador(1, "Taylor Swift", "12345678900",
                        "taylor@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
                   15.0, "tulipa.jpg", 10, 3);

    comprador.favoritarProduto(rosa);
    comprador.desfavoritarProduto(tulipa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Rosa");
}

TEST_CASE("Comprador desfavorita apenas um produto selecionado") {
    Comprador comprador(1, "Taylor Swift", "12345678900",
                        "taylor@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores",
                   15.0, "tulipa.jpg", 10, 3);

    comprador.favoritarProduto(rosa);
    comprador.favoritarProduto(tulipa);
    comprador.desfavoritarProduto(rosa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Tulipa");
}
TEST_CASE("Comprador pode favoritar novamente um produto depois de desfavoritar") {
    Comprador comprador(1, "Taylor Swift", "12345678900",
                        "taylor@email.com", "11999999999", "senha");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 10.0, "rosa.jpg", 20, 5);

    comprador.favoritarProduto(rosa);
    comprador.desfavoritarProduto(rosa);
    comprador.favoritarProduto(rosa);

    auto favoritos = comprador.consultarProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Rosa");
}