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

class Imovel : public AbstractEntity {
  long anfitriaoResponsavelId;
  string endereco;
  TiposImovel tipo;
  int capacidade;
  float precoDiaria;
  static int quantidadeDeImoveis;
  vector<ImovelAlugado> imoveisAlugados;

public:
  Imovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria,
         long anfitriaoResponsavelId)
      : AbstractEntity(quantidadeDeImoveis) {
    this->endereco = endereco;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->precoDiaria = precoDiaria;
    this->anfitriaoResponsavelId = anfitriaoResponsavelId;
    this->imoveisAlugados = vector<ImovelAlugado>();
    quantidadeDeImoveis++;
  }

  string getEndereco() const { return this->endereco; }
  TiposImovel getTipo() const { return this->tipo; }
  int getCapacidade() const { return this->capacidade; }
  float getPrecoDiaria() const{ return this->precoDiaria; }
  long getAnfitriaoResponsavelId() const { return this->anfitriaoResponsavelId; }
  vector<ImovelAlugado> getImoveisAlugados() const {return this->imoveisAlugados; }
  void setEndereco(string endereco) { this->endereco = endereco; }
  void setTipo(TiposImovel tipo) { this->tipo = tipo; }
  void setCapacidade(int capacidade) { this->capacidade = capacidade; }
  void setPrecoDiaria(float precoDiaria) { this->precoDiaria = precoDiaria; }
  void addImovelAlugado(ImovelAlugado imovelAlugado) { this->imoveisAlugados.push_back(imovelAlugado); }

};

int Imovel::quantidadeDeImoveis = 0;

#endif