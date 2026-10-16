#include <stdexcept>
#include <string>

#include "doctest.h"

#include "Desconto.hpp"
#include "Endereco.hpp"
#include "Gerente.hpp"
#include "ItemPedido.hpp"
#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Venda.hpp"

namespace {

Gerente criarGerente() {
    return Gerente(1, "Carlos Lima", "111.444.777-35", "carlos@floricultura.com", "(31) 98888-7777", "admin123");
}

// id 1, preco 50, estoque 10, estoque minimo 3
Produto criarProduto() {
    return Produto(1, "Rosa Vermelha", "Buque com 12 rosas", "Buques", 50.0, "img/rosa.png", 10, 3);
}

Venda criarVenda() {
    Endereco endereco("Maria Silva", "30130-000", "Rua das Flores", "100", "Centro", "Apto 2", "Belo Horizonte", "MG");
    return Venda(1, "529.982.247-25", endereco, "Maria Silva");
}

}  // namespace



TEST_CASE("Gerente - construtor com dados repassa os atributos para Pessoa") {
    Gerente g = criarGerente();

    CHECK(g.getIdPessoa() == 1);
    CHECK(g.getNome() == "Carlos Lima");
    CHECK(g.getCpf() == "111.444.777-35");
    CHECK(g.getEmail() == "carlos@floricultura.com");
    CHECK(g.getTelefone() == "(31) 98888-7777");
    CHECK(g.getSenha() == "admin123");
    CHECK(g.getEnderecos().empty());
}

TEST_CASE("Gerente - construtor padrao inicia com valores vazios") {
    Gerente g;

    CHECK(g.getIdPessoa() == 0);
    CHECK(g.getNome().empty());
    CHECK(g.getEnderecos().empty());
}

TEST_CASE("Gerente - e uma Pessoa via ponteiro da base") {
    Pessoa* p = new Gerente(1, "Carlos Lima", "111.444.777-35", "carlos@floricultura.com", "(31) 98888-7777", "admin123");

    CHECK(p->getNome() == "Carlos Lima");
    CHECK(dynamic_cast<Gerente*>(p) != nullptr);
    CHECK_NOTHROW(delete p);  // destrutor virtual de Pessoa
}

TEST_CASE("Gerente - cadastrarProduto aceita um produto valido sem alterar seus dados") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    CHECK_NOTHROW(g.cadastrarProduto(produto));
    CHECK(produto.getNome() == "Rosa Vermelha");
    CHECK(produto.getQuantidadeEstoque() == 10);
}

TEST_CASE("Gerente - editarProduto atualiza nome, descricao, preco e categoria") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    SUBCASE("caminho feliz") {
        g.editarProduto(produto, "Rosa Branca", "Buque com 6 rosas", 35.5, "Presentes");

        CHECK(produto.getNome() == "Rosa Branca");
        CHECK(produto.getDescricao() == "Buque com 6 rosas");
        CHECK(produto.getPreco() == doctest::Approx(35.5));
        CHECK(produto.getCategoria() == "Presentes");
    }
    SUBCASE("nao altera identificador nem estoque") {
        g.editarProduto(produto, "Rosa Branca", "Buque com 6 rosas", 35.5, "Presentes");

        CHECK(produto.getIdProduto() == 1);
        CHECK(produto.getQuantidadeEstoque() == 10);
        CHECK(produto.getQuantidadeMinima() == 3);
    }
    SUBCASE("preco negativo lanca invalid_argument e nao altera o produto") {
        CHECK_THROWS_AS(g.editarProduto(produto, "Rosa Branca", "Buque", -1.0, "Presentes"),
                        std::invalid_argument);
        CHECK(produto.getNome() == "Rosa Vermelha");
        CHECK(produto.getPreco() == doctest::Approx(50.0));
    }
}

TEST_CASE("Gerente - adicionarEstoqueProduto soma unidades ao estoque") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    SUBCASE("quantidade tipica") {
        g.adicionarEstoqueProduto(produto, 5);
        CHECK(produto.getQuantidadeEstoque() == 15);
    }
    SUBCASE("quantidade minima valida (1)") {
        g.adicionarEstoqueProduto(produto, 1);
        CHECK(produto.getQuantidadeEstoque() == 11);
    }
    SUBCASE("chamadas sucessivas acumulam") {
        g.adicionarEstoqueProduto(produto, 2);
        g.adicionarEstoqueProduto(produto, 3);
        CHECK(produto.getQuantidadeEstoque() == 15);
    }
}

TEST_CASE("Gerente - adicionarEstoqueProduto com quantidade invalida lanca invalid_argument") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    SUBCASE("zero") {
        CHECK_THROWS_AS(g.adicionarEstoqueProduto(produto, 0), std::invalid_argument);
    }
    SUBCASE("negativa") {
        CHECK_THROWS_AS(g.adicionarEstoqueProduto(produto, -4), std::invalid_argument);
    }
    CHECK(produto.getQuantidadeEstoque() == 10); // em qualquer caso o estoque permanece intacto
}

