#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>

using namespace std;

class Ship {
  private:
    int size;
    string hability;
    bool destroyed;

  public:
    vector<string> coordinates;

    int get_size();
    void set_size(int size);

    void set_coordinates_size();
    void set_coordinates(string coordinate);

    string get_hability();
    void set_hability(string hability);

    bool get_destroyed();
    void set_destroyed(bool destroyed);
};

#endif
