#include <iostream>
#include <string>

#include "player.hpp"
#include "game.hpp"

using namespace std;

int main(void) {
  cout << "Seja bem vindo ao jogo de batalha naval!!\n" << endl;

  Player *player_1 = new Player(1);
  Player *player_2 = new Player(2);

  system("clear");

  Game *game = new Game();

  game->initialize(player_1, player_2);

  return 0;
}
