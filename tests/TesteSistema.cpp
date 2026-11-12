#include <stdexcept>
#include "doctest.h"
#include "Gerente.hpp"
#include "Sistema.hpp"
#include "Comprador.hpp"
#include "Endereco.hpp"
#include "ItemPedido.hpp"
#include "Venda.hpp"
#include "Desconto.hpp"

namespace {
Produto criarProduto(int id) {
    return Produto(id, "Rosa", "Buque", "Buques", 50.0, "img.png", 10, 3);
}
Gerente* criarGerente(const std::string& email) {
    return new Gerente(1, "Emanuelle", "111", email, "999", "senha123");
}
Endereco criarEndereco() {
    return Endereco("Maria Silva", "30130000", "Rua das Flores", "100", "Centro", "Apto 2", "Belo Horizonte", "MG");
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


TEST_CASE("Sistema - proximoId devolve o maior id + 1") {
    Sistema s;
    CHECK(s.proximoIdProduto() == 1);
    CHECK(s.proximoIdUsusario() == 1);
    CHECK(s.proximoIdVenda() == 1);
 
    s.adicionarProduto(criarProduto(1));
    s.adicionarProduto(criarProduto(5));
    CHECK(s.proximoIdProduto() == 6);
 
    s.adicionarUsuario(criarGerente("ana@email.com"));  // id 1
    CHECK(s.proximoIdUsusario() == 2);
}
 
TEST_CASE("Sistema - vendas: adicionar, buscar e rejeitar id repetido") {
    Sistema s;
    CHECK(s.getVendas().empty());
 
    s.adicionarVenda(Venda(1, 7, 0, criarEndereco(), "Maria Silva"));
 
    REQUIRE(s.buscarVenda(1) != nullptr);
    CHECK(s.buscarVenda(1)->getIdPessoa() == 7);
    CHECK(s.buscarVenda(2) == nullptr);
    CHECK_THROWS_AS(s.adicionarVenda(Venda(1, 8, 0, criarEndereco(), "Joao")), std::invalid_argument);
    CHECK(s.getVendas().size() == 1);
    CHECK(s.proximoIdVenda() == 2);
}
 
TEST_CASE("Sistema - devolverEstoque") {
    Sistema s;
    s.adicionarProduto(criarProduto(1));  // estoque 10
    Venda v(1, 7, 0, criarEndereco(), "Maria Silva");
    v.adicionarItem(ItemPedido(*s.buscarProduto(1), 3));
 
    SUBCASE("venda nao cancelada lanca logic_error e nao mexe no estoque") {
        CHECK_THROWS_AS(s.devolverEstoque(v), std::logic_error);
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 10);
    }
    SUBCASE("venda cancelada devolve os itens ao estoque") {
        v.atualizarSvenda(StatusVenda::CANCELADO);
        s.devolverEstoque(v);
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 13);
    }
}
 
TEST_CASE("Sistema - finalizarPedido valida tudo antes de mexer em algo") {
    Sistema s;
    s.adicionarProduto(criarProduto(1));  // estoque 10
    Comprador c(2, "Ana", "", "ana@email.com", "", "senha123");
 
    SUBCASE("carrinho vazio lanca invalid_argument") {
        CHECK_THROWS_AS(s.finalizarPedido(c, criarEndereco(), nullptr),
                        std::invalid_argument);
    }
    SUBCASE("endereco sem destinatario lanca invalid_argument") {
        c.adicionarAoCarrinho(ItemPedido(*s.buscarProduto(1), 3));
        CHECK_THROWS_AS(s.finalizarPedido(c, Endereco(), nullptr),
                        std::invalid_argument);
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 10);
        CHECK(c.consultarCarrinho().size() == 1);  // carrinho preservado
    }
    SUBCASE("estoque insuficiente lanca runtime_error e nao altera nada") {
        c.adicionarAoCarrinho(ItemPedido(*s.buscarProduto(1), 3));
        s.buscarProduto(1)->removerEstoque(8);  // sobram 2
        CHECK_THROWS_AS(s.finalizarPedido(c, criarEndereco(), nullptr),
                        std::runtime_error);
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 2);
        CHECK(s.getVendas().empty());
        CHECK(c.consultarCarrinho().size() == 1);
    }
    SUBCASE("produto que nao esta no sistema lanca runtime_error") {
        c.adicionarAoCarrinho(ItemPedido(criarProduto(99), 1));
        CHECK_THROWS_AS(s.finalizarPedido(c, criarEndereco(), nullptr),
                        std::runtime_error);
        CHECK(s.getVendas().empty());
    }
}
 
TEST_CASE("Sistema - finalizarPedido registra a venda e da baixa no estoque") {
    Sistema s;
    s.adicionarProduto(criarProduto(1));  // estoque 10, preco 50
    Comprador c(2, "Ana", "", "ana@email.com", "", "senha123");
    c.adicionarAoCarrinho(ItemPedido(*s.buscarProduto(1), 2));  // 100.00 em produtos
 
    // mesma venda montada a mao, sem cupom, para descobrir o total com frete
    Venda referencia(99, 2, 0, criarEndereco(), "Maria Silva");
    referencia.adicionarItem(ItemPedido(*s.buscarProduto(1), 2));
 
    SUBCASE("sem cupom") {
        Venda v = s.finalizarPedido(c, criarEndereco(), nullptr);
 
        CHECK(v.getIdVenda() == 1);
        CHECK(v.getIdPessoa() == 2);
        CHECK(v.getNomeDestina() == "Maria Silva");
        CHECK(v.getMetodoPagamento() == MetodoPagamento::PIX);
        CHECK(v.getValorTotal() == doctest::Approx(referencia.getValorTotal()));
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 8);
        CHECK(s.getVendas().size() == 1);
        CHECK(c.consultarCarrinho().empty());
        CHECK_FALSE(v.getDataEntrega().empty());
        CHECK_FALSE(v.getHorarioEntregaPrevisao().empty());
    }
    SUBCASE("com cupom valido de 10%") {
        Desconto cupom("DEZ", 10.0, "2099-12-31");
        Venda v = s.finalizarPedido(c, criarEndereco(), &cupom,
                                    );
 
        CHECK(v.getDescontoAplicado().getCupom() == "DEZ");
        CHECK(v.getValorTotal() == doctest::Approx(referencia.getValorTotal() - 10.0));
        CHECK(s.buscarVenda(1)->getValorTotal() == doctest::Approx(v.getValorTotal()));
    }
    SUBCASE("o segundo pedido recebe o id seguinte") {
        s.finalizarPedido(c, criarEndereco(), nullptr);
        c.adicionarAoCarrinho(ItemPedido(*s.buscarProduto(1), 1));
        Venda v2 = s.finalizarPedido(c, criarEndereco(), nullptr);
 
        CHECK(v2.getIdVenda() == 2);
        CHECK(s.buscarProduto(1)->getQuantidadeEstoque() == 7);
    }
}
 