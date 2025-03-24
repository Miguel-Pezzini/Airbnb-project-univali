#ifndef USUARIO_H
#define USUARIO_H

#include "AbstractEntity.h"
#include <string>

using namespace std;

class Usuario : public AbstractEntity {
  string nome;
  int telefone;
  static int quantidadeDeUsuarios;

public:
  Usuario(string nome, int telefone) : AbstractEntity(quantidadeDeUsuarios) {
    quantidadeDeUsuarios++;
    this->nome = nome;
    this->telefone = telefone;
  }

  string getNome() { return this->nome; }
  int getTelefone() { return this->telefone; }
  void setNome(string nome) { this->nome = nome; }
  void setTelefone(int telefone) { this->telefone = telefone; }
};

int Usuario::quantidadeDeUsuarios = 0;

#endif