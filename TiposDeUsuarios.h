#ifndef TIPOSDEUSUARIOS_H
#define TIPOSDEUSUARIOS_H

#include "Imovel.h"
#include "Usuario.h"
#include <iostream>
#include <vector>

class Anfitriao : public Usuario {

public:
  Anfitriao(string nome, string senha, int telefone) : Usuario(nome, senha, telefone) {}
};

class Hospede : public Usuario {

public:
  Hospede(string nome, string senha, int telefone) : Usuario(nome, senha, telefone){};
};

#endif