#include "doctest.h"
#include "Endereco.hpp"
#include <stdexcept>

TEST_CASE("Endereco com CEP invalido gera excecao"){
    CHECK_THROWS_AS(
        Endereco("Ana", "123", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG"),
        std::invalid_argument
    );
}

TEST_CASE("Endereco com numero invalido gera excecao"){
    CHECK_THROWS_AS(
        Endereco("Ana", "31250000", "Rua das Flores", "a1", "Planalto", "", "Belo Horizonte", "MG"),
        std::invalid_argument
    );
}

TEST_CASE("Endereco com estado invalido gera excecao"){
    CHECK_THROWS_AS(
        Endereco("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "XX"),
        std::invalid_argument
    );
}

TEST_CASE("Endereco sem cidade gera excecao"){
    CHECK_THROWS_AS(
        Endereco("Ana", "31250000", "Rua das Flores", "10", "Planalto", "", "", "MG"),
        std::invalid_argument
    );
}

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

TEST_CASE("Construtor valido preenche todos os getters"){
    Endereco e("Taylor Swift", "31250000", "Rua das Flores", "10", "Planalto", "Casa", "Belo Horizonte", "MG");
    CHECK(e.getNomeDest() == "Taylor Swift");
    CHECK(e.getCep() == "31250000");
    CHECK(e.getRua() == "Rua das Flores");
    CHECK(e.getNumero() == "10");
    CHECK(e.getBairro() == "Planalto");
    CHECK(e.getComplemento() == "Casa");
    CHECK(e.getCidade() == "Belo Horizonte");
    CHECK(e.getEstado() == "MG");
}

TEST_CASE("Campos obrigatorios vazios geram excecao"){
    CHECK_THROWS_AS(Endereco("", "31250000", "Rua", "10", "Bairro", "", "BH", "MG"), std::invalid_argument);
    CHECK_THROWS_AS(Endereco("Taylor", "31250000", "", "10", "Bairro", "", "BH", "MG"), std::invalid_argument);
    CHECK_THROWS_AS(Endereco("Taylor", "31250000", "Rua", "", "Bairro", "", "BH", "MG"), std::invalid_argument);
    CHECK_THROWS_AS(Endereco("Taylor", "31250000", "Rua", "10", "", "", "BH", "MG"), std::invalid_argument);
    CHECK_NOTHROW(Endereco("Taylor", "31250000", "Rua", "10", "Bairro", "", "BH", "MG"));  
}

TEST_CASE("CEP com hifen e estado em minusculas sao rejeitados"){
    CHECK_THROWS_AS(Endereco("Taylor Swift", "31250-000", "Rua", "10", "Bairro", "", "BH", "MG"), std::invalid_argument);
    CHECK_THROWS_AS(Endereco("Taylor Swift", "31250000", "Rua", "10", "Bairro", "", "BH", "mg"), std::invalid_argument);
    CHECK_THROWS_AS(Endereco("Taylor Swift", "31250000", "Rua", "10", "Bairro", "", "BH", ""), std::invalid_argument);
}

TEST_CASE("Setter que falha mantem o valor anterior"){
    Endereco e("Taylor Swift", "31250000", "Rua das Flores", "10", "Planalto", "", "Belo Horizonte", "MG");
    CHECK(e.setCep("123") == false);
    CHECK(e.getCep() == "31250000");
    CHECK(e.setEstado("XX") == false);
    CHECK(e.getEstado() == "MG");

    CHECK(e.setCep("01310100") == true);
    CHECK(e.getCep() == "01310100");
    CHECK(e.setEstado("SP") == true);
    CHECK(e.getEstado() == "SP");
}

TEST_CASE("Construtor padrao cria endereco vazio"){
    Endereco e;
    CHECK(e.getCep().empty());
    CHECK(e.getEstado().empty());
    CHECK(e.regiao() == "Estado invalido");
}