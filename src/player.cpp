#include "boat.hpp"
#include "player.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Player::Player(int number) {
  this->number = number;

  name = this->set_name();
}

bool Player::get_winner() {
  return winner;
}

void Player::set_winner(bool winner) {
  this->winner = winner;
}

int Player::get_number() {
  return number;
}

string Player::get_name() {
  return name;
}

string Player::set_name() {
  string name;
  bool invalid;

  do {
    cout << "Player " << to_string(number) << " digite seu nome: ";
    cin >> name;

    invalid = (name[0] == '1' || name[0] == '2' || name[0] == '3' || name[0] == '4' ||
      name[0] == '5' || name[0] == '6' || name[0] == '7' || name[0] == '8' ||
      name[0] == '9' || name[0] == '0') || name.size() == 1;

    if (invalid) {
      system("clear");

      cout << "Não pode começar com número e tem que ter mais de 1 carácter.\n" << endl;
    }
  } while (invalid);

  return name;
}

void Player::set_ships(Boat *boats, Submarine *submarines, AeroCarrier *aero_carriers) {
  set_boats(boats);
  set_submarines(submarines);
  set_aero_carriers(aero_carriers);

  string file_name = get_map_file_path();

  if (remove(file_name.c_str()) != 0) {
    cout << "Deu ruim!" << endl;
    exit(1);
  }
}

void Player::set_boats(Boat *boats) {
  for (int i = 0; i < 6; i++) {
    this->boats[i] = boats[i];

    set_boat_coordinate(i+1);
  }
}

void Player::set_submarines(Submarine *submarines) {
  for (int i = 0; i < 4; i++) {
    this->submarines[i] = submarines[i];

    find_submarine_coordinate(i+1);
  }
}

void Player::set_aero_carriers(AeroCarrier *aero_carriers) {
  for (int i = 0; i < 2; i++) {
    this->aero_carriers[i] = aero_carriers[i];

    find_aero_carrier_coordinate(i+1);
  }
}

string Player::get_map_file_path() {
  string path, file_name, player_number_string;

  path = "doc/temp_map_player";

  player_number_string = to_string(this->number);

  file_name = path + "_" + player_number_string + ".txt";

  return file_name;
}

