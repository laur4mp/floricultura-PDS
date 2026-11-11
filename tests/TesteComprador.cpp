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

//consultarHistorico compras

TEST_CASE("Comprador inicia com historico de compras vazio") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    auto historico = comprador.consultarHistoricoCompras();

    CHECK(historico.empty());
}

TEST_CASE("Historico registra uma compra realizada") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100-000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);

    auto historico = comprador.consultarHistoricoCompras();

    REQUIRE(historico.size() == 1);
    CHECK(historico[0].getIdVenda() == venda.getIdVenda());
}

TEST_CASE("Historico registra varias compras realizadas") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100-000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);
    Venda venda1 = comprador.fazerPedido(1, endereco);

    comprador.adicionarAoCarrinho(item);
    Venda venda2 = comprador.fazerPedido(2, endereco);

    auto historico = comprador.consultarHistoricoCompras();

    REQUIRE(historico.size() == 2);
    CHECK(historico[0].getIdVenda() == venda1.getIdVenda());
    CHECK(historico[1].getIdVenda() == venda2.getIdVenda());
}

//acompanhar pedido

TEST_CASE("Comprador acompanha pedido enviado") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100-000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);
    venda.atualizarSvenda(StatusVenda::ENVIADO);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::ENVIADO);
}

TEST_CASE("Comprador acompanha pedido em processamento") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100-000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);
    venda.atualizarSvenda(StatusVenda::PROCESSAMENTO);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::PROCESSAMENTO);
}

TEST_CASE("Comprador acompanha pedido entregue") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100-000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);
    venda.atualizarSvenda(StatusVenda::ENTREGUE);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::ENTREGUE);
}

//fazerpedido
TEST_CASE("Comprador faz pedido com itens validos") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "asdashdajf");

    Endereco endereco("Tomas", "30100-000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);

    CHECK(venda.getIdVenda() == 1);
    CHECK(venda.getItens().size() == 1);
}

TEST_CASE("Fazer pedido sem itens") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100-000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    CHECK_THROWS(comprador.fazerPedido(1, endereco));
}

TEST_CASE("Fazer pedido registra venda no historico") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100-000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco);

    REQUIRE(comprador.consultarHistoricoCompras().size() == 1);

    CHECK(comprador.consultarHistoricoCompras()[0].getIdVenda()
          == venda.getIdVenda());
}

TEST_CASE("Fazer pedido limpa o carrinho apos a compra") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100-000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);
    comprador.fazerPedido(1, endereco);

    CHECK(comprador.consultarCarrinho().empty());
}