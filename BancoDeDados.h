#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include "TiposDeUsuarios.h"
#include <iostream>
#include <vector>

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

  void adicionarImovel(Imovel imovel) { this->imoveis.push_back(imovel); }
  void adicionarAnfitriao(Anfitriao anfitriao) {
    this->anfitrioes.push_back(anfitriao);
  }
  void adicionarHospede(Hospede hospede) { this->hospedes.push_back(hospede); }
  void adicionarUsuario(Usuario usuario) { this->usuarios.push_back(usuario); }

  void criarAnfitriao(string nome, string senha, int telefone) {
    this->adicionarAnfitriao(Anfitriao(nome, senha, telefone));
  }

  void criarHospede(string nome, string senha, int telefone) {
    this->adicionarHospede(Hospede(nome, senha, telefone));
  }
};

#endif