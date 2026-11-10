#include <stdexcept>
#include "doctest.h"
#include "Gerente.hpp"
#include "Sistema.hpp"

namespace {
Produto criarProduto(int id) {
    return Produto(id, "Rosa", "Buque", "Buques", 50.0, "img.png", 10, 3);
}
Gerente* criarGerente(const std::string& email) {
    return new Gerente(1, "Emanuelle", "111", email, "999", "senha123");
}
}  // namespace

TEST_CASE("Sistema - autenticar devolve o usuario quando e-mail e senha conferem") {
    Sistema s;
    s.adicionarUsuario(criarGerente("ana@email.com"));

    Pessoa* p = s.autenticar("ana@email.com", "senha123");
    REQUIRE(p != nullptr);
    CHECK(p->getEmail() == "ana@email.com");
    CHECK(dynamic_cast<Gerente*>(p) != nullptr);   // o tipo real foi preservado
}

TEST_CASE("Sistema - autenticar devolve nullptr com senha ou e-mail errados") {
    Sistema s;
    s.adicionarUsuario(criarGerente("ana@email.com"));

    CHECK(s.autenticar("ana@email.com", "errada") == nullptr);
    CHECK(s.autenticar("outra@email.com", "senha123") == nullptr);
    CHECK(s.autenticar("", "") == nullptr);
}

TEST_CASE("Sistema - adicionarUsuario rejeita nulo e e-mail repetido") {
    Sistema s;
    s.adicionarUsuario(criarGerente("ana@email.com"));

    CHECK_THROWS_AS(s.adicionarUsuario(nullptr), std::invalid_argument);
    CHECK_THROWS_AS(s.adicionarUsuario(criarGerente("ana@email.com")), std::invalid_argument);
}

TEST_CASE("Sistema - produtos: adicionar, buscar por id e listar") {
    Sistema s;
    CHECK(s.getProdutos().empty());
    CHECK(s.buscarProduto(1) == nullptr);

    s.adicionarProduto(criarProduto(1));
    s.adicionarProduto(criarProduto(2));

    CHECK(s.getProdutos().size() == 2);
    REQUIRE(s.buscarProduto(2) != nullptr);
    CHECK(s.buscarProduto(2)->getIdProduto() == 2);
    CHECK(s.buscarProduto(3) == nullptr);
}

TEST_CASE("Sistema - adicionarProduto rejeita id repetido") {
    Sistema s;
    s.adicionarProduto(criarProduto(1));
    CHECK_THROWS_AS(s.adicionarProduto(criarProduto(1)), std::invalid_argument);
    CHECK(s.getProdutos().size() == 1);
}

TEST_CASE("Sistema - alterar o produto buscado altera o produto guardado") {
    Sistema s;
    s.adicionarProduto(criarProduto(1));
    Gerente g;

    g.adicionarEstoqueProduto(*s.buscarProduto(1), 5);

    CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 15);
}

TEST_CASE("Sistema - cupons: adicionar e buscar pelo codigo") {
    Sistema s;
    CHECK(s.buscarCupom("A") == nullptr);

    s.adicionarCupom(Desconto("A", 10.0, "2099-12-31"));
    s.adicionarCupom(Desconto("B", 50.0, "2099-12-31"));

    REQUIRE(s.buscarCupom("B") != nullptr);
    CHECK(s.buscarCupom("B")->aplicar(100.0) == doctest::Approx(50.0));
    CHECK(s.buscarCupom("C") == nullptr);
    CHECK(s.getCupons().size() == 2);
}

TEST_CASE("Sistema - adicionarCupom rejeita codigo repetido ou vazio") {
    Sistema s;
    s.adicionarCupom(Desconto("A", 10.0, "2099-12-31"));

    CHECK_THROWS_AS(s.adicionarCupom(Desconto("A", 20.0, "2099-12-31")), std::invalid_argument);
    CHECK_THROWS_AS(s.adicionarCupom(Desconto("", 5.0, "2099-12-31")), std::invalid_argument);
}