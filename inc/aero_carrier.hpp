#ifndef AEROCARRIER_HPP
#define AEROCARRIER_HPP

#include <string>
#include <stdlib.h>
#include <time.h>

#include "ship.hpp"

using namespace std;

class AeroCarrier : public Ship {
  private:
    vector<string> received_shots;

    bool defend();
    void set_received_shots_size();
    bool already_shooted(string coordinate);
  public:
    AeroCarrier();
    ~AeroCarrier() = default;

    void set_received_shots(string coordinate1, string coordinate2,
      string coordinate3, string coordinate4);

    bool get_destroyed();
    int receive_shot(string coordinate);
};

#endif
