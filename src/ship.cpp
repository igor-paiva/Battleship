#include "ship.hpp"
#include <iostream>

using namespace std;

int Ship::get_size() {
  return size;
}

void Ship::set_size(int size) {
  this->size = size;
}

void Ship::set_coordinates_size() {
  coordinates.reserve(size);
}

void Ship::set_coordinates(string coordinate) {
  coordinates.push_back(coordinate);
}

string Ship::get_hability() {
  return hability;
}

void Ship::set_hability(string hability) {
  this->hability = hability;
}

bool Ship::get_destroyed() {
  return destroyed;
}

void Ship::set_destroyed(bool destroyed) {
  this->destroyed = destroyed;
}
