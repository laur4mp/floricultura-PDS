#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "doctest.h"
#include "Endereco.hpp"
#include "Pessoa.hpp"

namespace {

Pessoa criarPessoa() {
    return Pessoa(7, "Ana Souza", "529.982.247-25", "ana@email.com", "(31) 99999-0000", "senha123");
}

Endereco criarEndereco(const std::string& rua) {
    return Endereco("Maria Silva", "30130-000", rua, "100", "Centro", "Apto 2", "Belo Horizonte", "MG");
}

}  // namespace

#include "doctest.h"


TEST_CASE("Pessoa - construtor com dados armazena todos os atributos") {
    Pessoa p(7, "Ana Souza", "529.982.247-25", "ana@email.com", "(31) 99999-0000", "senha123");

    CHECK(p.getIdPessoa() == 7);
    CHECK(p.getNome() == "Ana Souza");
    CHECK(p.getCpf() == "529.982.247-25");
    CHECK(p.getEmail() == "ana@email.com");
    CHECK(p.getTelefone() == "(31) 99999-0000");
    CHECK(p.getSenha() == "senha123");
}

TEST_CASE("Pessoa - construtor padrao inicia com valores vazios") {
    Pessoa p;

    CHECK(p.getIdPessoa() == 0);
    CHECK(p.getNome().empty());
    CHECK(p.getCpf().empty());
    CHECK(p.getEmail().empty());
    CHECK(p.getTelefone().empty());
    CHECK(p.getSenha().empty());
    CHECK(p.getEnderecos().empty());
}

TEST_CASE("Pessoa - setters atualizam apenas o atributo correspondente") {
    Pessoa p = criarPessoa();

    SUBCASE("setNome") {
        p.setNome("Ana Maria Souza");
        CHECK(p.getNome() == "Ana Maria Souza");
        CHECK(p.getCpf() == "529.982.247-25");
    }
    SUBCASE("setCpf") {
        p.setCpf("111.444.777-35");
        CHECK(p.getCpf() == "111.444.777-35");
        CHECK(p.getNome() == "Ana Souza");
    }
    SUBCASE("setEmail") {
        p.setEmail("nova@email.com");
        CHECK(p.getEmail() == "nova@email.com");
        CHECK(p.getTelefone() == "(31) 99999-0000");
    }
    SUBCASE("setTelefone") {
        p.setTelefone("(31) 3333-4444");
        CHECK(p.getTelefone() == "(31) 3333-4444");
        CHECK(p.getEmail() == "ana@email.com");
    }
    SUBCASE("setSenha") {
        p.setSenha("outraSenha");
        CHECK(p.getSenha() == "outraSenha");
        CHECK(p.getNome() == "Ana Souza");
    }

    CHECK(p.getIdPessoa() == 7);
}

TEST_CASE("Pessoa - adicionarEndereco insere ao final da lista") {
    Pessoa p = criarPessoa();
    Endereco primeiro = criarEndereco("Rua das Flores");
    Endereco segundo = criarEndereco("Avenida Afonso Pena");

    SUBCASE("um endereco") {
        p.adicionarEndereco(primeiro);

        REQUIRE(p.getEnderecos().size() == 1);
        CHECK(p.getEnderecos()[0].formatarEndereco() == primeiro.formatarEndereco());
    }
    SUBCASE("dois enderecos mantem a ordem de insercao") {
        p.adicionarEndereco(primeiro);
        p.adicionarEndereco(segundo);

        REQUIRE(p.getEnderecos().size() == 2);
        CHECK(p.getEnderecos()[0].formatarEndereco() == primeiro.formatarEndereco());
        CHECK(p.getEnderecos()[1].formatarEndereco() == segundo.formatarEndereco());
    }
}

TEST_CASE("Pessoa - removerEndereco remove pela posicao (comeca em 0)") {
    Pessoa p = criarPessoa();
    Endereco a = criarEndereco("Rua A");
    Endereco b = criarEndereco("Rua B");
    Endereco c = criarEndereco("Rua C");
    p.adicionarEndereco(a);
    p.adicionarEndereco(b);
    p.adicionarEndereco(c);
    REQUIRE(p.getEnderecos().size() == 3);

    SUBCASE("remove o primeiro") {
        p.removerEndereco(0);
        REQUIRE(p.getEnderecos().size() == 2);
        CHECK(p.getEnderecos()[0].formatarEndereco() == b.formatarEndereco());
        CHECK(p.getEnderecos()[1].formatarEndereco() == c.formatarEndereco());
    }
    SUBCASE("remove o do meio") {
        p.removerEndereco(1);
        REQUIRE(p.getEnderecos().size() == 2);
        CHECK(p.getEnderecos()[0].formatarEndereco() == a.formatarEndereco());
        CHECK(p.getEnderecos()[1].formatarEndereco() == c.formatarEndereco());
    }
    SUBCASE("remove o ultimo") {
        p.removerEndereco(2);
        REQUIRE(p.getEnderecos().size() == 2);
        CHECK(p.getEnderecos()[0].formatarEndereco() == a.formatarEndereco());
        CHECK(p.getEnderecos()[1].formatarEndereco() == b.formatarEndereco());
    }
    SUBCASE("remover todos deixa a lista vazia") {
        p.removerEndereco(0);
        p.removerEndereco(0);
        p.removerEndereco(0);
        CHECK(p.getEnderecos().empty());
    }
}

TEST_CASE("Pessoa - removerEndereco com indice invalido lanca out_of_range") {
    Pessoa p = criarPessoa();

    SUBCASE("lista vazia") {
        CHECK_THROWS_AS(p.removerEndereco(0), std::out_of_range);
    }
    SUBCASE("indice igual a quantidade de enderecos (limite)") {
        p.adicionarEndereco(criarEndereco("Rua A"));
        CHECK_THROWS_AS(p.removerEndereco(1), std::out_of_range);
    }
    SUBCASE("indice muito maior que a quantidade") {
        p.adicionarEndereco(criarEndereco("Rua A"));
        CHECK_THROWS_AS(p.removerEndereco(100), std::out_of_range);
    }
    SUBCASE("falha nao altera a lista") {
        p.adicionarEndereco(criarEndereco("Rua A"));
        try {
            p.removerEndereco(5);
        } catch (const std::out_of_range&) {
        }
        CHECK(p.getEnderecos().size() == 1);
    }
}

TEST_CASE("Pessoa - possui destrutor virtual (uso polimorfico seguro)") {
    CHECK(std::has_virtual_destructor<Pessoa>::value);
}