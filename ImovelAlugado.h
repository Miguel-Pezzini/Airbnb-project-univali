//
// Created by migue on 12/05/2025.
//

#ifndef IMOVELALUGADO_H
#define IMOVELALUGADO_H

#include <string>
#include "AbstractEntity.h"
#include "Tempo.h"

class ImovelAlugado : public AbstractEntity {
  long imovelId;
    long hospedeId;
    Tempo dataInicio;
    Tempo dataFinal;
    bool ativo;

    public:
    static int quantidadeDeImoveisAlugados;
    ImovelAlugado(long imovelId, long hospedeId, int diaInicio, int mesInicio,int anoInicio,int diaFinal,int mesFinal,int anoFinal)
      : AbstractEntity(quantidadeDeImoveisAlugados), dataInicio(diaInicio, mesInicio, anoInicio), dataFinal(diaFinal, mesFinal, anoFinal) {
      this->dataInicio = dataInicio;
      this->dataFinal = dataFinal;
      this->imovelId = imovelId;
      this->ativo = true;
      this->hospedeId = hospedeId;
      quantidadeDeImoveisAlugados++;
  }
  ImovelAlugado()
    : AbstractEntity(-1), dataInicio(0, 0, 0), dataFinal(0, 0, 0) {
      this->imovelId = -1;
      this->hospedeId = -1;
      this->ativo = false;
    }

  ImovelAlugado(long imovelId, long hospedeId, int diaInicio, int mesInicio,int anoInicio,int diaFinal,int mesFinal,int anoFinal, bool ativo, int id)
    : AbstractEntity(id, true), dataInicio(diaInicio, mesInicio, anoInicio), dataFinal(diaFinal, mesFinal, anoFinal)
     {
      this->dataInicio = dataInicio;
      this->dataFinal = dataFinal;
      this->imovelId = imovelId;
      this->ativo = ativo;
      this->hospedeId = hospedeId;
    }

  Tempo getDataInicio() const { return dataInicio; }
    Tempo getDataFinal() const { return dataFinal; }
  long getImovelId() const { return imovelId; }
  int getHospedeId() const { return hospedeId; }
  bool getAtivo() const { return ativo; }
    void setDataInicio(Tempo dataInicio) { this->dataInicio = dataInicio; }
    void setDataFinal(Tempo dataFinal) { this->dataFinal = dataFinal; }
  void setImovelId(long imovelId) { this->imovelId = imovelId; }
  void setHospede(long hospedeId) {this->hospedeId = hospedeId; }
  void setAtivo(bool ativo) { this->ativo = ativo; }

};

int ImovelAlugado::quantidadeDeImoveisAlugados = 0;
#endif //IMOVELALUGADO_H
