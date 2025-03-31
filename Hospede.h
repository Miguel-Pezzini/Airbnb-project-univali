//
// Created by miguel on 3/30/25.
//

#ifndef HOSPEDE_H
#define HOSPEDE_H

#include <iostream>

#include "Usuario.h"
#include "Imovel.h"

#include <vector>

class Hospede : public Usuario {
public:
    Hospede(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {};

    vector<Imovel> getImoveisDisponiveis(const vector<Imovel>& imoveis) {
        vector<Imovel> imoveisDisponiveis;
        for (const auto& imovel : imoveis) {
            if (!imovel.getIsAlugado()) {
                imoveisDisponiveis.push_back(imovel);
            }
        }
        return imoveisDisponiveis;
    }

    void listarImoveis(const vector<Imovel>& imoveis) {
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


    vector<Imovel> filtrarPorPreco(const vector<Imovel>& imoveis, float precoMIN, float precoMAX) {
        vector<Imovel> imoveisFiltrados;
        for (const auto& imovel : imoveis) {
            if (imovel.getPrecoDiaria() >= precoMIN && imovel.getPrecoDiaria() <= precoMAX) {
                imoveisFiltrados.push_back(imovel);
            }
        }
        return imoveisFiltrados;
    }

    vector<Imovel> filtrarPorEndereco(const vector<Imovel>& imoveis, const string& endereco) {
        vector<Imovel> imoveisFiltrados;
        for (const auto& imovel : imoveis) {
            if (imovel.getEndereco().find(endereco) != string::npos) {
                imoveisFiltrados.push_back(imovel);
            }
        }
        return imoveisFiltrados;
    }

    vector<Imovel> filtrarImoveis(vector<Imovel> imoveisTotais) {
        vector<Imovel> imoveisDisponiveis = getImoveisDisponiveis(imoveisTotais);

        int dia, mes, ano, opcao;
        cout << "Qual o dia do aluguel? ";
        cin >> dia;
        cout << "Qual o mes do aluguel? ";
        cin >> mes;
        cout << "Qual o ano do aluguel? ";
        cin >> ano;

        vector<Imovel> imoveisFiltrados;
        for (const auto& imovel : imoveisDisponiveis) {
            if (imovel.getDataAluguel().getDia() == dia &&
                imovel.getDataAluguel().getMes() == mes &&
                imovel.getDataAluguel().getAno() == ano) {
                imoveisFiltrados.push_back(imovel);
                }
        }

        cout << "Você gostaria de filtrar por preço? (1 - Sim, 0 - Não): ";
        cin >> opcao;
        if (opcao == 1) {
            float precoMAX, precoMIN;
            cout << "Qual o preço máximo? ";
            cin >> precoMAX;
            cout << "Qual o preço mínimo? ";
            cin >> precoMIN;
            imoveisFiltrados = filtrarPorPreco(imoveisFiltrados, precoMIN, precoMAX);
        }

        cout << "Você gostaria de filtrar por endereço? (1 - Sim, 0 - Não): ";
        cin >> opcao;
        if (opcao == 1) {
            string endereco;
            cout << "Qual o endereço? ";
            cin.ignore();
            getline(cin, endereco);
            imoveisFiltrados = filtrarPorEndereco(imoveisFiltrados, endereco);
        }

        return imoveisFiltrados;
    }

    Imovel getImovel(vector<Imovel> imoveis, int idImovel) {
        for (int i = 0; i < imoveis.size(); i++) {
            if (imoveis.at(i).getId() == idImovel) {
                return imoveis.at(i);
            }
        }
    }

    Imovel alugarImovel(vector<Imovel> imoveis) {
        int idImovel;
        vector<Imovel> imoveisFiltrados = this->filtrarImoveis(imoveis);
        this->listarImoveis(imoveisFiltrados);

        cout<<"Digite o id do imovel que voce deseja alugar: ";
        cin>>idImovel;

        Imovel imovel = getImovel(imoveisFiltrados, idImovel);
        imovel.setHospedeId(this->getId());
        imovel.setIsAlugado(true);
        return imovel;
    }

    void listarImoveisAlugados(vector<Imovel> imoveis) {
        for (const auto& imovel : imoveis) {
            if (imovel.getHospedeId() == this->getId()) {
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
