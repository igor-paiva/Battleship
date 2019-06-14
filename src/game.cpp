#include <iostream>

#include "game.hpp"

using namespace std;

void Game::menu(Player *player) {
  int option;
  char answer;
  bool invalid;

  do {
    cout << "Opções: \n" << endl;
    cout << "1) Jogar" << endl;
    cout << "2) Instruções" << endl;
    cout << "3) Sair" << endl;

    cout << "\nDigite o número que deseja: ";

    invalid = (!(cin >> option) || option < 1 || option > 3);

    if (invalid) { system("clear"); }
  } while(invalid);

  switch (option) {
    case 1:
      return;

      break;
    case 2:
      cout << "\nVoce tem que destruir todas as embarçaões inimigas, ";
      cout << "mas voce nao sabe em que coordenadas elas estao. Descubra e destrua todas!" << endl;

      cout << "\nCada embarcação tem uma habilidade: \n" << endl;

      cout << "Canoa: tem a habilidade de ao ser acertada ser destruida. :D" << endl;

      cout << "\nSubmarino: " << player->submarines[0].get_hability() << endl;

      cout << "\nPorta-avioes: " << player->aero_carriers[0].get_hability() << endl;

      cout << "\nVamos jogar? ";
      cin >> answer;
      cout << "\n";

      if (toupper(answer) == 'S') { break; }

      exit(0);
    case 3:
      cout << "\nEstarei no aguardo...\n" << endl;

      exit(0);

      break;
  }
}

string Game::get_winner() {
  return winner;
}

void Game::set_winner(string winner) {
  this->winner = winner;
}

int Game::find_winner(Player *player) {
  int destroyed_number = 0;

  for (int i = 0; i < 6; i++) {
    if (player->boats[i].get_destroyed()) {
      destroyed_number++;
    }
  }

  for (int j = 0; j < 4; j++) {
    if (player->submarines[j].get_destroyed()) {
      destroyed_number++;
    }
  }

  for (int k = 0; k < 2; k++) {
    if (player->aero_carriers[k].get_destroyed()) {
      destroyed_number++;
    }
  }

  return destroyed_number;
}

bool Game::check_and_set_winner(Player *player_1, Player *player_2) {
  if (find_winner(player_1) == 12) {
    player_1->set_winner(true);

    set_winner(player_1->get_name());

    return true;
  }

  if (find_winner(player_2) == 12) {
    player_1->set_winner(true);

    set_winner(player_2->get_name());

    return true;
  }

  return false;
}

void Game::print_board() {
  map.print_game_board_map(1);
  map.print_game_board_map(2);
}

void Game::player_turn(Player *turn_player, Player *opponent_player) {
  char answer = ' ';
  string attack_coordinate;
  AttackAnswer opponent_player_answer;

  cout << "Turno do Player " << turn_player->get_number() << ":\n" << endl;

  print_board();

  cout << "Turno do Player " << turn_player->get_number() << ":\n" << endl;

  attack_coordinate = turn_player->attack();

  opponent_player_answer = attack_player(opponent_player, attack_coordinate);

  cout << opponent_player_answer.status << endl;

  while (toupper(answer) != 'S') {
    cout << "\nDeseja encerrar o turno? ";
    cin >> answer;
  }

  system("clear");
}

bool Game::attack_boats(AttackAnswer *answer, string coordinate, Player *player) {
  for (int i = 0; i < 6; i++) {
    if (player->boats[i].receive_shot(coordinate)) {
      answer->ship = "boat";
      answer->coordinate = coordinate;
      answer->status = "\nVocê acertou uma canoa inimiga e transformou-a em pedaços!!!";
      answer->suceeded = true;

      map.set_shooted_ship(coordinate, 'C', player->get_number());

      return true;
    }
  }

  return false;
}

