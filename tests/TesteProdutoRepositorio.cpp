#include "doctest.h"
#include <stdexcept>
#include "ProdutoRepositorio.hpp"
#include <cstdio>
#include <fstream>

namespace {
// Apaga o arquivo antes e depois de cada teste, para um teste não interferir no outro.
struct ArquivoTemp {
    std::string caminho;
    explicit ArquivoTemp(const std::string& c) : caminho(c) { std::remove(caminho.c_str()); }
    ~ArquivoTemp() { std::remove(caminho.c_str()); }
};
}

TEST_CASE("ProdutoRepositorio: arquivo inexistente devolve lista vazia") {
    ArquivoTemp arq("teste_produtos_inexistente.txt");
    ProdutoRepositorio repo(arq.caminho);
    CHECK(repo.carregar().empty());
}

TEST_CASE("ProdutoRepositorio: gravar e carregar mantem todos os campos") {
    ArquivoTemp arq("teste_produtos.txt");
    ProdutoRepositorio repo(arq.caminho);

    std::vector<Produto> originais;
    originais.push_back(Produto(1, "Rosas", "Rosa vermelha", "Flores", 15.50, "img/rosa.png", 50, 10));
    originais.push_back(Produto(2, "Vaso", "", "Acessorios", 30.0, "", 0, 2)); // descricao e imagem vazias
    repo.gravar(originais);

    std::vector<Produto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 2);

    CHECK(lidos[0].getIdProduto() == 1);
    CHECK(lidos[0].getNome() == "Rosas");
    CHECK(lidos[0].getDescricao() == "Rosa vermelha");
    CHECK(lidos[0].getCategoria() == "Flores");
    CHECK(lidos[0].getPreco() == doctest::Approx(15.50));
    CHECK(lidos[0].getEnderecoImagem() == "img/rosa.png");
    CHECK(lidos[0].getQuantidadeEstoque() == 50);
    CHECK(lidos[0].getQuantidadeMinima() == 10);

    CHECK(lidos[1].getIdProduto() == 2);
    CHECK(lidos[1].getDescricao().empty());
    CHECK(lidos[1].getEnderecoImagem().empty());
    CHECK(lidos[1].getQuantidadeEstoque() == 0);
}

TEST_CASE("ProdutoRepositorio: '|' digitado pelo usuario nao quebra o arquivo") {
    ArquivoTemp arq("teste_produtos_pipe.txt");
    ProdutoRepositorio repo(arq.caminho);

    repo.gravar({ Produto(1, "Rosa|Vermelha", "linha1\nlinha2", "Flores", 10.0, "img.png", 5, 1) });

    std::vector<Produto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 1);
    CHECK(lidos[0].getNome() == "Rosa/Vermelha");
    CHECK(lidos[0].getDescricao() == "linha1 linha2");
}

TEST_CASE("ProdutoRepositorio: gravar reescreve o arquivo inteiro") {
    ArquivoTemp arq("teste_produtos_trunc.txt");
    ProdutoRepositorio repo(arq.caminho);

    repo.gravar({ Produto(1, "Rosas", "", "Flores", 10.0, "", 5, 1),
                  Produto(2, "Lirio", "", "Flores", 12.0, "", 5, 1) });
    repo.gravar({ Produto(3, "Tulipa", "", "Flores", 20.0, "", 5, 1) });

    std::vector<Produto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 1);
    CHECK(lidos[0].getIdProduto() == 3);
}

TEST_CASE("ProdutoRepositorio: linha com numero errado de campos e ignorada") {
    ArquivoTemp arq("teste_produtos_invalido.txt");
    {
        std::ofstream out(arq.caminho);
        out << "1|Rosas|desc|Flores|10.000000|img.png|5|1\n";
        out << "linha qualquer sem formato\n";
        out << "\n";
    }
    ProdutoRepositorio repo(arq.caminho);
    std::vector<Produto> lidos = repo.carregar();
    REQUIRE(lidos.size() == 1);
    CHECK(lidos[0].getNome() == "Rosas");
}