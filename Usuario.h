#ifndef USUARIO_H
#define USUARIO_H

#include "AbstractEntity.h"
#include <string>

using namespace std;

class Usuario : public AbstractEntity {
  string nome;
  string senha;
  int telefone;
  static int quantidadeDeUsuarios;

public:
  Usuario(string nome, string senha, int telefone) : AbstractEntity(quantidadeDeUsuarios) {
    quantidadeDeUsuarios++;
    this->nome = nome;
    this->senha = senha;
    this->telefone = telefone;
  }

  string getNome() { return this->nome; }
  string getSenha() { return this->senha; }
  int getTelefone() { return this->telefone; }
  void setNome(string nome) { this->nome = nome; }
  void setTelefone(int telefone) { this->telefone = telefone; }
};

int Usuario::quantidadeDeUsuarios = 0;

#endif