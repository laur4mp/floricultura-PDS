#include "doctest.h"
#include <stdexcept>
#include "VendaRepositorio.hpp"
#include <cstdio>
#include <fstream>

namespace {
struct ArquivoTemp {
    std::string caminho;
    explicit ArquivoTemp(const std::string& c) : caminho(c) { std::remove(caminho.c_str()); }
    ~ArquivoTemp() { std::remove(caminho.c_str()); }
};

Endereco enderecoAna() {
    return Endereco("Ana Clara", "30130000", "Rua Sergipe", "1000", "Savassi", "Apt 2", "Belo Horizonte", "MG");
}

Produto rosa()    { return Produto(1, "Rosas", "Rosa vermelha", "Flores", 15.0, "img/rosa.png", 50, 10); }
Produto orquidea(){ return Produto(2, "Orquidea", "Orquidea roxa", "Exoticas", 40.0, "img/orq.png", 20, 5); }

// Venda com dois itens, ainda em processamento
Venda vendaBase(int id) {
    Venda v(id, 7, 0, enderecoAna());
    v.adicionarItem(ItemPedido(rosa(), 3));
    v.adicionarItem(ItemPedido(orquidea(), 1));
    return v;
}
}

TEST_CASE("VendaRepositorio: arquivo inexistente devolve lista vazia") {
    ArquivoTemp arq("teste_vendas_inexistente.txt");
    VendaRepositorio repo(arq.caminho);
    CHECK(repo.carregar().empty());
}

TEST_CASE("VendaRepositorio: gravar e carregar reconstroi itens, endereco e datas") {
    ArquivoTemp arq("teste_vendas.txt");
    VendaRepositorio repo(arq.caminho);

    Venda original = vendaBase(1);
    original.setDataEntrega("2026-11-20");
    original.setHorarioEntregaPrevisao("Entre 08:00 e 18:00");
    repo.gravar({ original });

    std::vector<Venda> lidas = repo.carregar();
    REQUIRE(lidas.size() == 1);
    const Venda& v = lidas[0];

    CHECK(v.getIdVenda() == 1);
    CHECK(v.getIdPessoa() == 7);
    CHECK(v.getEnderecoEntrega().getNomeDest() == "Ana Clara");
    CHECK(v.getDataEntrega() == "2026-11-20");
    CHECK(v.getHorarioEntregaPrevisao() == "Entre 08:00 e 18:00");

    // itens
    REQUIRE(v.getItens().size() == 2);
    CHECK(v.getItens()[0].getProduto().getNome() == "Rosas");
    CHECK(v.getItens()[0].getQuantidade() == 3);
    CHECK(v.getItens()[1].getProduto().getIdProduto() == 2);
    CHECK(v.getItens()[1].getQuantidade() == 1);

    // endereco
    const Endereco& e = v.getEnderecoEntrega();
    CHECK(e.getCep() == "30130000");
    CHECK(e.getRua() == "Rua Sergipe");
    CHECK(e.getNumero() == "1000");
    CHECK(e.getComplemento() == "Apt 2");
    CHECK(e.getCidade() == "Belo Horizonte");
    CHECK(e.getEstado() == "MG");

    // total recalculado ao ler deve bater com o original
    CHECK(v.getValorTotal() == doctest::Approx(original.getValorTotal()));
}

TEST_CASE("VendaRepositorio: item guarda o preco da epoca da venda") {
    ArquivoTemp arq("teste_vendas_preco.txt");
    VendaRepositorio repo(arq.caminho);

    Produto p = rosa();                       // preco 15
    Venda v(1, 7, 0, enderecoAna());
    v.adicionarItem(ItemPedido(p, 2));
    repo.gravar({ v });

    p.setPreco(99.0);                         // o catalogo muda depois da venda

    std::vector<Venda> lidas = repo.carregar();
    REQUIRE(lidas.size() == 1);
    CHECK(lidas[0].getItens()[0].getProduto().getPreco() == doctest::Approx(15.0));
}

