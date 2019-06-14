#ifndef BOAT_HPP
#define BOAT_HPP

#include <string>
#include "ship.hpp"

using namespace std;

class Boat: public Ship{
  public:
    Boat();
    ~Boat() = default;

    bool receive_shot(string coordinate);
};

#endif
