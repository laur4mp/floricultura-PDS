#include "doctest.h"
#include <stdexcept>
#include "Venda.hpp"
#include "Endereco.hpp"
#include "ItemPedido.hpp"
#include "Desconto.hpp"
#include "Produto.hpp"


namespace {
Endereco enderecoMaria() {
    return Endereco("Maria Silva", "30100000", "Rua das Flores", "123", "Centro", "Apt 101", "Belo Horizonte", "MG");
}
Endereco enderecoSP() {
    return Endereco("Maria Silva", "01310100", "Av. Paulista", "900", "Bela Vista", "", "Sao Paulo", "SP");
}
Produto rosa()     { return Produto(1, "Rosas", "Rosa vermelha", "Flores", 15.0, "img/rosa.png", 50, 10); }
Produto orquidea() { return Produto(2, "Orquidea", "Orquidea roxa", "Exoticas", 40.0, "img/orq.png", 20, 5); }

Venda vendaComItens(int id = 1) {
    Venda v(id, 7, 0, enderecoMaria(), "Maria Silva");
    v.adicionarItem(ItemPedido(rosa(), 2));
    return v;
}
}

TEST_CASE("Venda: construtor e getters") {
    Venda venda(1, 7, 0, enderecoMaria(), "Maria Silva");
    CHECK(venda.getIdVenda() == 1);
    CHECK(venda.getIdPessoa() == 7);
    CHECK(venda.getNomeDestina() == "Maria Silva");
    CHECK(venda.getAvaliacao() == 0);
    CHECK(venda.getValorTotal() == 0.0);
    CHECK(venda.getItens().empty());
    CHECK(venda.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);
    CHECK(venda.getEnderecoEntrega().getCep() == "30100000");
}

TEST_CASE("Venda: construtor padrao inicializa tudo") {
    Venda venda;
    CHECK(venda.getIdVenda() == 0);
    CHECK(venda.getIdPessoa() == 0);
    CHECK(venda.getAvaliacao() == 0);
    CHECK(venda.getValorTotal() == 0.0);
}

TEST_CASE("Venda: construtor recusa dados invalidos") {
    CHECK_THROWS_AS(Venda(0, 7, 0, enderecoMaria(), "Maria"), std::invalid_argument);
    CHECK_THROWS_AS(Venda(1, 0, 0, enderecoMaria(), "Maria"), std::invalid_argument);
    CHECK_THROWS_AS(Venda(1, 7, 0, enderecoMaria(), ""),      std::invalid_argument);
    // venda nova nao pode nascer avaliada
    CHECK_THROWS_AS(Venda(1, 7, 5, enderecoMaria(), "Maria"), std::logic_error);
    CHECK(Venda(1, 7, 5, enderecoMaria(), "Maria").getAvaliacao() == 0);
}

TEST_CASE("Venda: data e horario") {
    Venda venda(2, 7, 0, enderecoMaria(), "Maria Silva");
    venda.setDataEntrega("2026-10-25");

    venda.setHorarioEntregaPrevisao("14:00 - 18:00");
    CHECK(venda.getDataEntrega() == "2026-10-25");
    CHECK(venda.getHorarioEntregaPrevisao() == "14:00 - 18:00");

    CHECK_THROWS_AS(venda.setDataEntrega(""), std::invalid_argument);
    CHECK_THROWS_AS(venda.setHorarioEntregaPrevisao(""), std::invalid_argument);
}

TEST_CASE("Venda: adicionar e remover itens atualiza o total") {
    Venda venda(3, 7, 0, enderecoMaria(), "Maria Silva");

    venda.adicionarItem(ItemPedido(rosa(), 2));
    double comUmItem = venda.getValorTotal();
    CHECK(comUmItem > 0.0);

    venda.adicionarItem(ItemPedido(orquidea(), 1));
    CHECK(venda.getItens().size() == 2);
    CHECK(venda.getValorTotal() == doctest::Approx(comUmItem + 40.0));  // frete cobrado uma vez so

    CHECK(venda.removerItem(2) == true);
    CHECK(venda.getItens().size() == 1);
    CHECK(venda.getValorTotal() == doctest::Approx(comUmItem));

    CHECK(venda.removerItem(99) == false);   // produto que nao esta no pedido
    CHECK_THROWS_AS(venda.removerItem(0), std::invalid_argument);
    CHECK_THROWS_AS(venda.adicionarItem(ItemPedido(rosa(), 0)), std::invalid_argument);
}

