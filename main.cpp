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
        Anfitriao anfitriaoLogado = bancoDeDados.getAnfitriao(idUsuarioLogado);
        anfitriaoLogado.greet();
        cout << "1 - Criar Imovel\n2 - Ver seus imoveis\n3 - Deslogar";
        cin>>option;

        switch (option) {
          case 1:
            limparTela();
          {
            Imovel imovelCriado = anfitriaoLogado.criarImovel();
            bancoDeDados.salvarImovelArquivo(imovelCriado);
            bancoDeDados.adicionarImovel(imovelCriado);
          }
            break;
          case 2:
            limparTela();
            anfitriaoLogado.listarImoveisCriados(bancoDeDados.getImoveis());
            break;
          case 3:
            limparTela();
            isAnfitriao = false;
            idUsuarioLogado = -1;
        }
      }
      while (isHospede) {
        Hospede hospedeLogado = bancoDeDados.getHospede(idUsuarioLogado);
        hospedeLogado.greet();
        cout << "1 - Reservar um Imovel\n2 - Ver suas reservas\n3 - Cancelar uma reserva\n4 - Deslogar";
        cin>>option;
        switch (option) {
          case 1:
            limparTela();
          {
            ImovelAlugado imovelAlugado = hospedeLogado.alugarImovel(bancoDeDados.getImoveis(), bancoDeDados.getImoveisAlugados());
            bancoDeDados.salvarHospede(hospedeLogado);
            bancoDeDados.adicionarImovelAlugado(imovelAlugado);
            bancoDeDados.salvarImovelAlugadoArquivo(imovelAlugado);
          }
          break;
          case 2:
            limparTela();
             hospedeLogado.listarImoveisAlugadosAtivosHospede(bancoDeDados.getImoveis(), bancoDeDados.getImoveisAlugados());
          break;
          case 3:
            limparTela();
          {
            ImovelAlugado imovelCancelado = hospedeLogado.cancelarReserva(bancoDeDados.getImoveis(), bancoDeDados.getImoveisAlugados());
            bancoDeDados.salvarImovelAlugado(imovelCancelado);
            bancoDeDados.reescreverImoveisAlugadosArquivo();
          }

          break;
          case 4:
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
}
