#include "dialogos.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  BancoDeDados bancoDeDados;
  int idUsuarioLogado = -1;
  bool isAnfitriao, isHospede;

  while (true) {
    int option;
    if (idUsuarioLogado > 0) {
      while (isAnfitriao) {
        cout << "1 - Criar Imovel\n2 - Ver seus imoveis\n3 - Sair";
        cin>>option;

        switch (option) {
          case 1:
            limparTela();
            criarImovel(bancoDeDados, idUsuarioLogado);
            break;
          case 2:
            limparTela();
            listarImoveisCriados(bancoDeDados, idUsuarioLogado);
            break;
          case 3:
            limparTela();
            isAnfitriao = false;
            idUsuarioLogado = -1;
        }
      }
      while (isHospede) {
        cout << "1 - Alugar um Imovel\n2 - Ver seus imoveis alugados\n3 - Sair";
        cin>>option;
        switch (option) {
          case 1:
            limparTela();
            alugarImovel(bancoDeDados, idUsuarioLogado);
          break;
          case 2:
            limparTela();
            listarImoveisAlugados(bancoDeDados, idUsuarioLogado);
          break;
          case 3:
            limparTela();
            isHospede = false;
           idUsuarioLogado = -1;
          break;
        }
      }
    }
    cout << "1 - Criar conta\n2 - Entrar na conta\n3 - Sair";
    cin >> option;

    switch (option) {
      case 1:
        criarUsuario(bancoDeDados);
      break;
      case 2:
        idUsuarioLogado = logarUsuario(bancoDeDados, isAnfitriao, isHospede);
        break;
      case 3:
        return 0;
    }
  }
  return 0;
}