TEST_CASE("Venda: trocar o endereco recalcula o total") {
    Venda venda = vendaComItens();
    venda.setEnderecoEntrega(enderecoSP());

    // mesma venda criada direto com o endereco de SP deve ter o mesmo total
    Venda referencia(9, 7, 0, enderecoSP(), "Maria Silva");
    referencia.adicionarItem(ItemPedido(rosa(), 2));

    CHECK(venda.getEnderecoEntrega().getEstado() == "SP");
    CHECK(venda.getValorTotal() == doctest::Approx(referencia.getValorTotal()));
}

TEST_CASE("Venda: cupom reduz o subtotal") {
    Venda semCupom = vendaComItens(1);
    Venda comCupom = vendaComItens(2);
    comCupom.aplicarCupom(Desconto("FLOR10", 10.0, "2099-12-31"));

    // 2 rosas = 30.00; 10% de desconto = 3.00 (o frete nao muda)
    CHECK(comCupom.getValorTotal() == doctest::Approx(semCupom.getValorTotal() - 3.0));
    CHECK(comCupom.getDescontoAplicado().getCupom() == "FLOR10");
}

TEST_CASE("Venda: fluxo normal de status") {
    Venda venda = vendaComItens();
    venda.atualizarSvenda(StatusVenda::ENVIADO);
    CHECK(venda.getStatusVenda() == StatusVenda::ENVIADO);
    CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);

    venda.atualizarSvenda(StatusVenda::ENTREGUE);
    CHECK(venda.getStatusVenda() == StatusVenda::ENTREGUE);
    CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);  // pagamento na entrega
}

TEST_CASE("Venda: transicoes de status invalidas") {
    Venda vazia(1, 7, 0, enderecoMaria(), "Maria Silva");
    CHECK_THROWS_AS(vazia.atualizarSvenda(StatusVenda::ENVIADO), std::logic_error);   // sem itens

    Venda venda = vendaComItens();
    CHECK_THROWS_AS(venda.atualizarSvenda(StatusVenda::ENTREGUE), std::logic_error);  // sem ter sido enviada

    venda.atualizarSvenda(StatusVenda::ENVIADO);
    CHECK_THROWS_AS(venda.atualizarSvenda(StatusVenda::PROCESSAMENTO), std::logic_error);

    Venda cancelada = vendaComItens(2);
    cancelada.atualizarSvenda(StatusVenda::CANCELADO);
    CHECK_THROWS_AS(cancelada.atualizarSvenda(StatusVenda::ENVIADO), std::logic_error);  // finalizada
}

TEST_CASE("Venda: regras do pagamento") {
    Venda vazia(1, 7, 0, enderecoMaria(), "Maria Silva");
    CHECK_THROWS_AS(vazia.atualizarSpagamento(StatusPagamento::PAGO), std::logic_error);

    Venda venda = vendaComItens();
    venda.atualizarSpagamento(StatusPagamento::PAGO);
    CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
    CHECK_THROWS_AS(venda.atualizarSpagamento(StatusPagamento::AGUARDANDO_PAGAMENTO), std::logic_error);

    Venda cancelada = vendaComItens(2);
    cancelada.atualizarSvenda(StatusVenda::CANCELADO);
    CHECK_THROWS_AS(cancelada.atualizarSpagamento(StatusPagamento::PAGO), std::logic_error);
}

TEST_CASE("Venda: avaliacao so depois da entrega") {
    Venda venda = vendaComItens();
    CHECK_THROWS_AS(venda.avaliar(5), std::logic_error);   // ainda em processamento

    venda.atualizarSvenda(StatusVenda::ENVIADO);
    CHECK_THROWS_AS(venda.avaliar(5), std::logic_error);   // enviada, mas nao entregue

    venda.atualizarSvenda(StatusVenda::ENTREGUE);
    CHECK_THROWS_AS(venda.avaliar(0), std::invalid_argument);
    CHECK_THROWS_AS(venda.avaliar(6), std::invalid_argument);

    venda.avaliar(4);
    CHECK(venda.getAvaliacao() == 4);
}

