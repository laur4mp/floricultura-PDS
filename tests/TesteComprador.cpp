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

    Produto buque(3, "Buque de Rosas", "Buque de Rosas", "Buque",
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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

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

    auto favoritos = comprador.getProdutosFavoritos();

    REQUIRE(favoritos.size() == 1);
    CHECK(favoritos[0].getNome() == "Rosa");
}

//consultarHistorico compras

TEST_CASE("Comprador inicia com historico de compras vazio") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    std::vector<Venda> vendas;

    CHECK(comprador.consultarHistoricoCompras(vendas).empty());
}

TEST_CASE("Historico registra uma compra realizada") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");
    Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    std::vector<Venda> vendas;
    comprador.adicionarAoCarrinho(ItemPedido(rosa, 2));
    vendas.push_back(comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO));

    auto historico = comprador.consultarHistoricoCompras(vendas);

    REQUIRE(historico.size() == 1);
    CHECK(historico[0].getIdVenda() == 1);
}

TEST_CASE("Historico registra varias compras realizadas") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");
    Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    std::vector<Venda> vendas;
    comprador.adicionarAoCarrinho(ItemPedido(rosa, 2));
    vendas.push_back(comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO));
    comprador.adicionarAoCarrinho(ItemPedido(rosa, 2));
    vendas.push_back(comprador.fazerPedido(2, endereco, MetodoPagamento::DINHEIRO));

    auto historico = comprador.consultarHistoricoCompras(vendas);

    REQUIRE(historico.size() == 2);
    CHECK(historico[0].getIdVenda() == 1);
    CHECK(historico[1].getIdVenda() == 2);
}

TEST_CASE("Historico nao mostra compras de outro comprador") {
    Comprador tomas(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Comprador ana(2, "Ana", "98765432100", "ana@email.com", "11888888888", "senha");
    Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    std::vector<Venda> vendas;
    ana.adicionarAoCarrinho(ItemPedido(rosa, 1));
    vendas.push_back(ana.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO));

    CHECK(tomas.consultarHistoricoCompras(vendas).empty());
}

//acompanhar pedido

TEST_CASE("Comprador acompanha pedido enviado") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO);
    venda.atualizarSvenda(StatusVenda::ENVIADO);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::ENVIADO);
}

TEST_CASE("Comprador acompanha pedido em processamento") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO);
    venda.atualizarSvenda(StatusVenda::PROCESSAMENTO);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::PROCESSAMENTO);
}

TEST_CASE("Comprador acompanha pedido entregue") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

   Endereco endereco("Tomas", "30100000", "rua dos fodoes",
                      "123", "taylor", "Apt 101",
                      "Belo Horizonte", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO);

    venda.atualizarSvenda(StatusVenda::ENVIADO);
    venda.atualizarSvenda(StatusVenda::ENTREGUE);

    CHECK(comprador.acompanharPedido(venda) == StatusVenda::ENTREGUE);
}

//fazerpedido
TEST_CASE("Comprador faz pedido com itens validos") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "asdashdajf");

    Endereco endereco("Tomas", "30100000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);

    Venda venda = comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO);

    CHECK(venda.getIdVenda() == 1);
    CHECK(venda.getItens().size() == 1);
}

TEST_CASE("Fazer pedido sem itens") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    CHECK_THROWS(comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO));
}



TEST_CASE("Fazer pedido limpa o carrinho apos a compra") {
    Comprador comprador(1, "Tomas", "12345678900",
                        "tomas@email.com", "11999999999", "senha");

    Endereco endereco("Tomas", "30100000", "rua dos swifties",
                      "123", "aaaaaaa", "Apt 666",
                      "Governador Valadares", "MG");

    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores",
                 5.0, "rosa.jpg", 100, 10);

    ItemPedido item(rosa, 2);

    comprador.adicionarAoCarrinho(item);
    comprador.fazerPedido(1, endereco, MetodoPagamento::DINHEIRO);

    CHECK(comprador.consultarCarrinho().empty());
}

