#include "doctest.h"
#include "Venda.hpp"
#include "Endereco.hpp"
#include "ItemPedido.hpp"
#include "Desconto.hpp"

TEST_CASE("Construtores e  da classe Venda") {
    Endereco end("Maria Silva", "30100-000", "Rua das Flores", "123", "Centro", "Apt 101", "Belo Horizonte", "MG");
    Venda venda(1, "123.456.789-00", end, "Maria Silva");
    //getters
    CHECK(venda.getIdVenda() == 1);
    CHECK(venda.getCpfCliente() == "123.456.789-00");
    CHECK(venda.getNomeDestina() == "Maria Silva");
    CHECK(venda.getValorTotal() == 0.0);
    CHECK(venda.getStatusVenda() == StatusVenda::PROCESSAMENTO);
    CHECK(venda.getStatusPagamento() == StatusPagamento::AGUARDANDO_PAGAMENTO);
}

TEST_CASE("Atualização de conteudos da compra") {
    Endereco end1("Carlos Alberto", "30160-010", "Rua da Bahia", "500", "Funcionários", "Sala 1", "Belo Horizonte", "MG");
    Endereco end2("Carlos Alberto", "30130-005", "Av. Afonso Pena", "1500", "Centro", "Loja 2", "Belo Horizonte", "MG");
    Venda venda(2, "987.654.321-11", end1, "Carlos Alberto");

    //modificação de morada de entrega
    venda.setEnderecoEntrega(end2);
    //verifica datas e horários previsto
    venda.setDataEntrega("2026-10-25");
    CHECK(venda.getDataEntrega() == "2026-10-25");
    
    venda.setHorarioEntregaPrevisao("14:00 - 18:00");
    CHECK(venda.getHorarioEntregaPrevisao() == "14:00 - 18:00");

    //alteração de estados da venda e do pagamento
    venda.atualizarSvenda(StatusVenda::ENVIADO);
    CHECK(venda.getStatusVenda() == StatusVenda::ENVIADO);
    venda.atualizarSpagamento(StatusPagamento::PAGO);
    CHECK(venda.getStatusPagamento() == StatusPagamento::PAGO);
}

TEST_CASE("Modificar itens e cálculo do total da venda") {
    Endereco end("Ana Clara", "30130-000", "Rua Sergipe", "1000", "Savassi", "", "Belo Horizonte", "MG");
    Venda venda(3, "111.222.333-44", end, "Ana Clara");

    CHECK(venda.getItens().empty() == true); //criar nova venda ela ta vazia de inicio
    CHECK(venda.getValorTotal() == 0.0);

}