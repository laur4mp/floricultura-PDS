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

Endereco criarEndereco() {
    // CEP so com os 8 digitos (o Endereco nao aceita hifen)
    return Endereco("Maria Silva", "30130000", "Rua das Flores", "100", "Centro", "Apto 2", "Belo Horizonte", "MG");
}

// venda sem itens: id 1, cliente 7
Venda criarVenda() {
    return Venda(1, 7, 0, criarEndereco(), "Maria Silva");
}

// venda com 2 x Rosa Vermelha (subtotal 100.00)
Venda criarVendaComItem() {
    Venda venda = criarVenda();
    venda.adicionarItem(ItemPedido(criarProduto(), 2));
    return venda;
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

TEST_CASE("Gerente - construtor padrao cria o administrador fixo") {
    Gerente g;

    CHECK(g.getIdPessoa() == 1);
    CHECK(g.getNome() == "Gerente TELL");
    CHECK(g.getEmail() == "admin@tell.com");
    CHECK(g.getSenha() == "admin");
    CHECK(g.getEnderecos().empty());
}

TEST_CASE("Gerente - e uma Pessoa via ponteiro da base") {
    Pessoa* p = new Gerente(1, "Carlos Lima", "111.444.777-35", "carlos@floricultura.com", "(31) 98888-7777", "admin123");

    CHECK(p->getNome() == "Carlos Lima");
    CHECK(dynamic_cast<Gerente*>(p) != nullptr);
    CHECK_NOTHROW(delete p);  // destrutor virtual de Pessoa
}

TEST_CASE("Gerente - cadastrarProduto cria o produto com os dados informados") {
    Gerente g = criarGerente();
    Produto p = g.cadastrarProduto(1, "Rosa Vermelha", "Buque com 12 rosas", "Buques",
                                   50.0, "img/rosa.png", 10, 3);

    CHECK(p.getIdProduto() == 1);
    CHECK(p.getNome() == "Rosa Vermelha");
    CHECK(p.getDescricao() == "Buque com 12 rosas");
    CHECK(p.getCategoria() == "Buques");
    CHECK(p.getPreco() == doctest::Approx(50.0));
    CHECK(p.getEnderecoImagem() == "img/rosa.png");
    CHECK(p.getQuantidadeEstoque() == 10);
    CHECK(p.getQuantidadeMinima() == 3);
}

TEST_CASE("Gerente - cadastrarProduto com dados invalidos lanca invalid_argument") {
    Gerente g = criarGerente();

    CHECK_THROWS_AS(g.cadastrarProduto(0, "Rosa", "", "Buques", 50.0, "", 10, 3), std::invalid_argument);   // id
    CHECK_THROWS_AS(g.cadastrarProduto(1, "", "", "Buques", 50.0, "", 10, 3), std::invalid_argument);       // nome
    CHECK_THROWS_AS(g.cadastrarProduto(1, "Rosa", "", "", 50.0, "", 10, 3), std::invalid_argument);         // categoria
    CHECK_THROWS_AS(g.cadastrarProduto(1, "Rosa", "", "Buques", -1.0, "", 10, 3), std::invalid_argument);   // preco
    CHECK_THROWS_AS(g.cadastrarProduto(1, "Rosa", "", "Buques", 50.0, "", -1, 3), std::invalid_argument);   // estoque
    CHECK_THROWS_AS(g.cadastrarProduto(1, "Rosa", "", "Buques", 50.0, "", 10, -1), std::invalid_argument);  // minimo
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
    CHECK(produto.getQuantidadeEstoque() == 10);  // em qualquer caso o estoque permanece intacto
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
    SUBCASE("quantidade zero ou negativa: retorna false") {
        CHECK(g.removerEstoqueProduto(produto, 0) == false);
        CHECK(g.removerEstoqueProduto(produto, -3) == false);
        CHECK(produto.getQuantidadeEstoque() == 10);
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
    SUBCASE("minimo negativo lanca invalid_argument") {
        CHECK_THROWS_AS(g.definirEstoqueMinimoProduto(produto, -1), std::invalid_argument);
        CHECK(produto.getQuantidadeMinima() == 3);
    }
}

TEST_CASE("Gerente - ajustarEstoqueProduto define o estoque para o valor exato") {
    Gerente g = criarGerente();
    Produto produto = criarProduto();  // estoque 10

    SUBCASE("aumentar") {
        g.ajustarEstoqueProduto(produto, 25);
        CHECK(produto.getQuantidadeEstoque() == 25);
    }
    SUBCASE("diminuir") {
        g.ajustarEstoqueProduto(produto, 4);
        CHECK(produto.getQuantidadeEstoque() == 4);
    }
    SUBCASE("zerar") {
        g.ajustarEstoqueProduto(produto, 0);
        CHECK(produto.getQuantidadeEstoque() == 0);
    }
    SUBCASE("mesmo valor nao muda nada") {
        g.ajustarEstoqueProduto(produto, 10);
        CHECK(produto.getQuantidadeEstoque() == 10);
    }
    SUBCASE("negativo lanca invalid_argument e nao altera o estoque") {
        CHECK_THROWS_AS(g.ajustarEstoqueProduto(produto, -1), std::invalid_argument);
        CHECK(produto.getQuantidadeEstoque() == 10);
    }
}

TEST_CASE("Gerente - atualizarStatusVenda segue o fluxo do pedido") {
    Gerente g = criarGerente();
    Venda venda = criarVendaComItem();  // comeca em PROCESSAMENTO

    SUBCASE("PROCESSAMENTO -> ENVIADO") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        CHECK(venda.getStatusVenda() == StatusVenda::ENVIADO);
    }
    SUBCASE("ENVIADO -> ENTREGUE marca o pagamento como PAGO") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        g.atualizarStatusVenda(venda, StatusVenda::ENTREGUE);
        CHECK(venda.getStatusVenda() == StatusVenda::ENTREGUE);
        CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
    }
    SUBCASE("PROCESSAMENTO -> CANCELADO") {
        g.atualizarStatusVenda(venda, StatusVenda::CANCELADO);
        CHECK(venda.getStatusVenda() == StatusVenda::CANCELADO);
    }
    SUBCASE("repetir o status atual nao faz nada") {
        CHECK_NOTHROW(g.atualizarStatusVenda(venda, StatusVenda::PROCESSAMENTO));
        CHECK(venda.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    }
}

TEST_CASE("Gerente - atualizarStatusVenda rejeita transicoes invalidas") {
    Gerente g = criarGerente();
    Venda venda = criarVendaComItem();

    SUBCASE("nao entrega sem enviar antes") {
        CHECK_THROWS_AS(g.atualizarStatusVenda(venda, StatusVenda::ENTREGUE), std::logic_error);
        CHECK(venda.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    }
    SUBCASE("nao volta para PROCESSAMENTO") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        CHECK_THROWS_AS(g.atualizarStatusVenda(venda, StatusVenda::PROCESSAMENTO), std::logic_error);
        CHECK(venda.getStatusVenda() == StatusVenda::ENVIADO);
    }
    SUBCASE("pedido cancelado nao muda mais") {
        g.atualizarStatusVenda(venda, StatusVenda::CANCELADO);
        CHECK_THROWS_AS(g.atualizarStatusVenda(venda, StatusVenda::ENVIADO), std::logic_error);
        CHECK(venda.getStatusVenda() == StatusVenda::CANCELADO);
    }
    SUBCASE("pedido entregue nao muda mais") {
        g.atualizarStatusVenda(venda, StatusVenda::ENVIADO);
        g.atualizarStatusVenda(venda, StatusVenda::ENTREGUE);
        CHECK_THROWS_AS(g.atualizarStatusVenda(venda, StatusVenda::CANCELADO), std::logic_error);
        CHECK(venda.getStatusVenda() == StatusVenda::ENTREGUE);
    }
}

TEST_CASE("Gerente - atualizarStatusVenda nao envia pedido sem itens") {
    Gerente g = criarGerente();
    Venda vazia = criarVenda();

    CHECK_THROWS_AS(g.atualizarStatusVenda(vazia, StatusVenda::ENVIADO), std::logic_error);
    CHECK(vazia.getStatusVenda() == StatusVenda::PROCESSAMENTO);
}

TEST_CASE("Gerente - atualizarStatusPagamento altera apenas o pagamento") {
    Gerente g = criarGerente();
    Venda venda = criarVendaComItem();
    StatusVenda statusAntes = venda.getStatusVenda();

    SUBCASE("AGUARDANDO_PAGAMENTO -> PAGO") {
        CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);
        g.atualizarStatusPagamento(venda, StatusPagamento::PAGO);
        CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
    }
    SUBCASE("pagamento confirmado nao pode voltar") {
        g.atualizarStatusPagamento(venda, StatusPagamento::PAGO);
        CHECK_THROWS_AS(g.atualizarStatusPagamento(venda, StatusPagamento::AGUARDANDO_PAGAMENTO),
                        std::logic_error);
        CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
    }

    CHECK(venda.getStatusVenda() == statusAntes);
}

