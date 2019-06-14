#include "aero_carrier.hpp"
#include <iostream>

using namespace std;

AeroCarrier::AeroCarrier() {
  string hability = "Ao ser acertado, pode, randomicamente, abater o míssil, e por isso não ser afetado.";

  int size = 4;
  bool destroyed = false;

  set_hability(hability);
  set_size(size);
  set_destroyed(destroyed);
  set_coordinates_size();
}

void AeroCarrier::set_received_shots_size() {
  received_shots.reserve(this->get_size());
}

void AeroCarrier::set_received_shots(string coordinate1, string coordinate2,
  string coordinate3, string coordinate4) {

  coordinate1.append("0");
  coordinate2.append("0");
  coordinate3.append("0");
  coordinate4.append("0");

  received_shots.push_back(coordinate1);
  received_shots.push_back(coordinate2);
  received_shots.push_back(coordinate3);
  received_shots.push_back(coordinate4);
}

bool AeroCarrier::defend() {
  int random;

  srand(time(0));

  random = rand() % 2 + 1;

  if (random == 1) { return true; }

  return false;
}

bool AeroCarrier::already_shooted(string coordinate) {
  string hits;

  for (int i = 0; i < this->get_size(); i++) {
    if (coordinates[i].compare(coordinate) == 0) {
      hits = received_shots[i];

      if (hits[4] == '1') { return true; }
    }
  }

  return false;
}

bool AeroCarrier::get_destroyed() {
  string hits1 = received_shots[0];
  string hits2 = received_shots[1];
  string hits3 = received_shots[2];
  string hits4 = received_shots[3];

  bool destroyed = hits1[4] == '1' && hits2[4] == '1' && hits3[4] == '1' && hits4[4] == '1' ;

  if (destroyed) { set_destroyed(true); }

  return destroyed;
}

int AeroCarrier::receive_shot(string coordinate) {
  string received_shot, ship_coordinate;
  int hits, compare;

  for (int i = 0; i < this->get_size(); i++) {
    ship_coordinate = coordinates[i];

    compare = ship_coordinate.compare(coordinate);

    if (compare == 0) {
      if (already_shooted(coordinate)) { return -2; }

      if (defend()) { return -1; }

      received_shot = received_shots[i];

      hits = received_shot[4] - '0';
      hits++;

      received_shots[i] = coordinate + to_string(hits);

      return 1;
    }
  }

  return 0;
}
