#include "headers/game.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

Fanorona::Game::Game() {}
Fanorona::Game::~Game() {}

namespace Fanorona {

std::map<int, std::vector<int>> neighbours = {
    {0, {1, 3, 4}}, {1, {0, 2, 4}},       {2, {1, 4, 5}},
    {3, {0, 4}},    {4, {0, 1, 2, 3, 5}}, {5, {2, 4, 8}},
    {6, {3, 4, 7}}, {7, {4, 6, 8}},       {8, {4, 5, 7}}};

void change_max_min(int *min, int *max, int val) {
  if (val > *max)
    *max = val;
  else if (val < *min)
    *min = val;
}

void Game::init_board(game_board i_board) {
  board = i_board;
  game_history.push_back(i_board);
}

game_board Game::get_board() { return board; }

int Game::play_move(int start, int end) {
  int sr = start / 3, sc = start % 3;
  int er = end / 3, ec = end % 3;

  std::vector<move> moves = possible_moves();
  move mv = {start, end};

  // Play the move if it is valid
  if (std::find(moves.begin(), moves.end(), mv) != moves.end()) {
    int st_value = board[start];
    int end_value = board[end];

    if (end_value == 0 && curr_player * st_value > 0 && is_over() == false) {
      // change the end square value
      board[end] = st_value;
      // if the piece was moved for the first time, mutliply the value by 2
      if (abs(st_value) == 1)
        board[end] = st_value * 2;

      // empty the start square value
      board[start] = 0;
      // switch player
      curr_player *= -1;

      game_history.push_back(board);
      return 0;
    }
  }
  return 1;
}

int Game::undo_move() {
  if (game_history.size() <= 1)
    return 1;

  winner = 0;
  game_history.pop_back();

  board = game_history.back();
  curr_player *= -1;

  return 0;
}

std::vector<move> Game::possible_moves() {
  std::vector<move> moves;
  for (int sq = 0; sq < 9; sq++) {
    int piece = board.at(sq);
    if (piece * curr_player > 0) {
      for (int nei : neighbours.at(sq)) {
        if (board[nei] == 0)
          moves.push_back({sq, nei});
      }
    }
  }
  return moves;
}

void Fanorona::Game::show_board() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int piece = board[i * 3 + j];
      if (piece > 0)
        std::cout << "X";
      else if (piece < 0)
        std::cout << "0";
      else
        std::cout << "+";
      std::cout << "";
    }
    std::cout << std::endl;
  }
}

// Game winning logic
bool Fanorona::Game::is_over() {
  int max_sum = -100, min_sum = 100, sum_t = 0, index = 0;

  // Horizontal
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      index = 3 * i + j;
      sum_t += board[index];
    }

    change_max_min(&min_sum, &max_sum, sum_t);
  }

  // Vertical
  for (int j = 0; j < 3; j++) {
    sum_t = 0;
    for (int i = 0; i < 3; i++) {
      index = 3 * i + j;
      sum_t += board[index];
      change_max_min(&min_sum, &max_sum, sum_t);
    }
  }

  // Diagonal
  sum_t = 0;
  for (int i = 0; i < 3; i++) {
    index = 3 * i + i;
    sum_t += board[index];
  }
  change_max_min(&min_sum, &max_sum, sum_t);

  sum_t = 0;
  for (int i = 0; i < 3; i++) {
    index = 2 * i + 2;
    sum_t += board[index];
  }
  change_max_min(&min_sum, &max_sum, sum_t);

  if (max_sum == 6) {
    winner = 1;
    return true;
  } else if (min_sum == -6) {
    winner = -1;
    return true;
  }

  return false;
}
} // namespace Fanorona
