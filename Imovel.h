#ifndef IMOVEL_H
#define IMOVEL_H

#include "AbstractEntity.h"
#include <string>

using namespace std;

enum TiposImovel { CASA, APARTAMENTO, CHALE };

struct Tempo {
  int dia;
  int mes;
  int ano;

  Tempo(int dia, int mes, int ano) {
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
  }

  string toString() const {
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);
  }
  int getDia() const { return dia; }
  int getMes() const { return mes; }
  int getAno() const { return ano; }
};

class Imovel : public AbstractEntity {
private:
  long anfitriaoResponsavelId;
  string endereco;
  TiposImovel tipo;
  int capacidade;
  float precoDiaria;
  static int quantidadeDeImoveis;
  Tempo dataAluguel;
  bool isAlugado = false;

public:
  Imovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria,
         long anfitriaoResponsavelId, int dia, int mes, int ano)
      : AbstractEntity(quantidadeDeImoveis), dataAluguel(dia, mes, ano) {
    this->endereco = endereco;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->precoDiaria = precoDiaria;
    this->anfitriaoResponsavelId = anfitriaoResponsavelId;
    quantidadeDeImoveis++;
  }

  string getEndereco() const { return this->endereco; }
  TiposImovel getTipo() const { return this->tipo; }
  int getCapacidade() const { return this->capacidade; }
  float getPrecoDiaria() const{ return this->precoDiaria; }
  long getAnfitriaoResponsavelId() const { return this->anfitriaoResponsavelId; }
  Tempo getDataAluguel() const{ return this->dataAluguel; }
  bool getIsAlugado() const{ return this->isAlugado; }
  void setEndereco(string endereco) { this->endereco = endereco; }
  void setTipo(TiposImovel tipo) { this->tipo = tipo; }
  void setCapacidade(int capacidade) { this->capacidade = capacidade; }
  void setPrecoDiaria(float precoDiaria) { this->precoDiaria = precoDiaria; }
  void setIsAlugado(bool isAlugado) { this->isAlugado = isAlugado; }
  void setDataAluguel(int dia, int mes, int ano) {
    this->dataAluguel = Tempo(dia, mes, ano);
  }
};

int Imovel::quantidadeDeImoveis = 0;

#endif