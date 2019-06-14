#include <iostream>

#include "map.hpp"

using namespace std;

const string initial_path = "doc/";

Map::Map() {
  int map_number;

  cout << "Opções de mapas: \n" << endl;
  cout << "1) Mapa 1" << endl;
  cout << "2) Mapa 2" << endl;
  cout << "3) Mapa 3" << endl;

  do {
    cout << "\nDigite o número do mapa em que deseja jogar: ";
  } while(!(cin >> map_number) || map_number < 1 || map_number > 3);

  cout << "\n";

  set_number(map_number);

  create_ships_file(1);
  create_ships_file(2);

  set_board_lines();

  system("clear");
}

void Map::set_board_lines() {
  int i, x = 0;
  string line;

  player_1_board_lines[0] = "    0  1  2  3  4  5  6  7  8  9 10 11 12\n\n";
  player_2_board_lines[0] = "    0  1  2  3  4  5  6  7  8  9 10 11 12\n\n";

  for (i = 1; i < 14; i++) {
    if (i == 11 || i == 12 || i == 13) {
      line = to_string(x) + "  0  0  0  0  0  0  0  0  0  0  0  0  0\n";
    } else {
      line = "0" + to_string(x) + "  0  0  0  0  0  0  0  0  0  0  0  0  0\n";
    }

    player_1_board_lines[i] = line;
    player_2_board_lines[i] = line;

    x++;
  }
}

int Map::get_number() {
  return number;
}

void Map::set_number(int number) {
  this->number = number;
}

void Map::set_shooted_ship(string coordinate, char ship_type, int player_number) {
  int position;
  string line, x_string, y_string;
  string::size_type size;

  x_string.push_back(coordinate[0]);
  x_string.push_back(coordinate[1]);

  y_string.push_back(coordinate[3]);
  y_string.push_back(coordinate[4]);

  int x = stoi (x_string, &size);
  int y = stoi (y_string, &size);

  position = 3*y + 4;

  x += 1;
  switch (player_number) {
    case 1:
      line = player_1_board_lines[x];

      line[position] = ship_type;

      player_1_board_lines[x] = line;

      break;
    case 2:
      line = player_2_board_lines[x];

      line[position] = ship_type;

      player_2_board_lines[x] = line;
      break;
  }
}

void Map::print_game_board_map(int player_number) {
  cout << "Campo do Player " << player_number << ":\n" << endl;

  for (int i = 0; i < 14; i++) {
    switch (player_number) {
      case 1:
        cout << player_1_board_lines[i];

        break;
      case 2:
        cout << player_2_board_lines[i];

        break;
    }
  }

  cout << "\n";
}


string Map::get_ships_map_file_path(string player_number) {
  string path, file_name;

  path = initial_path + "temp_map_player";

  file_name = path + "_" + player_number + ".txt";

  return file_name;
}

void Map::create_ships_file(int player_number) {
  int k = 0;
  bool finded = false;
  string file_name, find_player, player, player_number_string;

  ofstream map_player;

  file_name = initial_path + "map_" + to_string(number) + ".txt";

  map.open(file_name);

  if (!map) {
    cout << "Houve algum erro." << endl;
    exit(1);
  }

  player_number_string = to_string(player_number);

  map_player.open(get_ships_map_file_path(player_number_string));

  if (!map_player) {
    cout << "Houve algum erro." << endl;
    exit(1);
  }

  player = "# player_" + player_number_string;

  while (getline(map, find_player)) {
    if (find_player.compare(player) == 0) {
      finded = true;

      continue;
    }

    if (player_number == 1 && finded && k < 20) {
      map_player << find_player << endl;
    }

    if (player_number == 2 && finded && k > 21) {
      map_player << find_player << endl;
    }

    k++;
  }

  map.close();
  map_player.close();
}
