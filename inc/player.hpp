#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "boat.hpp"
#include "submarine.hpp"
#include "aero_carrier.hpp"

using namespace std;

class Player {
  private:
    int number;
    string name;
    bool winner;

    Player();

    bool is_number(char c);
    int beginning_of_direction_in_file(string &data);
    void ajust_file_coordinates(string &x_string, string &y_string, string &boat_data);

    string get_map_file_path();

    void set_boat_coordinate(int boat_number);
    void set_boats(Boat *boats);

    void find_submarine_coordinate(int submarine_number);
    void set_submarines(Submarine *submarines);
    void set_submarines_coordinates(int submarine_index, string direction,
      string x_string, string y_string);

    void find_aero_carrier_coordinate(int aero_carrier_number);
    void set_aero_carriers(AeroCarrier *aero_carriers);
    void set_aero_carriers_coordinates(int aero_carrier_index, string direction,
      string x_string, string y_string);

  public:
    Boat boats[6];
    Submarine submarines[4];
    AeroCarrier aero_carriers[2];

    Player(int number);
    ~Player() = default;

    string get_name();
    string set_name();

    bool get_winner();
    void set_winner(bool winner);

    int get_number();

    void set_ships(Boat *boats, Submarine *submarines, AeroCarrier *aero_carriers);

    string attack();
};

#endif