//pro carrinho

TEST_CASE("Adicionar o mesmo produto soma a quantidade") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 2));
    c.adicionarAoCarrinho(ItemPedido(rosa, 3));

    REQUIRE(c.consultarCarrinho().size() == 1);
    CHECK(c.consultarCarrinho()[0].getQuantidade() == 5);
}

TEST_CASE("Alterar quantidade no carrinho") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 2));
    c.alterarQuantidadeCarrinho(1, 7);

    CHECK(c.consultarCarrinho()[0].getQuantidade() == 7);
}

TEST_CASE("Alterar quantidade para zero remove do carrinho") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 2));
    c.alterarQuantidadeCarrinho(1, 0);

    CHECK(c.consultarCarrinho().empty());
}

TEST_CASE("Subtotal do carrinho") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);
    Produto tulipa(2, "Tulipa", "Tulipa amarela", "Flores", 15.0, "tulipa.jpg", 10, 3);

    c.adicionarAoCarrinho(ItemPedido(rosa, 2));
    c.adicionarAoCarrinho(ItemPedido(tulipa, 1));

    CHECK(c.subtotalCarrinho() == 25.0);
}

TEST_CASE("Limpar carrinho") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 2));
    c.limparCarrinho();

    CHECK(c.consultarCarrinho().empty());
}

//bool favoriot

TEST_CASE("ehFavorito indica se o produto esta nos favoritos") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    CHECK_FALSE(c.ehFavorito(1));
    c.favoritarProduto(rosa);
    CHECK(c.ehFavorito(1));
}

//cancelar pedido

TEST_CASE("Comprador cancela pedido em processamento") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Endereco e("Tomas", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 1));
    Venda v = c.fazerPedido(1, e, MetodoPagamento::DINHEIRO);
    c.cancelarPedido(v);

    CHECK(v.getStatusVenda() == StatusVenda::CANCELADO);
}

TEST_CASE("Comprador nao cancela pedido ja enviado") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Endereco e("Tomas", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 1));
    Venda v = c.fazerPedido(1, e, MetodoPagamento::DINHEIRO);
    v.atualizarSvenda(StatusVenda::ENVIADO);

    CHECK_THROWS(c.cancelarPedido(v));
}

TEST_CASE("Comprador nao cancela pedido de outra pessoa") {
    Comprador tomas(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Comprador ana(2, "Ana", "98765432100", "ana@email.com", "11888888888", "senha");
    Endereco e("Ana", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    ana.adicionarAoCarrinho(ItemPedido(rosa, 1));
    Venda v = ana.fazerPedido(1, e, MetodoPagamento::DINHEIRO);

    CHECK_THROWS(tomas.cancelarPedido(v));
}

//avaliarPedido
TEST_CASE("Comprador avalia pedido entregue") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Endereco e("Tomas", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 1));
    Venda v = c.fazerPedido(1, e, MetodoPagamento::DINHEIRO);
    v.atualizarSvenda(StatusVenda::ENVIADO);
    v.atualizarSvenda(StatusVenda::ENTREGUE);
    c.avaliarPedido(v, 5);

    CHECK(v.getAvaliacao() == 5);
}

TEST_CASE("Comprador nao avalia pedido que nao foi entregue") {
    Comprador c(1, "Tomas", "12345678900", "tomas@email.com", "11999999999", "senha");
    Endereco e("Tomas", "30100000", "Rua A", "10", "Centro", "", "Belo Horizonte", "MG");
    Produto rosa(1, "Rosa", "Rosa vermelha", "Flores", 5.0, "rosa.jpg", 100, 10);

    c.adicionarAoCarrinho(ItemPedido(rosa, 1));
    Venda v = c.fazerPedido(1, e, MetodoPagamento::DINHEIRO);

    CHECK_THROWS(c.avaliarPedido(v, 5));
}

