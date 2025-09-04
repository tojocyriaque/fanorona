#include "headers/bot.hpp"
#include "headers/game.hpp"
#include <vector>

namespace Fanorona {

Bot::Bot() {}
Bot::~Bot() {}

float Bot::evaluate_board(Game *g) {
  float score = 0;
  if (g->is_over())
    return 10 * g->winner;

  for (int i = 0; i < 9; i++)
    score += g->get_board()[i];

  return score;
}

float Bot::mini_max(Game *g, int depth, int is_max, move *best_move) {
  if (depth == 0 || g->is_over()) {
    return evaluate_board(g);
  }

  float minmax_score = -100 * is_max;
  std::vector<move> moves = g->possible_moves(is_max);
  for (move mv : moves) {
    Game tg = *g;
    tg.play_move(mv.first, mv.second, is_max);
    float eval = mini_max(&tg, depth - 1, -is_max, nullptr);

    // change the minmax_score if it should be
    if (is_max == 1 && eval > minmax_score ||
        is_max == -1 && eval < minmax_score) {
      minmax_score = eval;
      if (best_move != nullptr)
        *best_move = mv;
    }
  }
  return minmax_score;
}

} // namespace Fanorona
