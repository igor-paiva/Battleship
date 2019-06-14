#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include <string>
#include <vector>

#include "ship.hpp"

using namespace std;

class Submarine : public Ship {
  private:
    vector<string> received_shots;

    void set_received_shots_size();
    bool shooted_twice(string coordinate);
  public:
    Submarine();
    ~Submarine() = default;

    void set_received_shots(string coordinate1, string coordinate2);

    bool get_destroyed();
    int receive_shot(string coordinate);
};

#endif
