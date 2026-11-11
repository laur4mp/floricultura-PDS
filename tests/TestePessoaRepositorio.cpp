#include "doctest.h"
#include <stdexcept>
#include "PessoaRepositorio.hpp"
#include <cstdio>
#include <fstream>

namespace {
struct ArquivoTemp {
    std::string caminho;
    explicit ArquivoTemp(const std::string& c) : caminho(c) { std::remove(caminho.c_str()); }
    ~ArquivoTemp() { std::remove(caminho.c_str()); }
};

Pessoa ana()   { return Pessoa(1, "Ana Souza",  "123.456.789-00", "ana@email.com",   "31999990000", "senha123"); }
Pessoa bruno() { return Pessoa(2, "Bruno Lima", "987.654.321-00", "bruno@email.com", "31988880000", "abc456"); }
Pessoa carla() { return Pessoa(3, "Carla Dias", "",               "carla@email.com", "",            "xyz789"); }

Endereco casaAna()    { return Endereco("Ana Souza", "30130-000", "Rua Sergipe", "1000", "Savassi", "Apt 2", "Belo Horizonte", "MG"); }
Endereco trabalhoAna(){ return Endereco("Ana Souza", "30160-010", "Rua da Bahia", "500", "Centro", "", "Belo Horizonte", "MG"); }
Endereco casaBruno()  { return Endereco("Bruno Lima", "01310-100", "Av. Paulista", "900", "Bela Vista", "", "Sao Paulo", "SP"); }
}

TEST_CASE("PessoaRepositorio: arquivo inexistente devolve listas vazias") {
    ArquivoTemp arq("teste_pessoas_inexistente.txt");
    PessoaRepositorio repo(arq.caminho);
    std::vector<PessoaRepositorio::Favorito> favoritos;
    CHECK(repo.carregar(favoritos).empty());
    CHECK(favoritos.empty());
}

TEST_CASE("PessoaRepositorio: gravar e carregar mantem os dados da pessoa") {
    ArquivoTemp arq("teste_pessoas.txt");
    PessoaRepositorio repo(arq.caminho);

    repo.gravar({ ana(), carla() }, {});

    std::vector<PessoaRepositorio::Favorito> favoritos;
    std::vector<Pessoa> lidas = repo.carregar(favoritos);
    REQUIRE(lidas.size() == 2);

    CHECK(lidas[0].getIdPessoa() == 1);
    CHECK(lidas[0].getNome() == "Ana Souza");
    CHECK(lidas[0].getCpf() == "123.456.789-00");
    CHECK(lidas[0].getEmail() == "ana@email.com");
    CHECK(lidas[0].getTelefone() == "31999990000");
    CHECK(lidas[0].getSenha() == "senha123");

    // CPF e telefone vazios tambem sobrevivem
    CHECK(lidas[1].getCpf().empty());
    CHECK(lidas[1].getTelefone().empty());
}

TEST_CASE("PessoaRepositorio: cada endereco volta para a pessoa certa") {
    ArquivoTemp arq("teste_pessoas_end.txt");
    PessoaRepositorio repo(arq.caminho);

    Pessoa a = ana();
    a.adicionarEndereco(casaAna());
    a.adicionarEndereco(trabalhoAna());
    Pessoa b = bruno();
    b.adicionarEndereco(casaBruno());
    Pessoa c = carla();                    

    repo.gravar({ a, b, c }, {});

    std::vector<PessoaRepositorio::Favorito> favoritos;
    std::vector<Pessoa> lidas = repo.carregar(favoritos);
    REQUIRE(lidas.size() == 3);

    REQUIRE(lidas[0].getEnderecos().size() == 2);
    CHECK(lidas[0].getEnderecos()[0].getCep() == "30130-000");
    CHECK(lidas[0].getEnderecos()[0].getComplemento() == "Apt 2");
    CHECK(lidas[0].getEnderecos()[1].getRua() == "Rua da Bahia");

    REQUIRE(lidas[1].getEnderecos().size() == 1);
    CHECK(lidas[1].getEnderecos()[0].getCidade() == "Sao Paulo");
    CHECK(lidas[1].getEnderecos()[0].getEstado() == "SP");

    CHECK(lidas[2].getEnderecos().empty());
}

TEST_CASE("PessoaRepositorio: endereco gravado depois da pessoa tambem e associado") {
    // simula o fluxo do app: a pessoa e cadastrada e o endereco chega numa tela posterior
    ArquivoTemp arq("teste_pessoas_end_depois.txt");
    PessoaRepositorio repo(arq.caminho);
    repo.gravar({ ana(), bruno() }, {});
    {
        std::ofstream out(arq.caminho, std::ios::app);
        out << "E|1|Ana Souza|30130-000|Rua Sergipe|1000|Savassi|Apt 2|Belo Horizonte|MG\n";
    }

    std::vector<PessoaRepositorio::Favorito> favoritos;
    std::vector<Pessoa> lidas = repo.carregar(favoritos);
    REQUIRE(lidas.size() == 2);
    CHECK(lidas[0].getEnderecos().size() == 1);
    CHECK(lidas[1].getEnderecos().empty());
}

TEST_CASE("PessoaRepositorio: favoritos sao gravados e carregados") {
    ArquivoTemp arq("teste_pessoas_fav.txt");
    PessoaRepositorio repo(arq.caminho);

    std::vector<PessoaRepositorio::Favorito> originais = { {1, 10}, {1, 12}, {2, 10} };
    repo.gravar({ ana(), bruno() }, originais);

    std::vector<PessoaRepositorio::Favorito> lidos;
    repo.carregar(lidos);
    REQUIRE(lidos.size() == 3);
    CHECK(lidos[0] == PessoaRepositorio::Favorito(1, 10));
    CHECK(lidos[1] == PessoaRepositorio::Favorito(1, 12));
    CHECK(lidos[2] == PessoaRepositorio::Favorito(2, 10));
}

TEST_CASE("PessoaRepositorio: '|' digitado pelo usuario nao quebra o arquivo") {
    ArquivoTemp arq("teste_pessoas_pipe.txt");
    PessoaRepositorio repo(arq.caminho);

    repo.gravar({ Pessoa(1, "Ana|Souza", "", "ana@email.com", "", "se|nha") }, {});

    std::vector<PessoaRepositorio::Favorito> favoritos;
    std::vector<Pessoa> lidas = repo.carregar(favoritos);
    REQUIRE(lidas.size() == 1);
    CHECK(lidas[0].getNome() == "Ana/Souza");
    CHECK(lidas[0].getSenha() == "se/nha");
}

TEST_CASE("PessoaRepositorio: linha corrompida lanca excecao") {
    ArquivoTemp arq("teste_pessoas_corrompido.txt");
    {
        std::ofstream out(arq.caminho);
        out << "P|1|Ana Souza|ana@email.com\n";   // faltam campos
    }
    PessoaRepositorio repo(arq.caminho);
    std::vector<PessoaRepositorio::Favorito> favoritos;
    CHECK_THROWS_AS(repo.carregar(favoritos), std::runtime_error);
}