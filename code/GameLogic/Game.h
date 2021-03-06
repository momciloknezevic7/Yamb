#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <utility>
#include <vector>

#include "../NetworkCommon/common.h"
#include "Column.h"
#include "Dice.h"
#include "Player.h"
#include "Ticket.h"

// Enum for game types
enum class gameTypes {
  Online,
  Offline,
  Bot,
};

class Game {
 public:
  Game();

  void add_player(Player* player);
  void play_move();

 private:
  void switch_turn();

 private:
  std::vector<Player*> players;
  // Set communication fields between Game and Players.
  Fields field_announced;
  bool announcement;

  // How many columns have been filled.
  int number_of_filled_columns;

  // Which player is on turn.
  int player_on_turn;
};

#endif
