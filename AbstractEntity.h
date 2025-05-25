#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

using namespace std;


class AbstractEntity {
  long id;

public:
  AbstractEntity(long id) { this->id = id + 1; }

  AbstractEntity(long id, bool sobrecarga) { this->id = id; }

  long getId() const { return this->id; }
  void setId(long id) { this->id = id; }
};

#endif