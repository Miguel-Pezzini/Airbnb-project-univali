#ifndef IMOVEL_H
#define IMOVEL_H

#include "AbstractEntity.h"
#include <string>
#include <vector>

#include "ImovelAlugado.h"

using namespace std;

enum TiposImovel { CASA, APARTAMENTO, CHALE };

TiposImovel intToTipos(int tipo) {
  switch (tipo) {
    case 0:
      return TiposImovel::CASA;
    case 1:
      return TiposImovel::APARTAMENTO;
    case 2:
      return TiposImovel::CHALE;
    default:
      return TiposImovel::CASA;
  }
}

int tipoToInt(TiposImovel tipo) {
  switch (tipo) {
    case TiposImovel::CASA:
      return 0;
    case TiposImovel::APARTAMENTO:
      return 1;
    case TiposImovel::CHALE:
      return 2;
    default:
      return 0;
  }
}

class Imovel : public AbstractEntity {
  long anfitriaoResponsavelId;
  string endereco;
  TiposImovel tipo;
  int capacidade;
  float precoDiaria;


public:
  static int quantidadeDeImoveis;
  Imovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria,
         long anfitriaoResponsavelId)
      : AbstractEntity(quantidadeDeImoveis) {
    this->endereco = endereco;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->precoDiaria = precoDiaria;
    this->anfitriaoResponsavelId = anfitriaoResponsavelId;
    quantidadeDeImoveis++;
  }

  Imovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria,
        long anfitriaoResponsavelId, int id)
     : AbstractEntity(id, true) {
    this->endereco = endereco;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->precoDiaria = precoDiaria;
    this->anfitriaoResponsavelId = anfitriaoResponsavelId;
  }

  string getEndereco() const { return this->endereco; }
  TiposImovel getTipo() const { return this->tipo; }
  int getCapacidade() const { return this->capacidade; }
  float getPrecoDiaria() const{ return this->precoDiaria; }
  long getAnfitriaoResponsavelId() const { return this->anfitriaoResponsavelId; }
  void setEndereco(string endereco) { this->endereco = endereco; }
  void setTipo(TiposImovel tipo) { this->tipo = tipo; }
  void setCapacidade(int capacidade) { this->capacidade = capacidade; }
  void setPrecoDiaria(float precoDiaria) { this->precoDiaria = precoDiaria; }
};

int Imovel::quantidadeDeImoveis = 0;

#endif