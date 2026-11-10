#include "VendaRepositorio.hpp"
#include <algorithm> //para remover o | caso alguem digite
#include <fstream>
#include <sstream>
#include <stdexcept>

VendaRepositorio::VendaRepositorio(const std::string& caminho) : _caminho(caminho) {}

std::string VendaRepositorio::limpar(std::string s) const {
    std::replace(s.begin(), s.end(), '|', '/');
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

void VendaRepositorio::gravar(const std::vector<Venda>& vendas) const {
    std::ofstream out(_caminho, std::ios::trunc); //mesma logica de apagar o arquivo e escrever de novo
    if (!out.is_open()) {
        throw std::runtime_error("Não foi possível gravar o arquivo " + _caminho);
    }

    for (const auto& v : vendas) {
        // Itens primeiro. Cada um guarda uma cópia do produto: se o preço do mudar, a venda antiga continua com o valor da época.
        for (const auto& it : v.getItens()) {
            const Produto& p = it.getProduto();
            out << "I|" << p.getIdProduto() << '|' << limpar(p.getNome()) << '|'
                << limpar(p.getDescricao()) << '|' << limpar(p.getCategoria()) << '|'
                << std::to_string(p.getPreco()) << '|' << limpar(p.getEnderecoImagem()) << '|'
                << p.getQuantidadeEstoque() << '|' << p.getQuantidadeMinima() << '|'
                << it.getQuantidade() << '\n';
        }

        const Endereco& e = v.getEnderecoEntrega();
        const Desconto& d = v.getDescontoAplicado();
        out << "V|" << v.getIdVenda() << '|' << v.getIdPessoa() << '|'
            << limpar(v.getNomeDestina()) << '|' << static_cast<int>(v.getStatusVenda()) << '|'  //converte o enum para int 
            << static_cast<int>(v.getStatusPagamento()) << '|' << limpar(v.getDataEntrega()) << '|' //converte o enum para int também
            << limpar(v.getHorarioEntregaPrevisao()) << '|' << limpar(e.getNomeDest()) << '|'
            << limpar(e.getCep()) << '|' << limpar(e.getRua()) << '|' << limpar(e.getNumero()) << '|'
            << limpar(e.getBairro()) << '|' << limpar(e.getComplemento()) << '|'
            << limpar(e.getCidade()) << '|' << limpar(e.getEstado()) << '|'
            << limpar(d.getCupom()) << '|' << std::to_string(d.getPercentual()) << '\n';
    }
} 
//como fica no arquivo o formato dos enums
//processameto 0, enviado 1, entregue 2, cancelado 3
//aguardando pagamento 0, pago 1

std::vector<Venda> VendaRepositorio::carregar() const {
    std::vector<Venda> vendas;
    std::vector<ItemPedido> itens; // itens já lidos, esperando a linha da sua venda

    std::ifstream in(_caminho);
    if (!in.is_open()) return vendas;

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> c;
        std::stringstream ss(linha);
        std::string campo;
        while (std::getline(ss, campo, '|')) c.push_back(campo);

        if (c[0] == "I" && c.size() == 10) {
            Produto p(std::stoi(c[1]), c[2], c[3], c[4], std::stod(c[5]), c[6], std::stoi(c[7]), std::stoi(c[8]));
            itens.push_back(ItemPedido(p, std::stoi(c[9])));

        } else if (c[0] == "V" && c.size() == 18) {
            Endereco endereco; // fica vazio se a venda não tinha endereço
            if (!c[8].empty()) endereco = Endereco(c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);

            Venda v(std::stoi(c[1]), std::stoi(c[2]), endereco, c[3]);
            if (!c[6].empty()) v.setDataEntrega(c[6]);
            if (!c[7].empty()) v.setHorarioEntregaPrevisao(c[7]);

            for (const auto& item : itens) v.adicionarItem(item);
            itens.clear();

         
            if (!c[16].empty()) v.aplicarCupom(Desconto(c[16], std::stod(c[17]), "9999-12-31"));

            // restaura o estado seguindo as transições normais de Venda
            StatusVenda sv = static_cast<StatusVenda>(std::stoi(c[4]));
            StatusPagamento sp = static_cast<StatusPagamento>(std::stoi(c[5]));
            if (sp == StatusPagamento::PAGO) v.atualizarSpagamento(StatusPagamento::PAGO);
            if (sv == StatusVenda::ENVIADO || sv == StatusVenda::ENTREGUE) v.atualizarSvenda(StatusVenda::ENVIADO);
            if (sv == StatusVenda::ENTREGUE) v.atualizarSvenda(StatusVenda::ENTREGUE);
            if (sv == StatusVenda::CANCELADO) v.atualizarSvenda(StatusVenda::CANCELADO);

            vendas.push_back(v);

        } else {
            throw std::runtime_error("VendaRepositorio: linha corrompida: " + linha);
        }
    }
    return vendas;
}