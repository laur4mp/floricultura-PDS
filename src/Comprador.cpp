#include "Comprador.hpp"
#include <stdexcept>
#include <cctype>

using namespace std;

static std::string minusculo(std::string s){
    for (char& ch : s)
        ch = std::tolower(static_cast<unsigned char>(ch));
    return s;
}

std::vector<Produto> Comprador::pesquisarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& nome
) const {
    vector<Produto> resultado;

    for (const Produto& produto : produtos){
        if (minusculo(produto.getNome()).find(minusculo(nome)) != string::npos){
            resultado.push_back(produto);
        }
    }
    return resultado;
}

std::vector<Produto> Comprador::filtrarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& categoria
) const {
    vector<Produto> resultado;

    for (const Produto& produto : produtos) {
        if (produto.getCategoria() == categoria) {
            resultado.push_back(produto);
        }
    }

    return resultado;
}

void Comprador::favoritarProduto(const Produto& produto) {
     for (const Produto& favorito : _produtosFavoritos) {
        if (favorito.getIdProduto() == produto.getIdProduto()) {
            return;
        }
    }

    _produtosFavoritos.push_back(produto);
}

void Comprador::desfavoritarProduto(const Produto& produto) {
    for (auto it = _produtosFavoritos.begin();
         it != _produtosFavoritos.end(); ++it) {

        if (it->getIdProduto() == produto.getIdProduto()) {
            _produtosFavoritos.erase(it);
            return;
        }
    }
}

const std::vector<Produto>& Comprador::consultarProdutosFavoritos() const {
    return _produtosFavoritos;
}


Venda Comprador::fazerPedido(
    int idVenda,
    const Endereco& enderecoEntrega,
    MetodoPagamento metodo) {

         if (_carrinho.empty()) {
            throw std::invalid_argument("Nao e possivel fazer um pedido com o carrinho vazio.");
        }

        Venda v(
        idVenda,
        getIdPessoa(),
        0,
        enderecoEntrega,
        enderecoEntrega.getNomeDest()
        );

        for (const ItemPedido& item : _carrinho) {
            v.adicionarItem(item);
        }

        v.setMetodoPagamento(metodo);
        limparCarrinho();

        return v;
    }

StatusVenda Comprador::acompanharPedido(const Venda& venda) const {
        return venda.getStatusVenda();
    }

void Comprador::cancelarPedido(Venda& venda) {
    if(venda.getIdPessoa() != getIdPessoa())
        throw std::invalid_argument("Este pedido nao pertence a voce!");
    if(venda.getStatusVenda() != StatusVenda::PROCESSAMENTO)
        throw std::logic_error("So eh possivel cancelar pedidos ainda em processamento!");
    venda.atualizarSvenda(StatusVenda::CANCELADO);
}

std::vector<Venda> Comprador::consultarHistoricoCompras(const std::vector<Venda>& vendas) const {
    std::vector<Venda> meus;
    for(const Venda& v : vendas)
        if(v.getIdPessoa() == getIdPessoa() ){
            meus.push_back(v);
        }
    return meus;
}

void Comprador::aplicarCupomVenda(Venda& venda, const Desconto& cupom) {
    venda.aplicarCupom(cupom);
}

void Comprador::adicionarAoCarrinho(const ItemPedido& item) {

    for (ItemPedido& it : _carrinho){
        if(it.getProduto().getIdProduto() == item.getProduto().getIdProduto()){
            it.setQuantidade(it.getQuantidade() + item.getQuantidade());
            return;
        }
    }

    _carrinho.push_back(item);
}

const std::vector<ItemPedido>& Comprador::consultarCarrinho() const {
    return _carrinho;
}

void Comprador::limparCarrinho() {
    _carrinho.clear();
}

void Comprador::alterarQuantidadeCarrinho(int idProduto, int novaQuantidade){

    for(auto it = _carrinho.begin(); it != _carrinho.end(); it++){

        if (it->getProduto().getIdProduto() == idProduto){
            if (novaQuantidade <= 0){
                _carrinho.erase(it);
            }else{
                it->setQuantidade(novaQuantidade);
            }
            return;
        }
    }
}

void Comprador::avaliarPedido(Venda& venda, int nota){
    if(venda.getIdPessoa() != getIdPessoa())
        throw std::invalid_argument("Este pedido nao pertence a voce.");
    venda.avaliar(nota);
}