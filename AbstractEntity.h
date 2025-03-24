#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <string>

using namespace std;

class AbstractEntity {
  long id;

public:
  AbstractEntity(long id) { this->id = id + 1; }

  long getId() { return this->id; }
};

#endif