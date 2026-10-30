#include "Endereco.hpp"

using namespace std;

Endereco::Endereco() {}

Endereco::Endereco(const string& nomeDest, const string& cep, const string& rua, const string& numero, const string& bairro, const string& complemento,
                   const string& cidade, const string& estado)
    : nomeDest(nomeDest), cep(cep), rua(rua), numero(numero), bairro(bairro), complemento(complemento), cidade(cidade), estado(estado) {}

Endereco::~Endereco() {}

string Endereco::formatarEndereco() const{
    string semComplemento = rua + ", " + numero + " - " + bairro + ", " + cidade + " - " + estado + ", " + "CEP " + cep;
    string comComplemento = rua + ", " + numero + " - " + complemento + " - " + bairro + ", " + cidade + " - " + estado + ", " + "CEP " + cep;

    if(complemento == ""){
        return semComplemento;
    } else {
        return comComplemento;
    }
}

string Endereco::regiao() const{
    if(estado == "AC" || estado == "AP" || estado == "AM" || estado == "PA" || estado == "RO" || estado == "RR" || estado == "TO"){
        return "Norte";
    } else if(estado == "AL" || estado == "BA" || estado == "CE" || estado == "MA" || estado == "PB" || estado == "PE"
            || estado == "PI" || estado == "RN" || estado == "SE") {
        return "Nordeste";
    } else if(estado == "MT" || estado == "MS" || estado == "GO" || estado == "DF"){
        return "Centro-Oeste";
    } else if(estado == "MG" || estado == "ES" || estado == "SP" || estado == "RJ"){
        return "Sudeste";
    } else if(estado == "PR" || estado == "SC" || estado == "RS"){
        return "Sul";
    } else {
    return "Estado invalido";
    }
}

string Endereco::getNomeDest() const{
    return nomeDest;
}

bool Endereco::setCep(const string& cep){
    if(cep.size() != 8){
        return false;
    }

    for(char c : cep){
        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9'){
            return false;
        }
    }

    this->cep = cep;
    return true;
}

bool Endereco::setEstado(const string& estado){
    if(estado == "AC" || estado == "AP" || estado == "AM" || estado == "PA" || estado == "RO" || estado == "RR" || estado == "TO" || estado == "AL" ||
       estado == "BA" || estado == "CE" || estado == "MA" || estado == "PB" || estado == "PE" || estado == "PI" || estado == "RN" || estado == "SE" ||
       estado == "MT" || estado == "MS" || estado == "GO" || estado == "DF" || estado == "MG" || estado == "ES" || estado == "SP" || estado == "RJ" ||
       estado == "PR" || estado == "SC" || estado == "RS"){
        this->estado = estado;
        return true;
    }
    return false;
}