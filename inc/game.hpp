#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include "map.hpp"
#include "player.hpp"

using namespace std;

typedef struct {
  string ship;
  string coordinate;
  string status;
  bool suceeded;
} AttackAnswer;

class Game {
  private:
    string winner;
    Map map;

    void finalize(Player *player_1, Player *player_2);

    void menu(Player *player);
    void print_board();

    int find_winner(Player *player);
    bool check_and_set_winner(Player *player_1, Player *player_2);

    void player_turn(Player *player, Player *opponent_player);

    bool attack_boats(AttackAnswer *answer, string coordinate, Player *player);
    bool attack_submarines(AttackAnswer *answer, string coordinate, Player *player);
    bool attack_aero_carriers(AttackAnswer *answer, string coordinate, Player *player);

    AttackAnswer attack_player(Player *player, string coordinate);
  public:
    Game() = default;
    ~Game() = default;

    string get_winner();
    void set_winner(string winner);

    void initialize(Player *player_1, Player *player_2);
};

#endif
