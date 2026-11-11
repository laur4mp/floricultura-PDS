#include "doctest.h"
#include <stdexcept>
#include "DescontoRepositorio.hpp"
#include <cstdio>
#include <fstream>

namespace {
struct ArquivoTemp {
    std::string caminho;
    explicit ArquivoTemp(const std::string& c) : caminho(c) { std::remove(caminho.c_str()); }
    ~ArquivoTemp() { std::remove(caminho.c_str()); }
};

// escreve um arquivo "na mao", para simular dados ja gravados (ou corrompidos)
void escrever(const std::string& caminho, const std::string& conteudo) {
    std::ofstream out(caminho);
    out << conteudo;
}
}

TEST_CASE("DescontoRepositorio: arquivo inexistente devolve lista vazia") {
    ArquivoTemp arq("teste_cupons_inexistente.txt");
    DescontoRepositorio repo(arq.caminho);
    CHECK(repo.carregar().empty());
}

TEST_CASE("DescontoRepositorio: gravar e carregar mantem codigo, percentual e validade real") {
    ArquivoTemp arq("teste_cupons.txt");
    DescontoRepositorio repo(arq.caminho);

    repo.gravar({ Desconto("FLOR10", 10.0, "2099-12-31"),
                  Desconto("MAES25", 12.5, "2020-05-10") });   // cupom ja vencido

    std::vector<Desconto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 2);

    CHECK(lidos[0].getCupom() == "FLOR10");
    CHECK(lidos[0].getPercentual() == doctest::Approx(10.0));
    CHECK(lidos[0].getDataValidade() == "2099-12-31");
    CHECK(lidos[0].ehValido() == true);

    // a validade REAL e gravada: o cupom vencido continua vencido depois de carregar
    CHECK(lidos[1].getCupom() == "MAES25");
    CHECK(lidos[1].getPercentual() == doctest::Approx(12.5));
    CHECK(lidos[1].getDataValidade() == "2020-05-10");
    CHECK(lidos[1].ehValido() == false);
}

TEST_CASE("DescontoRepositorio: percentuais nos limites 0 e 100 sao aceitos") {
    ArquivoTemp arq("teste_cupons_limites.txt");
    DescontoRepositorio repo(arq.caminho);

    repo.gravar({ Desconto("ZERO", 0.0, "2099-12-31"),
                  Desconto("GRATIS", 100.0, "2099-12-31") });

    std::vector<Desconto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 2);
    CHECK(lidos[0].getPercentual() == doctest::Approx(0.0));
    CHECK(lidos[1].getPercentual() == doctest::Approx(100.0));
}

TEST_CASE("DescontoRepositorio: '|' digitado no codigo nao quebra o arquivo") {
    ArquivoTemp arq("teste_cupons_pipe.txt");
    DescontoRepositorio repo(arq.caminho);

    repo.gravar({ Desconto("FLOR|10", 10.0, "2099-12-31") });

    std::vector<Desconto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 1);
    CHECK(lidos[0].getCupom() == "FLOR/10");
    CHECK(lidos[0].getPercentual() == doctest::Approx(10.0));
}

TEST_CASE("DescontoRepositorio: gravar reescreve o arquivo inteiro") {
    ArquivoTemp arq("teste_cupons_trunc.txt");
    DescontoRepositorio repo(arq.caminho);

    repo.gravar({ Desconto("A", 5.0, "2099-12-31"), Desconto("B", 5.0, "2099-12-31") });
    repo.gravar({ Desconto("C", 5.0, "2099-12-31") });

    std::vector<Desconto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 1);
    CHECK(lidos[0].getCupom() == "C");
}

TEST_CASE("DescontoRepositorio: percentual invalido no arquivo e recusado pelo construtor") {
    ArquivoTemp arq("teste_cupons_percentual.txt");
    escrever(arq.caminho, "SUPER|150.000000|2099-12-31\n");
    DescontoRepositorio repo(arq.caminho);
    CHECK_THROWS_AS(repo.carregar(), std::invalid_argument);

    escrever(arq.caminho, "NEG|-5.000000|2099-12-31\n");
    CHECK_THROWS_AS(repo.carregar(), std::invalid_argument);
}

TEST_CASE("DescontoRepositorio: linha com numero errado de campos lanca excecao") {
    ArquivoTemp arq("teste_cupons_corrompido.txt");
    escrever(arq.caminho, "FLOR10|10.000000\n");          // falta a validade
    DescontoRepositorio repo(arq.caminho);
    CHECK_THROWS_AS(repo.carregar(), std::runtime_error);
}

TEST_CASE("DescontoRepositorio: percentual que nao e numero lanca excecao") {
    ArquivoTemp arq("teste_cupons_texto.txt");
    escrever(arq.caminho, "FLOR10|dez|2099-12-31\n");
    DescontoRepositorio repo(arq.caminho);
    CHECK_THROWS(repo.carregar());
}

TEST_CASE("DescontoRepositorio: linhas em branco sao ignoradas") {
    ArquivoTemp arq("teste_cupons_branco.txt");
    escrever(arq.caminho, "\nFLOR10|10.000000|2099-12-31\n\n");
    DescontoRepositorio repo(arq.caminho);
    CHECK(repo.carregar().size() == 1);
}

// So passa depois da alteracao recomendada no Desconto.cpp:
// usar o validarData() dentro do construtor.
TEST_CASE("DescontoRepositorio: validade em formato invalido e recusada") {
    ArquivoTemp arq("teste_cupons_data.txt");
    escrever(arq.caminho, "FLOR10|10.000000|31/12/2099\n");
    DescontoRepositorio repo(arq.caminho);
    CHECK_THROWS_AS(repo.carregar(), std::invalid_argument);
}