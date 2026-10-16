#include "doctest.h"
#include "Desconto.hpp"

TEST_CASE("Pedido sem desconto continua com o mesmo valor"){
    Desconto d;
    CHECK(d.getCupom() == "");
    CHECK(d.aplicar(100.0) == 100.0);
}

TEST_CASE("Desconto de 10%"){
    Desconto d("FLORES10", 10.0);
    CHECK(d.getCupom() == "FLORES10");
    CHECK(d.aplicar(100.0) == 90.0);
}

TEST_CASE("Desconto de 50%"){
    Desconto d("FLORES50", 50.0);
    CHECK(d.getCupom() == "FLORES50");
    CHECK(d.aplicar(200.0) == 100.0);
}

TEST_CASE("Porcentagem maior que 100 vira zero"){
    Desconto d("FLORES150", 150.0);
    CHECK(d.aplicar(100.0) == 100.0);
}

TEST_CASE("Porcentagem negativa vira zero"){
    Desconto d("FLORESMENOS", -10.0);
    CHECK(d.aplicar(100.0) == 100.0);
}