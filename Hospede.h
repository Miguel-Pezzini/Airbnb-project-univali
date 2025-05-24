//
// Created by miguel on 3/30/25.
//

#ifndef HOSPEDE_H
#define HOSPEDE_H

#include <iostream>
#include <ctime>

#include "BancoDeDados.h"
#include "Usuario.h"
#include "Imovel.h"

#include <vector>

class Hospede : public Usuario {
    vector<ImovelAlugado> imoveisAlugados;
public:
    Hospede(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {
        this->imoveisAlugados = vector<ImovelAlugado>();
    };

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

    ImovelAlugado filtrarImoveis(vector<Imovel> imoveisTotais) {
        int diaInicio, mesInicio, anoInicio, opcao;
        cout << "Qual o dia do inicio do aluguel? ";
        cin >> diaInicio;
        cout << "Qual o mes do inicio do aluguel? ";
        cin >> mesInicio;
        cout << "Qual o ano do inicio do aluguel? ";
        cin >> anoInicio;
        Tempo dataInicio(diaInicio, mesInicio, anoInicio);
        int diaFinal, mesFinal, anoFinal;
        cout << "Qual o dia do final do aluguel? ";
        cin >> diaFinal;
        cout << "Qual o mes do final do aluguel? ";
        cin >> mesFinal;
        cout << "Qual o ano do final do aluguel? ";
        cin >> anoFinal;
        Tempo dataFinal(diaInicio, mesInicio, anoInicio);

        vector<Imovel> imoveisFiltrados;
        for (int i = 0; i < imoveisTotais.size(); i++) {
            vector<ImovelAlugado>imoveisAlugados = imoveisTotais.at(i).getImoveisAlugados();
            bool valido = true;
            for (int j = 0; j < imoveisAlugados.size(); j++) {
                if (Tempo::isBetween(dataInicio, dataFinal, imoveisAlugados.at(i).getDataInicio(), imoveisAlugados.at(j).getDataFinal())) {
                    valido = false;
                }
            }
            if (valido) {
                imoveisFiltrados.push_back(imoveisTotais.at(i));
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
        int idImovel;
        if (imoveisFiltrados.size() > 0) {
            this->listarImoveis(imoveisFiltrados);
            cout<<"Digite o id do imovel que voce deseja alugar: ";
            cin>>idImovel;
        } else {
            cout << string(50, '\n');
            cout << "Nao existem imoveis com esses filtros!"<<endl;
            return ImovelAlugado();
        }
        ImovelAlugado imovelAlugado(idImovel, this->getId(), diaInicio, mesInicio, anoInicio, diaFinal, mesFinal, anoFinal);
        return imovelAlugado;
    }

    Imovel getImovel(vector<Imovel> imoveis, int idImovel) {
        for (int i = 0; i < imoveis.size(); i++) {
            if (imoveis.at(i).getId() == idImovel) {
                return imoveis.at(i);
            }
        }
        throw std::runtime_error("Imovel com ID " + std::to_string(idImovel) + " não encontrado.");
    }

    ImovelAlugado getImovelAlugado(vector<ImovelAlugado> imoveisAlugados, int idImovelAlugado) {
        for (int i = 0; i < imoveisAlugados.size(); i++) {
            if (imoveisAlugados.at(i).getId() == idImovelAlugado && this->getId() == imoveisAlugados.at(i).getHospedeId()) {
                return imoveisAlugados.at(i);
            }
        }
        throw std::runtime_error("Imovel alugado com ID " + std::to_string(idImovelAlugado) + " não encontrado.");
    }

    ImovelAlugado alugarImovel(vector<Imovel> imoveis) {
        ImovelAlugado imovelAlugado = this->filtrarImoveis(imoveis);

        this->imoveisAlugados.push_back(imovelAlugado);

        return imovelAlugado;
    }

    ImovelAlugado cancelarReserva(vector<Imovel> imoveis, vector<ImovelAlugado> imoveisAlugados) {
        time_t t = time(0);
        tm* now = localtime(&t);
        Tempo hoje(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
        int idImovelAlugado = 0;
        cout << "==============================\n";
        cout << "     CANCELAMENTO DE RESERVAS\n";
        cout << "==============================\n";
        cout << "Atenção: só é possível cancelar reservas com no mínimo\n";
        cout << "1 semana de antecedência da data de início da estadia.\n";
        this->listarImoveisAlugadosAtivosHospede(imoveis);
        cout << endl << "Digite o id da reserva";
        cin>>idImovelAlugado;

        ImovelAlugado imovel_alugado = this->getImovelAlugado(imoveisAlugados, idImovelAlugado);

        int diasAnterior = hoje.diasAte(imovel_alugado.getDataInicio());

        if (diasAnterior > 7) {
            throw std::runtime_error("O cancelamento da reserva so e possivel com 1 semana de antecedencia");
        }
        imovel_alugado.setAtivo(false);
        return imovel_alugado;
    }

    void listarImoveisAlugadosAtivosHospede(vector<Imovel> imoveis) {
        for (const auto& imovelAlugado : this->imoveisAlugados) {
            if (!imovelAlugado.getAtivo() && this->getId() != imovelAlugado.getHospedeId()) return;
            Imovel imovel = getImovel(imoveis, imovelAlugado.getImovelId());
                cout << "Id da reserva: " << imovel.getId() << endl;
                cout << "Preco da diária: R$ " << imovel.getPrecoDiaria() << endl;
                cout << "Endereço: " << imovel.getEndereco() << endl;
                cout << "Data do aluguel: " << imovelAlugado.getDataInicio().getDia()
                     << "/" << imovelAlugado.getDataInicio().getMes()
                     << "/" << imovelAlugado.getDataInicio().getAno() <<" - "
            << imovelAlugado.getDataFinal().getDia()
            << "/" << imovelAlugado.getDataFinal().getMes()
            << "/" << imovelAlugado.getDataFinal().getAno() << endl;
                cout << "--------------------------------------\n";
        }
    }

    void listarImoveis(const vector<Imovel>& imoveis) {
        for (const auto& imovel : imoveis) {
            cout << "Id do Imovel: " << imovel.getId() << endl;
            cout << "Preco da diária: R$ " << imovel.getPrecoDiaria() << endl;
            cout << "Endereço: " << imovel.getEndereco() << endl;
            cout << "--------------------------------------\n";
        }
    }
};

#endif