TEST_CASE("Venda: remover todos os itens zera o total") {
    Venda venda = vendaComItens();
    CHECK(venda.removerItem(1) == true);
    CHECK(venda.getItens().empty());
    CHECK(venda.getValorTotal() == doctest::Approx(0.0));   // sem itens nao ha frete
    CHECK(venda.removerItem(1) == false);
}

TEST_CASE("Venda: cupom aplicado antes dos itens vale para os itens seguintes") {
    Venda semCupom = vendaComItens(1);
    Venda comCupom(2, 7, 0, enderecoMaria(), "Maria Silva");
    comCupom.aplicarCupom(Desconto("FLOR10", 10.0, "2099-12-31"));
    CHECK(comCupom.getValorTotal() == doctest::Approx(0.0));
    comCupom.adicionarItem(ItemPedido(rosa(), 2));
    CHECK(comCupom.getValorTotal() == doctest::Approx(semCupom.getValorTotal() - 3.0));
}

TEST_CASE("Venda: cupom vencido nao altera o total e cupom novo substitui o anterior") {
    Venda semCupom = vendaComItens(1);
    Venda venda = vendaComItens(2);

    venda.aplicarCupom(Desconto("VELHO", 50.0, "2000-01-01"));
    CHECK(venda.getValorTotal() == doctest::Approx(semCupom.getValorTotal()));

    venda.aplicarCupom(Desconto("FLOR10", 10.0, "2099-12-31"));
    venda.aplicarCupom(Desconto("FLOR20", 20.0, "2099-12-31"));  
    CHECK(venda.getValorTotal() == doctest::Approx(semCupom.getValorTotal() - 6.0));
    CHECK(venda.getDescontoAplicado().getCupom() == "FLOR20");
}

TEST_CASE("Venda: repetir o status atual nao faz nada") {
    Venda venda = vendaComItens();
    CHECK_NOTHROW(venda.atualizarSvenda(StatusVenda::PROCESSAMENTO));
    CHECK_NOTHROW(venda.atualizarSpagamento(StatusPagamento::AGUARDANDO_PAGAMENTO));

    venda.atualizarSvenda(StatusVenda::CANCELADO);
    CHECK_NOTHROW(venda.atualizarSvenda(StatusVenda::CANCELADO)); 

    Venda vazia(3, 7, 0, enderecoMaria(), "Maria Silva");
    CHECK_NOTHROW(vazia.atualizarSpagamento(StatusPagamento::AGUARDANDO_PAGAMENTO));
}

TEST_CASE("Venda: pedido enviado pode ser cancelado; entregue nao muda mais") {
    Venda enviada = vendaComItens(1);
    enviada.atualizarSvenda(StatusVenda::ENVIADO);
    enviada.atualizarSvenda(StatusVenda::CANCELADO);
    CHECK(enviada.getStatusVenda() == StatusVenda::CANCELADO);

    Venda entregue = vendaComItens(2);
    entregue.atualizarSvenda(StatusVenda::ENVIADO);
    entregue.atualizarSvenda(StatusVenda::ENTREGUE);
    CHECK_THROWS_AS(entregue.atualizarSvenda(StatusVenda::CANCELADO), std::logic_error);
    CHECK_THROWS_AS(entregue.atualizarSvenda(StatusVenda::ENVIADO), std::logic_error);
    // entrega marcou PAGO e pagamento confirmado nao volta
    CHECK_THROWS_AS(entregue.atualizarSpagamento(StatusPagamento::AGUARDANDO_PAGAMENTO), std::logic_error);
}

TEST_CASE("Venda: pedido pago antes continua pago ate a entrega") {
    Venda venda = vendaComItens();
    venda.atualizarSpagamento(StatusPagamento::PAGO);
    venda.atualizarSvenda(StatusVenda::ENVIADO);
    venda.atualizarSvenda(StatusVenda::ENTREGUE);
    CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
}

TEST_CASE("Venda: avaliacao pode ser refeita e pedido cancelado nao e avaliado") {
    Venda venda = vendaComItens(1);
    venda.atualizarSvenda(StatusVenda::ENVIADO);
    venda.atualizarSvenda(StatusVenda::ENTREGUE);
    venda.avaliar(1);
    venda.avaliar(5);                       
    CHECK(venda.getAvaliacao() == 5);

    Venda cancelada = vendaComItens(2);
    cancelada.atualizarSvenda(StatusVenda::CANCELADO);
    CHECK_THROWS_AS(cancelada.avaliar(5), std::logic_error);
}