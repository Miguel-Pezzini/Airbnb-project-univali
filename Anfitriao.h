//
// Created by miguel on 3/30/25.
//

#ifndef ANFITRIAO_H
#define ANFITRIAO_H

#include <iostream>
#include <vector>

#include "Usuario.h"
#include "Imovel.h"

class Anfitriao : public Usuario {
    vector<Imovel> imoveisCriados;

public:
    Anfitriao(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {}

    void listarImoveisCriados(vector<Imovel> imoveis) {
        for (const auto& imovel : imoveis) {
            if (imovel.getAnfitriaoResponsavelId() == this->getId()) {
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

    Imovel criarImovel() {
        string endereco;
        int capacidade, dia, mes, ano, tipo;
        float precoDiaria;
        cout<<"Digite o endereco ";
        cin.ignore();
        getline(cin, endereco);
        cout<<"Digite o tipo do imovel: "<<endl;
        cout<<"1: Casa"<<endl;
        cout<<"2: Apartamento"<<endl;
        cout<<"3: Chale"<<endl;
        cin>>tipo;
        cout<<"Digite a capacidade: ";
        cin>>capacidade;
        cout<<"Digite o dia: ";
        cin>>dia;
        cout<<"Digite o mes: ";
        cin>>mes;
        cout<<"Digite o ano: ";
        cin>>ano;
        cout<<"Digite o preco da diaria: ";
        cin>>precoDiaria;

        Imovel imovelCriado = Imovel(endereco, intToTipos(tipo), capacidade, precoDiaria, this->getId(), dia, mes, ano);
        this->imoveisCriados.push_back(imovelCriado);
        return imovelCriado;
    }
};

#endif //ANFITRIAO_H