bool Player::is_number(char c) {
  bool response = (c == '0' || c == '1' || c == '2' || c == '3' || c == '4'
    || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');

  return response;
}

void Player::ajust_file_coordinates(string &x_string, string &y_string, string &data) {
  x_string.push_back(data[0]);

  if (!is_number(data[1])) {
    x_string.insert(0, "0");

    y_string.push_back(data[2]);

    if (!is_number(data[3])) {
      y_string.insert(0, "0");
    } else {
      y_string.push_back(data[3]);
    }
  } else {
    x_string.push_back(data[1]);

    y_string.push_back(data[3]);

    if (!is_number(data[4])) {
      y_string.insert(0, "0");
    } else {
      y_string.push_back(data[4]);
    }
  }
}

void Player::set_boat_coordinate(int boat_number) {
  int k = 0;
  int boat_index = boat_number - 1;
  string line, boat_data, coordinate;
  string x_string = "", y_string = "";

  ifstream map;

  map.open(get_map_file_path());

  if (!map) {
    cout << "Houve algum erro." << endl;
    exit(1);
  }

  while (getline(map, line) && k < 6) {
    if (k == boat_index) {
      boat_data = line;
    }

    k++;
  }

  map.close();

  ajust_file_coordinates(x_string, y_string, boat_data);

  coordinate = x_string + y_string;

  this->boats[boat_index].set_coordinates(coordinate);
}

int Player::beginning_of_direction_in_file(string &data) {
  int i = 0, number_of_spaces = 0, beginning_of_direction;

  while (data[i] != '\n') {
    if (number_of_spaces == 3) {
      beginning_of_direction = i;

      break;
    }

    if (data[i] == ' ') {
      number_of_spaces++;
    }

    i++;
  }

  return beginning_of_direction;
}

void Player::set_submarines_coordinates(int submarine_index, string direction,
  string x_string, string y_string) {

  string other_x, other_y, coordinate1, coordinate2;
  string::size_type size;

  int x = stoi (x_string, &size);
  int y = stoi (y_string, &size);

  if (direction.compare("direita") == 0) {
    other_y = to_string(y+1);

    coordinate1 = x_string + y_string;

    if (other_y.size() == 2) { coordinate2 = x_string + other_y; }
    if (other_y.size() == 1) { coordinate2 = x_string + "0" + other_y; }
  }
  else if (direction.compare("esquerda") == 0) {
    other_y = to_string(y-1);

    coordinate1 = x_string + y_string;

    if (other_y.size() == 2) { coordinate2 = x_string + other_y; }
    if (other_y.size() == 1) { coordinate2 = x_string + "0" + other_y; }
  }
  else if (direction.compare("cima") == 0) {
    other_x = to_string(x-1);

    coordinate1 = x_string + y_string;

    if (other_x.size() == 2) { coordinate2 = other_x + y_string; }
    if (other_x.size() == 1) { coordinate2 = "0" + other_x + y_string; }
  }
  else if (direction.compare("baixo") == 0) {
    other_x = to_string(x+1);

    coordinate1 = x_string + y_string;

    if (other_x.size() == 2) { coordinate2 = other_x + y_string; }
    if (other_x.size() == 1) { coordinate2 = "0" + other_x + y_string; }
  }

  this->submarines[submarine_index].set_received_shots(coordinate1, coordinate2);

  this->submarines[submarine_index].set_coordinates(coordinate1);
  this->submarines[submarine_index].set_coordinates(coordinate2);
}

void Player::find_submarine_coordinate(int submarine_number) {
  int j, k = 0, size_data;
  int submarine_index = submarine_number - 1;
  bool within_range;
  string line, submarine_data;
  string x_string = "", y_string = "", direction = "";

  ifstream map;

  map.open(get_map_file_path());

  if (!map) {
    cout << "Houve algum erro." << endl;
    exit(1);
  }

  while (getline(map, line)) {
    within_range = k > 6 && k < 11;

    if (k == 6 + submarine_number && within_range) {
      submarine_data = line;
    }

    k++;
  }

  map.close();

  ajust_file_coordinates(x_string, y_string, submarine_data);

  size_data = submarine_data.size();

  int beginning_of_direction = beginning_of_direction_in_file(submarine_data);

  for (j = beginning_of_direction; j < size_data; j++) {
    direction.push_back(submarine_data[j]);
  }

  set_submarines_coordinates(submarine_index, direction, x_string, y_string);
}


void Player::set_aero_carriers_coordinates(int aero_carrier_index, string direction,
  string x_string, string y_string) {

  string x2, x3, x4, y2, y3, y4;
  string coordinate1, coordinate2, coordinate3, coordinate4;
  string::size_type size;

  int x = stoi (x_string, &size);
  int y = stoi (y_string, &size);

  coordinate1 = x_string + y_string;

  if (direction.compare("direita") == 0) {
    y2 = to_string(y+1);
    y3 = to_string(y+2);
    y4 = to_string(y+3);

    if (y2.size() == 2) { coordinate2 = x_string + y2; }
    if (y2.size() == 1) { coordinate2 = x_string + "0" + y2; }

    if (y3.size() == 2) { coordinate3 = x_string + y3; }
    if (y3.size() == 1) { coordinate3 = x_string + "0" + y3; }

    if (y4.size() == 2) { coordinate4 = x_string + y4; }
    if (y4.size() == 1) { coordinate4 = x_string + "0" + y4; }
  }
  else if (direction.compare("esquerda") == 0) {
    y2 = to_string(y-1);
    y3 = to_string(y-2);
    y4 = to_string(y-3);

    if (y2.size() == 2) { coordinate2 = x_string + y2; }
    if (y2.size() == 1) { coordinate2 = x_string + "0" + y2; }

    if (y3.size() == 2) { coordinate3 = x_string + y3; }
    if (y3.size() == 1) { coordinate3 = x_string + "0" + y3; }

    if (y4.size() == 2) { coordinate4 = x_string + y4; }
    if (y4.size() == 1) { coordinate4 = x_string + "0" + y4; }
  }
  else if (direction.compare("cima") == 0) {
    x2 = to_string(x-1);
    x3 = to_string(x-2);
    x4 = to_string(x-3);

    if (x2.size() == 2) { coordinate2 = x2 + y_string; }
    if (x2.size() == 1) { coordinate2 = "0" + x2 + y_string; }

    if (x3.size() == 2) { coordinate3 = x3 + y_string; }
    if (x3.size() == 1) { coordinate3 = "0" + x3 + y_string; }

    if (x4.size() == 2) { coordinate4 = x4 + y_string; }
    if (x4.size() == 1) { coordinate4 = "0" + x4 + y_string; }
  }
  else if (direction.compare("baixo") == 0) {
    x2 = to_string(x+1);
    x3 = to_string(x+2);
    x4 = to_string(x+3);

    if (x2.size() == 2) { coordinate2 = x2 + y_string; }
    if (x2.size() == 1) { coordinate2 = "0" + x2 + y_string; }

    if (x3.size() == 2) { coordinate3 = x3 + y_string; }
    if (x3.size() == 1) { coordinate3 = "0" + x3 + y_string; }

    if (x4.size() == 2) { coordinate4 = x4 + y_string; }
    if (x4.size() == 1) { coordinate4 = "0" + x4 + y_string; }
  }

  this->aero_carriers[aero_carrier_index].set_received_shots(coordinate1, coordinate2,
    coordinate3, coordinate4);

  this->aero_carriers[aero_carrier_index].set_coordinates(coordinate1);
  this->aero_carriers[aero_carrier_index].set_coordinates(coordinate2);
  this->aero_carriers[aero_carrier_index].set_coordinates(coordinate3);
  this->aero_carriers[aero_carrier_index].set_coordinates(coordinate4);
}

void Player::find_aero_carrier_coordinate(int aero_carrier_number) {
  int j, k = 0, size_data;
  int aero_carrier_index = aero_carrier_number - 1;
  bool within_range;
  string line, aero_carrier_data;
  string x_string = "", y_string = "", direction = "";

  ifstream map;

  map.open(get_map_file_path());

  if (!map) {
    cout << "Houve algum erro." << endl;
    exit(1);
  }

  while (getline(map, line)) {
    within_range = k > 11 && k < 14;

    if (k == 11 + aero_carrier_number && within_range) {
      aero_carrier_data = line;
    }

    k++;
  }

  map.close();

  ajust_file_coordinates(x_string, y_string, aero_carrier_data);

  size_data = aero_carrier_data.size();

  int beginning_of_direction = beginning_of_direction_in_file(aero_carrier_data);

  for (j = beginning_of_direction; j < size_data; j++) {
    direction.push_back(aero_carrier_data[j]);
  }

  set_aero_carriers_coordinates(aero_carrier_index, direction, x_string, y_string);
}


string Player::attack() {
  string coordinate_x, coordinate_y, coordinate;
  string::size_type size;
  int x, y;

  do {
    cout << "Digite a coordenada do ataque(xx yy): ";
    cin >> coordinate_x >> coordinate_y;

    x = stoi (coordinate_x, &size);
    y = stoi (coordinate_y, &size);
  } while(x < 0 || x > 12 || y < 0 || y > 12);

  coordinate = coordinate_x + coordinate_y;

  return coordinate;
}
