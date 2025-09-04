#include "headers/bot.hpp"
#include "headers/game.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#define DIM 9

bool fill(Fanorona::game_board &positions, std::vector<int> pieces, int c_index,
          int &count) {

  std::map<int, std::vector<int>> neighbours = {
      {0, {1, 3, 4}}, {1, {0, 2, 4}},       {2, {1, 4, 5}},
      {3, {0, 4}},    {4, {0, 1, 2, 3, 5}}, {5, {2, 4, 8}},
      {6, {3, 4, 7}}, {7, {4, 6, 8}},       {8, {4, 5, 7}}};

  if (c_index >= DIM) {
    Fanorona::Game G;
    Fanorona::Bot B;
    Fanorona::move bot_move;

    int total = 0;
    for (int p : positions) {
      if (p > 0) {
        total += 1;
      } else if (p < 0) {
        total -= 1;
      }
    }

    int c2 = std::count(positions.begin(), positions.end(), 1);
    int c_2 = std::count(positions.begin(), positions.end(), -1);

    int diff = c2 - c_2;
    int turn = (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
    if (c2 != 3 && c_2 != 3)
      turn = 0;

    int c0 = std::count(positions.begin(), positions.end(), 0);
    if (c0 != 3 || total != 0 || (int)std::fabs(diff) > 1)
      return false;

    bool valid = false;
    bool can_move = false;
    for (int i = 0; i < positions.size(); i++) {
      if (std::fabs(positions[i]) == 2) {
        if (std::any_of(
                neighbours[i].begin(), neighbours[i].end(),
                [positions](int x) -> bool { return positions[x] == 0; }))
          valid = true;
      }
      if (c2 == 3 && c_2 < 3 && turn == 1 && positions[i] == 1) {
        bool a = std::any_of(
            neighbours[i].begin(), neighbours[i].end(),
            [positions](int x) -> bool { return positions[x] == 0; });
        if (a)
          can_move = true;
      } else if (c_2 == 3 && c2 < 3 && turn == -1 && positions[i] == -1) {
        bool a = std::any_of(
            neighbours[i].begin(), neighbours[i].end(),
            [positions](int x) -> bool { return positions[x] == 0; });
        if (a)
          can_move = true;
      }
    }

    if (!valid)
      return false;
    if ((turn != 0 && !can_move))
      return false;

    // Affichage

    G.set_board(positions);
    B.mini_max(&G, 9, 1, &bot_move);

    if (bot_move.first != bot_move.second) {
      for (int i = 0; i < DIM; i++) {
        std::cout << positions[i] << " ";
      }
      std::cout << "1 " << bot_move.first << " " << bot_move.second
                << std::endl;
    }

    B.mini_max(&G, 9, -1, &bot_move);

    if (bot_move.first != bot_move.second) {
      for (int i = 0; i < DIM; i++) {
        std::cout << positions[i] << " ";
      }
      std::cout << "2 " << bot_move.first << " " << bot_move.second
                << std::endl;
    }

    count++;
    return true;
  }

  for (int i = 0; i < (int)pieces.size(); i++) {
    positions[c_index] = pieces[i];
    fill(positions, pieces, c_index + 1, count);
  }

  return true;
}

int main() {
  int count = 0;
  std::vector<int> pieces{0, -1, 1, -2, 2};
  // Index de piece à parcourir
  int c_index = 0;

  std::array<int, 9> positions;

  // Fonction récursive pour remplir petit à petit les positions
  fill(positions, pieces, c_index, count);
  std::cout << count;

  return 0;
}
