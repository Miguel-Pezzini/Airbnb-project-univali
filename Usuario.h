#ifndef USUARIO_H
#define USUARIO_H

#include "AbstractEntity.h"
#include <string>

using namespace std;

class Usuario : public AbstractEntity {
  string nome;
  string senha;
  int telefone;


public:
  static int quantidadeDeUsuarios;
  Usuario(string nome, string senha, int telefone) : AbstractEntity(quantidadeDeUsuarios) {
    quantidadeDeUsuarios++;
    this->nome = nome;
    this->senha = senha;
    this->telefone = telefone;
  }

  Usuario(string nome, string senha, int telefone, int usuarioId) : AbstractEntity(usuarioId, true) {
    this->nome = nome;
    this->senha = senha;
    this->telefone = telefone;
  }
  string getNome() { return this->nome; }
  string getSenha() { return this->senha; }
  int getTelefone() { return this->telefone; }
  void setNome(string nome) { this->nome = nome; }
  void setTelefone(int telefone) { this->telefone = telefone; }

  void greet() {
    cout << "Olá, usuário " << this->getNome() << "!" << endl;
  }
};

int Usuario::quantidadeDeUsuarios = 0;

#endif