TEST_CASE("Gerente - atualizarStatusPagamento rejeita pedido cancelado ou sem itens") {
    Gerente g = criarGerente();

    SUBCASE("pedido cancelado") {
        Venda venda = criarVendaComItem();
        g.atualizarStatusVenda(venda, StatusVenda::CANCELADO);
        CHECK_THROWS_AS(g.atualizarStatusPagamento(venda, StatusPagamento::PAGO), std::logic_error);
        CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);
    }
    SUBCASE("pedido sem itens") {
        Venda vazia = criarVenda();
        CHECK_THROWS_AS(g.atualizarStatusPagamento(vazia, StatusPagamento::PAGO), std::logic_error);
    }
}

TEST_CASE("Gerente - cadastrarCupom cria o cupom com codigo, percentual e validade") {
    Gerente g = criarGerente();

    SUBCASE("caminho feliz") {
        Desconto cupom = g.cadastrarCupom("PRIMAVERA10", 10.0, "2099-12-31");

        CHECK(cupom.getCupom() == "PRIMAVERA10");
        CHECK(cupom.getPercentual() == doctest::Approx(10.0));
        CHECK(cupom.getDataValidade() == "2099-12-31");
        CHECK(cupom.aplicar(200.0) == doctest::Approx(180.0));
    }
    SUBCASE("limite inferior: 0% nao altera o valor") {
        Desconto cupom = g.cadastrarCupom("SEM_DESCONTO", 0.0, "2099-12-31");
        CHECK(cupom.aplicar(100.0) == doctest::Approx(100.0));
    }
    SUBCASE("limite superior: 100% zera o valor") {
        Desconto cupom = g.cadastrarCupom("GRATIS", 100.0, "2099-12-31");
        CHECK(cupom.aplicar(100.0) == doctest::Approx(0.0));
    }
    SUBCASE("cupom vencido nao concede desconto") {
        Desconto cupom = g.cadastrarCupom("VELHO", 10.0, "2000-01-01");
        CHECK_FALSE(cupom.ehValido());
        CHECK(cupom.aplicar(100.0) == doctest::Approx(100.0));
    }
}

