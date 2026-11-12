#include "doctest.h"
#include "Desconto.hpp"
#include <stdexcept>
#include <ctime>
#include <string>

static std::string hoje(){
    std::time_t agora = std::time(nullptr);
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&agora));
    return buf;
}

TEST_CASE("Data de validade invalida gera excecao no construtor"){
    for(const char* data : {"31-12-2100", "2100/12/31", "2100-12/31", "2100-1-01", "2100-12-311",
                            "", "abcd-ef-gh", "2100-1a-10", "0000-12-10",
                            "2100-00-10", "2100-13-10", "2100-12-00", "2100-12-32"}){
        CAPTURE(data);
        CHECK_THROWS_AS(Desconto("FLORES10", 10.0, data), std::invalid_argument);
    }
}

TEST_CASE("Getters devolvem os dados do cupom"){
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.getCupom() == "FLORES10");
    CHECK(d.getPercentual() == doctest::Approx(10.0));
    CHECK(d.getDataValidade() == "2100-12-31");
}

TEST_CASE("Construtor padrao cria desconto vazio e invalido"){
    Desconto d;
    CHECK(d.getPercentual() == doctest::Approx(0.0));
    CHECK(d.getDataValidade() == "");
    CHECK(d.ehValido() == false);
}

TEST_CASE("Cupom que vence hoje ainda e valido"){
    Desconto d("HOJE", 10.0, hoje());
    CHECK(d.ehValido() == true);
    CHECK(d.aplicar(100.0) == doctest::Approx(90.0));
}

TEST_CASE("Limites do percentual: 0 e 100 sao aceitos"){
    CHECK(Desconto("ZERO", 0.0, "2100-12-31").aplicar(80.0) == doctest::Approx(80.0));
    CHECK(Desconto("TUDO", 100.0, "2100-12-31").aplicar(80.0) == doctest::Approx(0.0));
}

TEST_CASE("Aplicar sobre total zero devolve zero"){
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.aplicar(0.0) == doctest::Approx(0.0));
}

TEST_CASE("Pedido sem desconto continua com o mesmo valor"){
    Desconto d;
    CHECK(d.getCupom() == "");
    CHECK(d.aplicar(100.0) == doctest::Approx(100.0));
}

TEST_CASE("Cupom dentro da validade sera aplicado") {
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.ehValido() == true);
    CHECK(d.aplicar(100.0) == doctest::Approx(90.0));
}

TEST_CASE("Cupom vencido nao da desconto") {
    Desconto d("FLORES10", 10.0, "2000-01-01");
    CHECK(d.ehValido() == false);
    CHECK(d.aplicar(100.0) == doctest::Approx(100.0));
}

TEST_CASE("Desconto de 10%"){
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.getCupom() == "FLORES10");
    CHECK(d.aplicar(100.0) == doctest::Approx(90.0));
}

TEST_CASE("Desconto de 50%"){
    Desconto d("FLORES50", 50.0, "2100-12-31");
    CHECK(d.getCupom() == "FLORES50");
    CHECK(d.aplicar(200.0) == doctest::Approx(100.0));
}

TEST_CASE("Porcentagem maior que 100 gera excecao"){
    CHECK_THROWS_AS(
        Desconto("FLORES150", 150.0, "2100-12-31"),
        std::invalid_argument
    );
}

TEST_CASE("Porcentagem negativa gera excecao"){
    CHECK_THROWS_AS(
        Desconto("FLORESN", -10.0, "2100-12-31"),
        std::invalid_argument
    );
}

TEST_CASE("Total negativo gera excecao"){
    Desconto d("FLORES10", 10.0, "2100-12-31");

    CHECK_THROWS_AS(
        d.aplicar(-100.0),
        std::invalid_argument
    );
}