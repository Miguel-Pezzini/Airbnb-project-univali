#ifndef DIALOGOS_H
#define DIALOGOS_H

#include "BancoDeDados.h"

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
    } else if (opcao_usuario == 2) {
        bancoDeDados.criarHospede(nome_usuario, senha, telefone);
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
        cout << "Seu login foi bem sucedido!";
    }

    return id_usuario_logado;
}

void criarImovel(BancoDeDados &bancoDeDados, int idUsuarioLogado) {

}
#endif
