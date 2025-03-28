#ifndef TIPOSDEUSUARIOS_H
#define TIPOSDEUSUARIOS_H

#include "Imovel.h"
#include "Usuario.h"
#include <iostream>
#include <vector>

class Anfitriao : public Usuario {
  vector<Imovel> imoveisCriados;

public:
  Anfitriao(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {}

  Imovel criarImovel(string endereco, TiposImovel tipo, int capacidade,
                     float precoDiaria, int dia, int mes, int ano) {
    Imovel imovel(endereco, tipo, capacidade, precoDiaria, this->getId(), dia,
                  mes, ano);

    imoveisCriados.push_back(imovel);

    return imovel;
  }
};

class Hospede : public Usuario {
  vector<Imovel> imovelAlugado;

public:
  Hospede(string nome, string senha, int telefone) : Usuario(nome, senha, telefone){};

  Imovel alugarImovel(Imovel imovel) {
    imovel.setIsAlugado(true);
    imovelAlugado.push_back(imovel);

    return imovel;
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

  vector<Imovel> listarImoveis(vector<Imovel> imoveisDisponiveis) {
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
          imovel.getDataAluguel().ano == ano) {
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