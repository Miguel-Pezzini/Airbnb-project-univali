#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include "Hospede.h"
#include "Anfitriao.h"
#include "Imovel.h"
#include "Usuario.h"
#include <vector>

class Anfitriao;
class Hospede;

class BancoDeDados {
  vector<Imovel> imoveis;
  vector<Anfitriao> anfitrioes;
  vector<Hospede> hospedes;
  vector<Usuario> usuarios;

public:
  BancoDeDados() {
    this->imoveis = vector<Imovel>();
    this->anfitrioes = vector<Anfitriao>();
    this->hospedes = vector<Hospede>();
    this->usuarios = vector<Usuario>();
  };

  vector<Imovel> getImoveis() {
    return this->imoveis;
  }

  void adicionarImovel(Imovel imovel) { this->imoveis.push_back(imovel); }
  void adicionarAnfitriao(Anfitriao anfitriao) { this->anfitrioes.push_back(anfitriao); this->usuarios.push_back(anfitriao); }
  void adicionarHospede(Hospede hospede) { this->hospedes.push_back(hospede); this->usuarios.push_back(hospede); }

  void criarAnfitriao(string nome, string senha, int telefone) {
    this->adicionarAnfitriao(Anfitriao(nome, senha, telefone));
  }
  void criarHospede(string nome, string senha, int telefone) {
    this->adicionarHospede(Hospede(nome, senha, telefone));
  }


  Hospede getHospede(int idHospede) {
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (this->hospedes.at(i).getId() == idHospede) {
        return this->hospedes.at(i);
      }
    }
  }

  Anfitriao getAnfitriao(int idAnfitriao) {
    for (int i = 0; i < this->anfitrioes.size(); i++) {
      if (this->anfitrioes.at(i).getId() == idAnfitriao) {
        return this->anfitrioes.at(i);
      }
    }
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