bool Game::attack_submarines(AttackAnswer *answer, string coordinate, Player *player) {
  for (int i = 0; i < 4; i++) {
    if (player->submarines[i].receive_shot(coordinate) == 1) {
      answer->ship = "submarine";
      answer->coordinate = coordinate;
      answer->suceeded = true;
      answer->status = "\nVocê acertou um submarino inimigo!!!";

      if (player->submarines[i].get_destroyed()) {
        answer->status = "\nVocê destruiu um submarino inimigo!!!";
      }

      map.set_shooted_ship(coordinate, 'S', player->get_number());

      return true;
    }
    if (player->submarines[i].receive_shot(coordinate) == -1) {
      answer->suceeded = false;
      answer->status = "\nVocê já acertou esse submarino duas vezes...";

      return true;
    }
  }

  return false;
}

bool Game::attack_aero_carriers(AttackAnswer *answer, string coordinate, Player *player) {
  for (int i = 0; i < 2; i++) {
    if (player->aero_carriers[i].receive_shot(coordinate) == 1) {
      answer->ship = "aero carrier";
      answer->coordinate = coordinate;
      answer->status = "\nVocê acertou um porta-aviões inimigo!!!";
      answer->suceeded = true;

      if (player->aero_carriers[i].get_destroyed()) {
        answer->status = "\nVocê destruiu um porta-aviões inimigo!!!";
      }

      map.set_shooted_ship(coordinate, 'P', player->get_number());

      return true;
    }
    if (player->aero_carriers[i].receive_shot(coordinate) == -1) {
      answer->status = "\nVocê acertou um porta-aviões inimigo, mas o míssil foi desviado...";
      answer->suceeded = false;

      map.set_shooted_ship(coordinate, 'P', player->get_number());

      return true;
    }
    if (player->aero_carriers[i].receive_shot(coordinate) == -2) {
      answer->status = "\nVocê acertou já acertou esse porta-aviões...";
      answer->suceeded = false;

      return true;
    }
  }

  return false;
}

AttackAnswer Game::attack_player(Player *player, string coordinate) {
  AttackAnswer answer;

  int player_number = player->get_number();

  if (attack_boats(&answer, coordinate, player)) { return answer; }

  if (attack_submarines(&answer, coordinate, player)) { return answer; }

  if (attack_aero_carriers(&answer, coordinate, player)) { return answer; }

  answer.suceeded = false;
  answer.status = "\nVocê acertou água...";

  map.set_shooted_ship(coordinate, '-', player_number);

  return answer;
}

void Game::finalize(Player *player_1, Player *player_2) {
  string winner = get_winner();

  system("clear");

  cout << "O jogador " << winner << " foi o vencedor!!!\n" << endl;

  cout << "O campeão " << winner << " destruiu as 12 embarcações inimigas!!\n" << endl;

  if (player_1->get_winner()) {
    cout << "O jogador " << player_2->get_name() << " destruiu ";

    cout << find_winner(player_2) << " embarcações inimigas." << endl;
  }
  if (player_2->get_winner()) {
    cout << "O jogador " << player_1->get_name() << " destruiu ";

    cout << find_winner(player_1) << " embarcações inimigas." << endl;
  }

  cout << "\nMuito obrigado por jogar!!" << endl;
}

void Game::initialize(Player *player_1, Player *player_2) {
  Boat *boats_1 = new Boat[6];
  Boat *boats_2 = new Boat[6];
  Submarine *submarines_1 = new Submarine[4];
  Submarine *submarines_2 = new Submarine[4];
  AeroCarrier *aero_carriers_1 = new AeroCarrier[2];
  AeroCarrier *aero_carriers_2 = new AeroCarrier[2];

  player_1->set_ships(&boats_1[0], &submarines_1[0], &aero_carriers_1[0]);
  player_2->set_ships(&boats_2[0], &submarines_2[0], &aero_carriers_2[0]);

  menu(player_1);

  while (true) {
    player_turn(player_1, player_2);

    player_turn(player_2, player_1);

    if (check_and_set_winner(player_1, player_2)) { break; }
  }

  finalize(player_1, player_2);
}