TEST_CASE("Gerente - cadastrarCupom com percentual invalido lanca invalid_argument") {
    Gerente g = criarGerente();

    CHECK_THROWS_AS(g.cadastrarCupom("NEGATIVO", -10.0, "2099-12-31"), std::invalid_argument);
    CHECK_THROWS_AS(g.cadastrarCupom("ABSURDO", 150.0, "2099-12-31"), std::invalid_argument);
}

TEST_CASE("Gerente - aplicarCupomVenda reduz o valor dos produtos (o frete nao tem desconto)") {
    Gerente g = criarGerente();
    Venda venda = criarVendaComItem();               // produtos: 2 x 50.00 = 100.00
    double frete = venda.getValorTotal() - 100.0;    // total = produtos + frete

    SUBCASE("cupom de 10%") {
        g.aplicarCupomVenda(venda, Desconto("PRIMAVERA10", 10.0, "2099-12-31"));
        CHECK(venda.getValorTotal() == doctest::Approx(90.0 + frete));
        CHECK(venda.getDescontoAplicado().getCupom() == "PRIMAVERA10");
    }
    SUBCASE("cupom de 0% mantem o valor") {
        g.aplicarCupomVenda(venda, Desconto("SEM_DESCONTO", 0.0, "2099-12-31"));
        CHECK(venda.getValorTotal() == doctest::Approx(100.0 + frete));
    }
    SUBCASE("cupom vencido mantem o valor") {
        g.aplicarCupomVenda(venda, Desconto("VELHO", 10.0, "2000-01-01"));
        CHECK(venda.getValorTotal() == doctest::Approx(100.0 + frete));
    }
}