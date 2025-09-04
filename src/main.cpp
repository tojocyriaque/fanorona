// #include "headers/bot.hpp"
// #include "headers/game.hpp"
// #include <cstdio>
// #include <iostream>
// #include <ostream>
// #include <unistd.h>

// using namespace Fanorona;
// int main(int argc, char *argv[]) {
//   game_board initial_board = {2, 2, 2, -2, -2, -2, 0, 0, 0};
//   int start, end;
//   Game G;
//   Bot B;
//   move bot_move;
//   int curr_player = -1;

//   G.set_board(initial_board);
//   char *players = "OX";
//   while (!G.is_over()) {
//     G.show_board();
//     std::cout << "------------------------" << std::endl;
//     std::cout << players[curr_player + 1] << "'s turn > Enter your move: ";
//     scanf("%d %d", &start, &end);
//     int mv = G.play_move(start, end, curr_player);
//     if (mv == 1) {
//       printf("Invalid move !!\n");
//     } else {
//       curr_player = curr_player * -1;
//       B.mini_max(&G, 9, G.curr_player, &bot_move);

//       // std::vector<move> moves = G.possible_moves();
//       G.play_move(bot_move.first, bot_move.second, curr_player);
//     }
//   }
//   std::cout << "Le joueur " << G.winner << " a gagné !" << std::endl;
//   return 0;
// }