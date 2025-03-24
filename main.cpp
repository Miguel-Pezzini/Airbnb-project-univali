#include "BancoDeDados.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main() {
  BancoDeDados bancoDeDados;

  while (true) {
    int opcao;
    cout << "1 - Criar conta\n2 - Entrar na conta\n3 - Sair";
    cin >> opcao;

    switch (opcao) {
    case 1:
      string nome, senha;
      int telefone, opcaoUsuario;
      cout << "Digite seu nome: ";
      cin >> nome;
      cout << "Digite sua senha: ";
      cin >> nome;
      cout << "Digite seu telefone: ";
      cin >> telefone;
      cout << "Qual seu tipo de usuário?\n1 - Anfitrião\n2 - Hóspede";
      cin >> opcaoUsuario;
      if (opcaoUsuario == 1) {
        bancoDeDados.criarAnfitriao(nome, senha, telefone);
      } else if (opcaoUsuario == 2) {
        bancoDeDados.criarHospede(nome, senha, telefone);
      }
      break;
    }
  }
  return 0;
}
