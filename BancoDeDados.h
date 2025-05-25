#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include "Hospede.h"
#include "Anfitriao.h"
#include "Imovel.h"
#include "Usuario.h"
#include "ImovelAlugado.h"

#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Anfitriao;
class Hospede;

class BancoDeDados {
  vector<Imovel> imoveis;
  vector<Anfitriao> anfitrioes;
  vector<Hospede> hospedes;
  vector<Usuario> usuarios;
  vector<ImovelAlugado> imoveisAlugados;

public:
  BancoDeDados() {
    this->imoveis = vector<Imovel>();
    this->anfitrioes = vector<Anfitriao>();
    this->hospedes = vector<Hospede>();
    this->usuarios = vector<Usuario>();
    this->imoveisAlugados = vector<ImovelAlugado>();

    this->carregarAnfitrioes();
    this->carregarHospedes();
    this->carregarImoveisAlugados();
    this->carregarImoveis();
  };

  vector<Imovel> getImoveis() {return this->imoveis;}
  vector<ImovelAlugado> getImoveisAlugados() {return this->imoveisAlugados;}

  void adicionarImovel(const Imovel& imovel) { this->imoveis.push_back(imovel); }
  void adicionarAnfitriao(const Anfitriao& anfitriao) { this->anfitrioes.push_back(anfitriao); this->usuarios.push_back(anfitriao); }
  void adicionarHospede(const Hospede& hospede) { this->hospedes.push_back(hospede); this->usuarios.push_back(hospede); }
  void adicionarImovelAlugado(const ImovelAlugado &imovelAlugado) { this->imoveisAlugados.push_back(imovelAlugado); }

  void criarAnfitriao(string nome, string senha, int telefone) {
    Anfitriao a(nome, senha, telefone);
    this->adicionarAnfitriao(a);
    this->salvarAnfitriaoArquivo(a);
  }
  void criarHospede(string nome, string senha, int telefone) {
    Hospede h(nome, senha, telefone);
    this->adicionarHospede(h);
    this->salvarHospedeArquivo(h);
  }

