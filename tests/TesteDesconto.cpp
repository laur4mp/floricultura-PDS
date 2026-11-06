#include "doctest.h"
#include "Desconto.hpp"
#include <stdexcept>

TEST_CASE("Data com formato errado nao valida o cupom"){
    Desconto d("FLORES10", 10.0, "31-12-2100");
    CHECK(d.ehValido() == false);
}

TEST_CASE("Data com mes invalido nao valida o cupom"){
    Desconto d("FLORES10", 10.0, "2100-15-10");
    CHECK(d.ehValido() == false);
}

TEST_CASE("Data com dia invalido nao valida o cupom"){
    Desconto d("FLORES10", 10.0, "2100-12-32");
    CHECK(d.ehValido() == false);
}

TEST_CASE("Pedido sem desconto continua com o mesmo valor"){
    Desconto d;
    CHECK(d.getCupom() == "");
    CHECK(d.aplicar(100.0) == 100.0);
}

TEST_CASE("Cupom dentro da validade sera aplicado") {
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.ehValido() == true);
    CHECK(d.aplicar(100.0) == 90.0);
}

TEST_CASE("Cupom vencido nao da desconto") {
    Desconto d("FLORES10", 10.0, "2000-01-01");
    CHECK(d.ehValido() == false);
    CHECK(d.aplicar(100.0) == 100.0);
}

TEST_CASE("Desconto de 10%"){
    Desconto d("FLORES10", 10.0, "2100-12-31");
    CHECK(d.getCupom() == "FLORES10");
    CHECK(d.aplicar(100.0) == 90.0);
}

TEST_CASE("Desconto de 50%"){
    Desconto d("FLORES50", 50.0, "2100-12-31");
    CHECK(d.getCupom() == "FLORES50");
    CHECK(d.aplicar(200.0) == 100.0);
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