#include "headers/game.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
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

int Game::play_move(square start, square end) {
  int st_value = board[start.first][start.second];
  int end_value = board[end.first][end.second];

  if (end_value == 0 && curr_player * st_value > 0 && is_over() == false) {
    // change the end square value
    board[end.first][end.second] = st_value;
    // if the stone was moved for the first time change the value to *2
    if (abs(st_value) == 1)
      board[end.first][end.second] = st_value * 2;

    // empty the start square value
    board[start.first][start.second] = 0;
    // switch player
    curr_player *= -1;

    game_history.push_back(board);
    return 0;
  }
  // invalid move
  return 1;
}

int Game::play_move_int(int start, int end) {
  int sr = start / 3, sc = start % 3;
  int er = end / 3, ec = end % 3;

  std::vector<move> moves = possible_moves();
  move mv = {{sr, sc}, {er, ec}};

  if (std::find(moves.begin(), moves.end(), mv) != moves.end()) {
    play_move({sr, sc}, {er, ec});
    return 0;
  }
  std::cout << "Not found in possible_moves" << std::endl;
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
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int sq = board[i][j];
      int sq_num = i * 3 + j;

      if (sq * curr_player > 0 && !is_over()) {
        for (auto nei : neighbours.at(sq_num)) {
          int r = nei / 3, c = nei % 3;
          if (board[r][c] == 0)
            moves.push_back({{i, j}, {r, c}});
        }
      }
    }
  }
  return moves;
}

void Fanorona::Game::show_board() {
  system("clear");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::string to_show = "+";
      int val = board[i][j];
      if (val > 0) {
        to_show = "X";
      } else if (val < 0) {
        to_show = "O";
      }

      std::cout << to_show << " ";
    }
    std::cout << std::endl;
  }
}

// Game winning logic
bool Fanorona::Game::is_over() {
  int max_sum = -100, min_sum = 100, sum_t = 0;

  // Horizontal
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      sum_t += board[i][j];

    change_max_min(&min_sum, &max_sum, sum_t);
  }

  // Vertical
  for (int j = 0; j < 3; j++) {
    sum_t = 0;
    for (int i = 0; i < 3; i++)
      sum_t += board[i][j];
    change_max_min(&min_sum, &max_sum, sum_t);
  }

  // Diagonal
  sum_t = 0;
  for (int i = 0; i < 3; i++)
    sum_t += board[i][i];
  change_max_min(&min_sum, &max_sum, sum_t);

  sum_t = 0;
  for (int i = 0; i < 3; i++)
    sum_t += board[i][2 - i];
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
