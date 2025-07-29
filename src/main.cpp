#include "headers/bot.hpp"
#include "headers/game.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>

using namespace Fanorona;
int main(int argc, char *argv[]) {
  game_board initial_board = {{{0, 1, 0}, {-1, 0, -1}, {1, 1, -1}}};
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
    int mv = G.play_move_int(start, end);
    if (mv == 1) {
      printf("Invalid move !!\n");
    } else {
      B.mini_max(&G, 9, G.curr_player, &bot_move);

      std::cout << bot_move.first.first << "," << bot_move.first.second << "  ";
      std::cout << bot_move.second.first << "," << bot_move.second.second
                << std::endl;

      std::vector<move> moves = G.possible_moves();
      if (std::find(moves.begin(), moves.end(), bot_move) != moves.end()) {
        std::cout << "Valid move" << std::endl;
      } else {
        std::cout << "Invalid move by bot" << std::endl;
      }
      sleep(2);
      G.play_move(bot_move.first, bot_move.second);
    }
  }
  std::cout << "Le joueur " << G.winner << " a gagné !" << std::endl;
  return 0;
}
