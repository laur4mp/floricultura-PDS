#include "doctest.h"
#include "Endereco.hpp"

TEST_CASE("setCep valida 8 digitos"){
    Endereco e("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG");
    CHECK(e.setCep("12345678") == true);
    CHECK(e.setCep("") == false);
    CHECK(e.setCep("123") == false);
    CHECK(e.setCep("a1234567") == false);
    CHECK(e.setCep("123456789") == false);
}

TEST_CASE("setEstado aceita as siglas validas"){
    Endereco e("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG");
    for(const char* sigla : {"AC", "AP", "AM", "PA", "RO", "RR", "TO", "AL", "BA", "CE", "MA", "PB",
                            "PE", "PI", "RN", "SE", "MT", "MS", "GO", "DF", "MG", "ES", "SP", "RJ",
                            "PR", "SC", "RS"}){
        CHECK(e.setEstado(sigla) == true);
    }
    CHECK(e.setEstado("XX") == false);
}

TEST_CASE("regiao"){
    Endereco e("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG");
    for(const char* n : {"AC", "AP", "AM", "PA", "RO", "RR", "TO"}){
        e.setEstado(n);
        CHECK(e.regiao() == "Norte");
    }

    for(const char* ne : {"AL", "BA", "CE", "MA", "PB", "PE", "PI", "RN", "SE"}){
        e.setEstado(ne);
        CHECK(e.regiao() == "Nordeste");
    }
    
    for(const char* co : {"MT", "MS", "GO", "DF"}){
        e.setEstado(co);
        CHECK(e.regiao() == "Centro-Oeste");
    }

    for(const char* se : {"MG", "ES", "SP", "RJ"}){
        e.setEstado(se);
        CHECK(e.regiao() == "Sudeste");
    }

    for(const char* s : {"PR", "SC", "RS"}) {
        e.setEstado(s);
        CHECK(e.regiao() == "Sul");
    }
}

TEST_CASE("formatarEndereco sem complemento"){
    Endereco f("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG");
    CHECK(f.formatarEndereco() == "Rua das Flores, 10 - Planalto, Belo Horizonte - MG, CEP 31250000");
}

TEST_CASE("formatarEndereco com complemento") {
    Endereco f("Ana", "31250000", "Rua das Flores", "10", "Planalto", "Casa", "Belo Horizonte", "MG");
    CHECK(f.formatarEndereco() == "Rua das Flores, 10 - Casa - Planalto, Belo Horizonte - MG, CEP 31250000");
}