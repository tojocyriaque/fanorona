#include "headers/bot.hpp"
#include "headers/game.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>

using namespace Fanorona;
int main(int argc, char *argv[]) {
  game_board initial_board = {1, -1, 0, 0, -1, -1, 1, 0, 1};
  int start, end;
  Game G;
  Bot B;
  move bot_move;

  G.init_board(initial_board);

  while (!G.is_over()) {
    G.show_board();
    std::cout << "------------------------" << std::endl;
    std::cout << "> Enter your move: ";
    scanf("%d %d", &start, &end);
    int mv = G.play_move(start, end);
    if (mv == 1) {
      printf("Invalid move !!\n");
    } else {
      B.mini_max(&G, 9, G.curr_player, &bot_move);

      std::vector<move> moves = G.possible_moves();
      G.play_move(bot_move.first, bot_move.second);
    }
  }
  std::cout << "Le joueur " << G.winner << " a gagné !" << std::endl;
  return 0;
}
