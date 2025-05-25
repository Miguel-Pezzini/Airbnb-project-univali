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

public:
    Anfitriao(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {}

    Anfitriao(string nome, string senha, int telefone, int anfitriaoId) : Usuario(nome, senha, telefone, anfitriaoId) {}

    void listarImoveisCriados(vector<Imovel> imoveis) {
        for (const auto& imovel : imoveis) {
            if (imovel.getAnfitriaoResponsavelId() == this->getId()) {
                cout << "Id do Imovel: " << imovel.getId() << endl;
                cout << "Preco da diária: R$ " << imovel.getPrecoDiaria() << endl;
                cout << "Endereço: " << imovel.getEndereco() << endl;
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
        cout<<"Digite o preco da diaria: ";
        cin>>precoDiaria;

        Imovel imovelCriado = Imovel(endereco, intToTipos(tipo), capacidade, precoDiaria, this->getId());
        return imovelCriado;
    }
};

#endif //ANFITRIAO_H
