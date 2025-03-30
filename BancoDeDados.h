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
  void adicionarAnfitriao(Anfitriao anfitriao) { this->anfitrioes.push_back(anfitriao); this->usuarios.push_back(anfitriao); }
  void adicionarHospede(Hospede hospede) { this->hospedes.push_back(hospede); this->usuarios.push_back(hospede); }

  void criarImovel(string endereco, TiposImovel tipo, int capacidade, float precoDiaria, long anfitriaoResponsavelId, int dia, int mes, int ano) {
    this->adicionarImovel(Imovel(endereco, tipo, capacidade, precoDiaria, anfitriaoResponsavelId, dia, mes, ano));
  }
  void criarAnfitriao(string nome, string senha, int telefone) {
    this->adicionarAnfitriao(Anfitriao(nome, senha, telefone));
  }
  void criarHospede(string nome, string senha, int telefone) {
    this->adicionarHospede(Hospede(nome, senha, telefone));
  }

  void salvarImovel(Imovel imovel) {
    for (int i = 0; i < this->imoveis.size(); i++) {
      if (this->imoveis.at(i).getId() == imovel.getId()) {
        this->imoveis.at(i) = imovel;
      }
    }
  }

  Imovel getImovel(int idImovel) {
    for (int i = 0; i < this->imoveis.size(); i++) {
      if (this->imoveis.at(i).getId() == idImovel) {
        return this->imoveis.at(i);
      }
    }
  }

  void alugarImovel(int idImovel, int idUsuarioLogado) {
    Imovel imovel = getImovel(idImovel);
    imovel.setHospedeId(idUsuarioLogado);
    imovel.setIsAlugado(true);

    this->salvarImovel(imovel);
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

  vector<Imovel> getImoveisDisponiveis() {
    vector<Imovel> imoveisDisponiveis;
    for (int i = 0; i < this->imoveis.size(); i++) {
      if (this->imoveis.at(i).getIsAlugado()) {
        break;
      }
      imoveisDisponiveis.push_back(this->imoveis.at(i));
    }

    return imoveisDisponiveis;
  }
  void listarImoveisCriadosDoUsuario(int idUsuarioLogado) {
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

  void listarImoveisAlugadosDoUsuario(int idUsuarioLogado) {
    for (const auto& imovel : imoveis) {
      if (idUsuarioLogado == imovel.getHospedeId()) {
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

  void listarImoveis(vector<Imovel> &imoveis){
    for (const auto& imovel : imoveis) {
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

  vector<Imovel> ordenarImoveisPorPrecoELocalizacao(
    vector<Imovel> imoveisDisponiveisFiltradosPorData, float precoMAX,
    float precoMIN) {
    vector<Imovel> imoveisFiltradosPorPreco;
    for (Imovel imovel : imoveisDisponiveisFiltradosPorData) {
      if (imovel.getPrecoDiaria() <= precoMAX &&
          imovel.getPrecoDiaria() >= precoMIN) {
        imoveisFiltradosPorPreco.push_back(imovel);
          }
    }
    return imoveisFiltradosPorPreco;
  }

  vector<Imovel> filtrarImoveis() {
    vector<Imovel> imoveisDisponiveis = getImoveisDisponiveis();

    int dia, mes, ano, opcao;
    std::cout << "Qual o dia do aluguel?";
    cin >> dia;
    std::cout << "Qual o mes do aluguel?";
    cin >> mes;
    std::cout << "Qual o ano do aluguel?";
    cin >> ano;

    vector<Imovel> imoveisDisponiveisFiltradosPorData;
    for (Imovel imovel : imoveisDisponiveis) {
      if (imovel.getDataAluguel().getDia() == dia &&
          imovel.getDataAluguel().getMes() == mes &&
          imovel.getDataAluguel().getAno() == ano) {
        imoveisDisponiveisFiltradosPorData.push_back(imovel);
          }
    }

    std::cout << "Você gostaria de filtar por preço? 1 para sim, 0 para não";
    std::cin >> opcao;
    if (opcao == 1) {
      int precoMAX;
      int precoMIN;
      std::cout << "Qual o preço máximo?";
      std::cin >> precoMAX;
      std::cout << "Qual o preço mínimo?";
      std::cin >> precoMIN;
      vector<Imovel> imoveisFiltradosPorPreco =
          ordenarImoveisPorPrecoELocalizacao(imoveisDisponiveisFiltradosPorData,
                                             precoMAX, precoMIN);
      return imoveisFiltradosPorPreco;
    }

    return imoveisDisponiveisFiltradosPorData;
  }


};

#endif