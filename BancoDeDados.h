#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include "Hospede.h"
#include "Anfitriao.h"
#include "Imovel.h"
#include "Usuario.h"
#include "ImovelAlugado.h"
#include <vector>

class Anfitriao;
class Hospede;

class BancoDeDados {
  vector<Imovel> imoveis;
  vector<Anfitriao> anfitrioes;
  vector<Hospede> hospedes;
  vector<Usuario> usuarios;
  vector<ImovelAlugado> imoveisAlugados;

public:
  BancoDeDados() {
    this->imoveis = vector<Imovel>();
    this->anfitrioes = vector<Anfitriao>();
    this->hospedes = vector<Hospede>();
    this->usuarios = vector<Usuario>();
    this->imoveisAlugados = vector<ImovelAlugado>();
  };

  vector<Imovel> getImoveis() {return this->imoveis;}
  vector<ImovelAlugado> getImoveisAlugados() {return this->imoveisAlugados;}

  void adicionarImovel(const Imovel& imovel) { this->imoveis.push_back(imovel); }
  void adicionarAnfitriao(const Anfitriao& anfitriao) { this->anfitrioes.push_back(anfitriao); this->usuarios.push_back(anfitriao); }
  void adicionarHospede(const Hospede& hospede) { this->hospedes.push_back(hospede); this->usuarios.push_back(hospede); }
  void adicionarImovelAlugado(const ImovelAlugado &imovelAlugado) { this->imoveisAlugados.push_back(imovelAlugado); }

  void criarAnfitriao(string nome, string senha, int telefone) {
    this->adicionarAnfitriao(Anfitriao(nome, senha, telefone));
  }
  void criarHospede(string nome, string senha, int telefone) {
    this->adicionarHospede(Hospede(nome, senha, telefone));
  }

  void salvarHospede(Hospede hospede) {
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (this->hospedes.at(i).getId() == hospede.getId()) {
        this->hospedes.at(i) = hospede;
      }
    }
  }

  void salvarImovelAlugado(ImovelAlugado imovelAlugado) {
    for (int i = 0; i < this->imoveis.size(); i++) {
      if (imovelAlugado.getImovelId() == this->imoveis.at(i).getId()) {
        this->imoveis.at(i).addImovelAlugado(imovelAlugado);
      }
    }
  }

  Hospede getHospede(int idHospede) {
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (this->hospedes.at(i).getId() == idHospede) {
        return this->hospedes.at(i);
      }
    }
    throw std::runtime_error("Hospede com ID " + std::to_string(idHospede) + " não encontrado.");
  }

  Anfitriao getAnfitriao(int idAnfitriao) {
    for (int i = 0; i < this->anfitrioes.size(); i++) {
      if (this->anfitrioes.at(i).getId() == idAnfitriao) {
        return this->anfitrioes.at(i);
      }
    }
    throw std::runtime_error("Anfitrião com ID " + std::to_string(idAnfitriao) + " não encontrado.");
  }

  int logar(string nome, string senha, bool &isAnfitriao, bool &isHospede) {
    for (int i = 0; i < this->anfitrioes.size(); i++) {
      if (nome == this->anfitrioes.at(i).getNome() && senha == this->anfitrioes.at(i).getSenha()) {
        isAnfitriao = true;
        isHospede = false;
        return this->anfitrioes.at(i).getId();
      }
    }
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (nome == this->hospedes.at(i).getNome() && senha == this->hospedes.at(i).getSenha()) {
        isHospede = true;
        isAnfitriao = false;
        return this->hospedes.at(i).getId();
      }
    }

    return -1;
  }
};

#endif