  void salvarHospede(Hospede hospede) {
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (this->hospedes.at(i).getId() == hospede.getId()) {
        this->hospedes.at(i) = hospede;
      }
    }
  }

  void salvarImovelAlugado(ImovelAlugado imovel_alugado) {
    for (int i = 0; i < this->imoveisAlugados.size(); i++) {
      if (this->imoveisAlugados.at(i).getId() == imovel_alugado.getId()) {
        this->imoveisAlugados.at(i) = imovel_alugado;
      }
    }
  }

  Hospede getHospede(int idHospede) {
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (this->hospedes.at(i).getId() == idHospede) {
        return this->hospedes.at(i);
      }
    }
    throw std::runtime_error("Hospede com ID " + std::to_string(idHospede) + " não encontrado.");
  }

  Anfitriao getAnfitriao(int idAnfitriao) {
    for (int i = 0; i < this->anfitrioes.size(); i++) {
      if (this->anfitrioes.at(i).getId() == idAnfitriao) {
        return this->anfitrioes.at(i);
      }
    }
    throw std::runtime_error("Anfitrião com ID " + std::to_string(idAnfitriao) + " não encontrado.");
  }

  int logar(string nome, string senha, bool &isAnfitriao, bool &isHospede) {
    for (int i = 0; i < this->anfitrioes.size(); i++) {
      if (nome == this->anfitrioes.at(i).getNome() && senha == this->anfitrioes.at(i).getSenha()) {
        isAnfitriao = true;
        isHospede = false;
        return this->anfitrioes.at(i).getId();
      }
    }
    for (int i = 0; i < this->hospedes.size(); i++) {
      if (nome == this->hospedes.at(i).getNome() && senha == this->hospedes.at(i).getSenha()) {
        isHospede = true;
        isAnfitriao = false;
        return this->hospedes.at(i).getId();
      }
    }

    return -1;
  }

  void carregarHospedes() {
    FILE* arquivo = fopen("hospedes.txt", "r");
    if (!arquivo) return;

    int id, telefone;
    char nome[100], senha[100];

    while (fscanf(arquivo, "%d,%99[^,],%99[^,],%d\n", &id, nome, senha, &telefone) == 4) {
      Hospede h(nome, senha, telefone, id);
      h.setId(id);
      this->adicionarHospede(h);
      Usuario::quantidadeDeUsuarios++;
    }

    fclose(arquivo);
  }

  void salvarHospedeArquivo(Hospede& h) {
    FILE* arquivo = fopen("hospedes.txt", "a"); // modo append
    if (!arquivo) return;

    fprintf(arquivo, "%d,%s,%s,%d\n",
            h.getId(), h.getNome().c_str(), h.getSenha().c_str(), h.getTelefone());

    fclose(arquivo);
  }

  void carregarAnfitrioes() {
    FILE* arquivo = fopen("anfitrioes.txt", "r");
    if (!arquivo) return;

    int id, telefone;
    char nome[100], senha[100];

    while (fscanf(arquivo, "%d,%99[^,],%99[^,],%d\n", &id, nome, senha, &telefone) == 4) {
      Hospede h(nome, senha, telefone, id);
      Usuario::quantidadeDeUsuarios++;
      this->adicionarHospede(h);
    }

    fclose(arquivo);
  }

  void carregarImoveisAlugados() {
    FILE* arquivo = fopen("imoveisAlugados.txt", "r");
    if (!arquivo) return;

    int id, imovelId, hospedeId;
    int diaInicio, mesInicio, anoInicio;
    int diaFinal, mesFinal, anoFinal;
    int ativoInt; // bool como int

    while (fscanf(arquivo, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                  &id, &imovelId, &hospedeId,
                  &diaInicio, &mesInicio, &anoInicio,
                  &diaFinal, &mesFinal, &anoFinal,
                  &ativoInt) == 10) {

      bool ativo = (ativoInt != 0);
      ImovelAlugado::quantidadeDeImoveisAlugados++;
      ImovelAlugado i(imovelId, hospedeId,
                      diaInicio, mesInicio, anoInicio,
                      diaFinal, mesFinal, anoFinal,
                      ativo, id);

      this->adicionarImovelAlugado(i);
                  }

    fclose(arquivo);
  }

  void salvarImovelAlugadoArquivo(ImovelAlugado& i) {
    FILE* arquivo = fopen("imoveisAlugados.txt", "a");
    if (!arquivo) return;

    fprintf(arquivo, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
            i.getId(), i.getImovelId(), i.getHospedeId(),
            i.getDataInicio().getDia(), i.getDataInicio().getMes(), i.getDataInicio().getAno(),
            i.getDataFinal().getDia(), i.getDataFinal().getMes(), i.getDataFinal().getAno(),
            i.getAtivo() ? 1 : 0);

    fclose(arquivo);
  }

  void reescreverImoveisAlugadosArquivo() {
    FILE* arquivo = fopen("imoveisAlugados.txt", "w"); // sobrescreve tudo
    if (!arquivo) return;

    for (int i = 0; i < imoveisAlugados.size(); i++) {
      ImovelAlugado& iAlugado = imoveisAlugados.at(i);
      fprintf(arquivo, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
              iAlugado.getId(), iAlugado.getImovelId(), iAlugado.getHospedeId(),
              iAlugado.getDataInicio().getDia(), iAlugado.getDataInicio().getMes(), iAlugado.getDataInicio().getAno(),
            iAlugado.getDataFinal().getDia(), iAlugado.getDataFinal().getMes(), iAlugado.getDataFinal().getAno(),
              iAlugado.getAtivo() ? 1 : 0);
    }

    fclose(arquivo);
  }

  void carregarImoveis() {
    FILE* arquivo = fopen("imoveis.txt", "r");
    if (!arquivo) return;

    int id, anfitriaoId, tipoImovelInt, capacidade;
    float precoDiaria;
    char endereco[100];
    while (fscanf(arquivo, "%d,%d,%99[^,],%d,%d,%f\n",
                  &id, &anfitriaoId, endereco,
                  &tipoImovelInt, &capacidade, &precoDiaria) == 6) {

      TiposImovel tipoImovel = intToTipos(tipoImovelInt);
      Imovel::quantidadeDeImoveis++;
      Imovel i(endereco, tipoImovel, capacidade, precoDiaria, anfitriaoId, id);

      this->adicionarImovel(i);}


    fclose(arquivo);
  }

  void salvarImovelArquivo(Imovel& i) {
    FILE* arquivo = fopen("imoveis.txt", "a");
    if (!arquivo) return;

    fprintf(arquivo, "%d,%d,%s,%d,%d,%.2f\n",
            i.getId(), i.getAnfitriaoResponsavelId(), i.getEndereco().c_str(),
            tipoToInt(i.getTipo()), i.getCapacidade(), i.getPrecoDiaria());

    fclose(arquivo);
  }

  void salvarAnfitriaoArquivo(Anfitriao& a) {
    FILE* arquivo = fopen("anfitrioes.txt", "a"); // modo append
    if (!arquivo) return;

    fprintf(arquivo, "%d,%s,%s,%d\n",
            a.getId(), a.getNome().c_str(), a.getSenha().c_str(), a.getTelefone());

    fclose(arquivo);
  }
};

#endif