#ifndef DIALOGOS_H
#define DIALOGOS_H

#include "BancoDeDados.h"

void limparTela() {
    cout << string(50, '\n'); // Imprime 50 quebras de linha
}

void criarUsuario(BancoDeDados &bancoDeDados) {
    string nome_usuario, senha;
    int opcao_usuario, telefone;
    cout << "Digite seu nome: ";
    cin >> nome_usuario;
    cout << "Digite sua senha: ";
    cin >> senha;
    cout << "Digite seu telefone: ";
    cin >> telefone;
    cout << "Qual seu tipo de usuário?\n1 - Anfitrião\n2 - Hóspede";
    cin >> opcao_usuario;
    if (opcao_usuario == 1) {
        bancoDeDados.criarAnfitriao(nome_usuario, senha, telefone);
        limparTela();
    } else if (opcao_usuario == 2) {
        bancoDeDados.criarHospede(nome_usuario, senha, telefone);
        limparTela();
    }
}

int logarUsuario(BancoDeDados bancoDeDados, bool &isAnfitriao, bool &isHospede) {
    string nomeUsuario, senha;
    cout << "Digite seu nome: ";
    cin >> nomeUsuario;
    cout << "Digite sua senha: ";
    cin >> senha;
    int id_usuario_logado = bancoDeDados.logar(nomeUsuario, senha, isAnfitriao, isHospede);
    if (id_usuario_logado == -1) {
        cout << "Verifique suas credenciais e tente novamente\n";
    } else {
        limparTela();
        cout << "Seu login foi bem sucedido!\n\n";
    }

    return id_usuario_logado;
}

void criarImovel(BancoDeDados &bancoDeDados, int idUsuarioLogado) {
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

    bancoDeDados.criarImovel(endereco, intToTipos(tipo), capacidade, precoDiaria, idUsuarioLogado, dia, mes, ano);
}

void listarImoveisCriados(BancoDeDados banco_de_dados, int idUsuarioLogado) {
    banco_de_dados.listarImoveisCriadosDoUsuario(idUsuarioLogado);
}

void alugarImovel(BancoDeDados &banco_de_dados, int idUsuarioLogado) {
    int idImovel;
    vector<Imovel> imoveisFiltrados =  banco_de_dados.filtrarImoveis();

    banco_de_dados.listarImoveis(imoveisFiltrados);

    cout<<"Digite o id do imovel que voce deseja alugar: ";
    cin>>idImovel;

    banco_de_dados.alugarImovel(idImovel, idUsuarioLogado);
}

void listarImoveisAlugados(BancoDeDados banco_de_dados, int idUsuarioLogado) {
    banco_de_dados.listarImoveisAlugadosDoUsuario(idUsuarioLogado);
}
#endif
