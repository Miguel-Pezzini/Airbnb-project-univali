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
  void adicionarAnfitriao(Anfitriao anfitriao) { this->anfitrioes.push_back(anfitriao); }
  void adicionarHospede(Hospede hospede) { this->hospedes.push_back(hospede); }

  void criarImovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria, long anfitriaoResponsavelId, int dia, int mes, int ano) {
    this->adicionarImovel(Imovel(endereco, tipo, capacidade, precoDiaria, anfitriaoResponsavelId, dia, mes, ano));
  }
  void criarAnfitriao(string nome, string senha, int telefone) {
    this->adicionarAnfitriao(Anfitriao(nome, senha, telefone));
  }
  void criarHospede(string nome, string senha, int telefone) {
    this->adicionarHospede(Hospede(nome, senha, telefone));
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
  void listarImoveis(int idUsuarioLogado) {
    for (const auto& imovel : imoveis) {
      if (idUsuarioLogado == imovel.getAnfitriaoResponsavelId()) {
        cout << "Id do Imovel: " << imovel.getId() << endl;
        cout << "Preco da diária: R$ " << imovel.getPrecoDiaria() << endl;
        cout << "Endereço: " << imovel.getEndereco() << endl;
        cout << "Data do aluguel: " << imovel.getDataAluguel().dia
             << "/" << imovel.getDataAluguel().mes
             << "/" << imovel.getDataAluguel().ano << endl;
        cout << "Status: " << (imovel.getIsAlugado() ? "🔴 Reservado" : "🟢 Disponível") << endl;

        cout << "--------------------------------------\n";
      }
    }
  }
};

#endif