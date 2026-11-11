#include "Desconto.hpp"
#include <stdexcept>
#include <ctime>
#include <cstdio>

using namespace std;

static bool validarData(const string& data){
    if(data.size() != 10 || data[4] != '-' || data[7] != '-'){
        return false;
    }
    int ano, mes, dia;

    if(sscanf(data.c_str(), "%d-%d-%d", &ano, &mes, &dia) != 3){
        return false;
    }
    if(ano < 1 || mes < 1 || mes > 12 || dia < 1 || dia > 31){
        return false;
    }
    return true;
}

static string dataAtual(){
    time_t agora = time(nullptr);
    tm* t = localtime(&agora);

    if(t == nullptr){
        throw runtime_error("Nao foi possivel obter a data atual!");
    }
    
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
    return string(buffer);
}

bool Desconto::ehValido() const{
    if((dataValidade == "") || (dataValidade < dataAtual())){
        return false;
    }
    return true;
}

Desconto::Desconto() : cupom(""), percentual(0.0), dataValidade("") {}

Desconto::Desconto(const string& cupom, double percentual, const string& dataValidade) : cupom(cupom), percentual(percentual), dataValidade(dataValidade){
    if(percentual < 0.0 || percentual > 100.0){
        throw invalid_argument("Percentual de desconto invalido!");
    }

    if(!validarData(dataValidade)){
        throw invalid_argument("Data de validade invalida! Use o formato AAAA-MM-DD.");
    }
}

Desconto::~Desconto() {}

string Desconto::getCupom() const{
    return cupom;
}

double Desconto::getPercentual() const {
    return percentual;
}

string Desconto::getDataValidade() const{
    return dataValidade;
}

double Desconto::aplicar(double valorTotal) const{
    if(valorTotal < 0.0){
        throw invalid_argument("Valor total nao pode ser negativo!");
    }
    if(!ehValido()){
        return valorTotal;
    }
    return valorTotal * ((100.0 - percentual) / 100.0);
}