TEST_CASE("VendaRepositorio: cupom aplicado e restaurado") {
    ArquivoTemp arq("teste_vendas_cupom.txt");
    VendaRepositorio repo(arq.caminho);

    Venda original = vendaBase(1);
    original.aplicarCupom(Desconto("FLOR10", 10.0, "2099-12-31"));
    repo.gravar({ original });

    std::vector<Venda> lidas = repo.carregar();
    REQUIRE(lidas.size() == 1);
    CHECK(lidas[0].getDescontoAplicado().getCupom() == "FLOR10");
    CHECK(lidas[0].getDescontoAplicado().getPercentual() == doctest::Approx(10.0));
    CHECK(lidas[0].getValorTotal() == doctest::Approx(original.getValorTotal()));
}

TEST_CASE("VendaRepositorio: status sao restaurados pelas transicoes normais") {
    ArquivoTemp arq("teste_vendas_status.txt");
    VendaRepositorio repo(arq.caminho);

    Venda processando = vendaBase(1);

    Venda paga = vendaBase(2);
    paga.atualizarSpagamento(StatusPagamento::PAGO);

    Venda enviada = vendaBase(3);
    enviada.atualizarSvenda(StatusVenda::ENVIADO);

    Venda entregue = vendaBase(4);
    entregue.atualizarSvenda(StatusVenda::ENVIADO);
    entregue.atualizarSvenda(StatusVenda::ENTREGUE);
    entregue.avaliar(4);

    Venda cancelada = vendaBase(5);
    cancelada.atualizarSvenda(StatusVenda::CANCELADO);

    repo.gravar({ processando, paga, enviada, entregue, cancelada });
    std::vector<Venda> lidas = repo.carregar();
    REQUIRE(lidas.size() == 5);

    CHECK(lidas[0].getStatusVenda() == StatusVenda::PROCESSAMENTO);
    CHECK(lidas[0].getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);

    CHECK(lidas[1].getStatusVenda() == StatusVenda::PROCESSAMENTO);
    CHECK(lidas[1].getStatusPagamento() == StatusPagamento::PAGO);

    CHECK(lidas[2].getStatusVenda() == StatusVenda::ENVIADO);

    CHECK(lidas[3].getStatusVenda() == StatusVenda::ENTREGUE);
    CHECK(lidas[3].getStatusPagamento() == StatusPagamento::PAGO);
    CHECK(lidas[3].getAvaliacao() == 4);

    CHECK(lidas[4].getStatusVenda() == StatusVenda::CANCELADO);
    CHECK(lidas[4].getAvaliacao() == 0);
}

TEST_CASE("VendaRepositorio: itens de uma venda nao vazam para a proxima") {
    ArquivoTemp arq("teste_vendas_itens.txt");
    VendaRepositorio repo(arq.caminho);

    Venda v1 = vendaBase(1);                               // 2 itens
    Venda v2(2, 8, 0, enderecoAna());
    v2.adicionarItem(ItemPedido(orquidea(), 5));           // 1 item
    repo.gravar({ v1, v2 });

    std::vector<Venda> lidas = repo.carregar();
    REQUIRE(lidas.size() == 2);
    CHECK(lidas[0].getItens().size() == 2);
    REQUIRE(lidas[1].getItens().size() == 1);
    CHECK(lidas[1].getItens()[0].getQuantidade() == 5);
}

TEST_CASE("VendaRepositorio: linha corrompida lanca excecao") {
    ArquivoTemp arq("teste_vendas_corrompido.txt");
    {
        std::ofstream out(arq.caminho);
        out << "X|isso nao e uma venda\n";
    }
    VendaRepositorio repo(arq.caminho);
    CHECK_THROWS_AS(repo.carregar(), std::runtime_error);
}

TEST_CASE("VendaRepositorio: avaliacao em venda nao entregue e recusada ao carregar") {
    ArquivoTemp arq("teste_vendas_avaliacao.txt");
    {
        std::ofstream out(arq.caminho);
        out << "I|1|Rosas|desc|Flores|15.000000|img.png|50|10|2\n";
        // statusVenda 0 (PROCESSAMENTO) com nota 5
      out << "V|1|7|0|0|||Ana Clara|30130000|Rua Sergipe|1000|Savassi||Belo Horizonte|MG||0.000000|5\n";
    }
    VendaRepositorio repo(arq.caminho);
    CHECK_THROWS(repo.carregar());
}