TEST_CASE("Gerente - removerEstoqueProduto") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    SUBCASE("estoque suficiente: remove e retorna true") {
        CHECK(g.removerEstoqueProduto(produto, 4) == true);
        CHECK(produto.getQuantidadeEstoque() == 6);
    }
    SUBCASE("limite: remover exatamente todo o estoque") {
        CHECK(g.removerEstoqueProduto(produto, 10) == true);
        CHECK(produto.getQuantidadeEstoque() == 0);
    }
    SUBCASE("estoque insuficiente: retorna false e nao altera o estoque") {
        CHECK(g.removerEstoqueProduto(produto, 11) == false);
        CHECK(produto.getQuantidadeEstoque() == 10);
    }
    SUBCASE("estoque zerado: nao permite remover mais nada") {
        REQUIRE(g.removerEstoqueProduto(produto, 10) == true);
        CHECK(g.removerEstoqueProduto(produto, 1) == false);
        CHECK(produto.getQuantidadeEstoque() == 0);
    }
}

TEST_CASE("Gerente - definirEstoqueMinimoProduto") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();

    SUBCASE("atualiza a quantidade minima") {
        g.definirEstoqueMinimoProduto(produto, 5);
        CHECK(produto.getQuantidadeMinima() == 5);
        CHECK(produto.getQuantidadeEstoque() == 10);
    }
    SUBCASE("estoque acima do minimo: sem alerta") {
        g.definirEstoqueMinimoProduto(produto, 5);
        CHECK_FALSE(produto.verificarEstoqueMinimo());
    }
    SUBCASE("estoque igual ao minimo: alerta (limite)") {
        g.definirEstoqueMinimoProduto(produto, 10);
        CHECK(produto.verificarEstoqueMinimo());
    }
    SUBCASE("estoque abaixo do minimo: alerta") {
        g.definirEstoqueMinimoProduto(produto, 12);
        CHECK(produto.verificarEstoqueMinimo());
    }
}

TEST_CASE("Gerente - atualizarStatusVenda altera o status de processamento/entrega") {
    Gerente g = criarGerente();
    Venda venda = criarVenda();

    SUBCASE("ENVIADO") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        CHECK(venda.getStatusVenda() == StatusVenda::ENVIADO);
    }
    SUBCASE("ENTREGUE") {
        g.atualizarStatusVenda(venda, StatusVenda::ENTREGUE);
        CHECK(venda.getStatusVenda() == StatusVenda::ENTREGUE);
    }
    SUBCASE("CANCELADO") {
        g.atualizarStatusVenda(venda, StatusVenda::CANCELADO);
        CHECK(venda.getStatusVenda() == StatusVenda::CANCELADO);
    }
    SUBCASE("PROCESSAMENTO (voltar ao estado inicial)") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        g.atualizarStatusVenda(venda, StatusVenda::PROCESSAMENTO);
        CHECK(venda.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    }
}

TEST_CASE("Gerente - atualizarStatusPagamento altera apenas o pagamento") {
    Gerente g = criarGerente();
    Venda venda = criarVenda();
    StatusVenda statusAntes = venda.getStatusVenda();

    SUBCASE("PAGO") {
        g.atualizarStatusPagamento(venda, StatusPagamento::PAGO);
        CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
    }
    SUBCASE("AGUARDANDO_PAGAMENTO") {
        g.atualizarStatusPagamento(venda, StatusPagamento::PAGO);
        g.atualizarStatusPagamento(venda, StatusPagamento::AGUARDANDO_PAGAMENTO);
        CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);
    }

    CHECK(venda.getStatusVenda() == statusAntes);
}

TEST_CASE("Gerente - cadastrarCupom cria o cupom com codigo e percentual") {
    Gerente g = criarGerente();

    SUBCASE("caminho feliz") {
        Desconto cupom = g.cadastrarCupom("PRIMAVERA10", 10.0, "01/01/2026");

        CHECK(cupom.getCupom() == "PRIMAVERA10");
        CHECK(cupom.aplicar(200.0) == doctest::Approx(180.0));
    }
    SUBCASE("limite inferior: 0% nao altera o valor") {
        Desconto cupom = g.cadastrarCupom("SEM_DESCONTO", 0.0, "01/01/2026");
        CHECK(cupom.aplicar(100.0) == doctest::Approx(100.0));
    }
    SUBCASE("limite superior: 100% zera o valor") {
        Desconto cupom = g.cadastrarCupom("GRATIS", 100.0, "01/01/2026");
        CHECK(cupom.aplicar(100.0) == doctest::Approx(0.0));
    }
}

TEST_CASE("Gerente - cadastrarCupom com percentual invalido nao concede desconto") {
    Gerente g = criarGerente();

    Desconto negativo = g.cadastrarCupom("NEGATIVO", -10.0, "01/01/2026");
    Desconto absurdo = g.cadastrarCupom("ABSURDO", 150.0, "01/01/2026");

    CHECK(negativo.getCupom() == "NEGATIVO");
    CHECK(negativo.aplicar(100.0) == doctest::Approx(100.0));
    CHECK(absurdo.getCupom() == "ABSURDO");
    CHECK(absurdo.aplicar(100.0) == doctest::Approx(100.0));
}

TEST_CASE("Gerente - aplicarCupomVenda reduz o valor total da venda") {
    Gerente g = criarGerente();
    Venda venda = criarVenda();
    venda.adicionarItem(ItemPedido(criarProduto(), 2));  // 2 x 50.00 = 100.00
    venda.calcularValorTotal();

    SUBCASE("cupom de 10%") {
        g.aplicarCupomVenda(venda, Desconto("PRIMAVERA10", 10.0));
        CHECK(venda.getValorTotal() == doctest::Approx(90.0));
    }
    SUBCASE("cupom de 0% mantem o valor") {
        g.aplicarCupomVenda(venda, Desconto("SEM_DESCONTO", 0.0));
        CHECK(venda.getValorTotal() == doctest::Approx(100.0));
    }
}