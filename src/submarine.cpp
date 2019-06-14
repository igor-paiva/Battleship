#include "submarine.hpp"
#include <iostream>

using namespace std;

Submarine::Submarine() {
  string hability = "Cada casa tem de ser atingida duas vezes para ser abatida.";
  int size = 2;
  bool destroyed = false;

  set_hability(hability);
  set_size(size);
  set_destroyed(destroyed);
  set_coordinates_size();
}

void Submarine::set_received_shots_size() {
  received_shots.reserve(this->get_size());
}

void Submarine::set_received_shots(string coordinate1, string coordinate2) {
  coordinate1.append("0");
  coordinate2.append("0");

  received_shots.push_back(coordinate1);
  received_shots.push_back(coordinate2);
}

bool Submarine::shooted_twice(string coordinate) {
  string hits;

  for (int i = 0; i < this->get_size(); i++) {
    if (coordinates[i].compare(coordinate) == 0) {
      hits = received_shots[i];

      if (hits[4] == '2') { return true; }
    }
  }

  return false;
}

bool Submarine::get_destroyed() {
  string hits1 = received_shots[0];
  string hits2 = received_shots[1];

  bool destroyed = hits1[4] == '2' && hits2[4] == '2';

  if (destroyed) { set_destroyed(true); }

  return destroyed;
}

int Submarine::receive_shot(string coordinate) {
  string received_shot, ship_coordinate;
  int hits, compare;

  for (int i = 0; i < this->get_size(); i++) {
    ship_coordinate = coordinates[i];

    compare = ship_coordinate.compare(coordinate);

    if (compare == 0) {
      if (shooted_twice(coordinate)) { return -1; }

      received_shot = received_shots[i];

      hits = received_shot[4] - '0';
      hits++;

      received_shots[i] = coordinate + to_string(hits);

      return 1;
    }
  }

  return 0;
}
