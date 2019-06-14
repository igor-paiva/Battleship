#include "boat.hpp"
#include <iostream>

using namespace std;

Boat::Boat() {
  string hability = "Nenhuma.";
  int size = 1;
  bool destroyed = false;

  set_hability(hability);
  set_size(size);
  set_destroyed(destroyed);
}

bool Boat::receive_shot(string coordinate) {
  int compare = coordinates[0].compare(coordinate);

  if (compare != 0) { return false; }

  set_destroyed(true);

  return true;
}
