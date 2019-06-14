#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <fstream>

using namespace std;

class Map {
  private:
    int number;
    ifstream map;
    string player_1_board_lines[14];
    string player_2_board_lines[14];

    string get_ships_map_file_path(string player_number);

    void create_ships_file(int player_number);

    void set_board_lines();
  public:
    Map();
    ~Map() = default;

    void print_game_board_map(int player_number);

    int get_number();
    void set_number(int number);

    void set_shooted_ship(string coordinate, char ship_type, int player_number);
};

#endif
