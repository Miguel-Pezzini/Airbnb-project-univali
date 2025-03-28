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
        cout << "1 - Criar Imovel\n2 - Ver seus imoveis\n3 - Editar algum imovel \n4 - Excluir algum imovel \n5- Sair";
        cin>>option;

        switch (option) {
          case 1:
            criarImovel(bancoDeDados, idUsuarioLogado);
            break;
          case 2:
            bancoDeDados.listarImoveis(idUsuarioLogado);
            break;
        }
      }
      if (isHospede) {}
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
