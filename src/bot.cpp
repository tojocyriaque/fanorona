#include "headers/bot.hpp"
#include "headers/game.hpp"
#include <vector>

namespace Fanorona {

Bot::Bot() {}
Bot::~Bot() {}

float Bot::evaluate_board(Game *g) {
  float score = 0;
  if (g->winner == 1)
    return 10;
  if (g->winner == -1)
    return -10;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      score += g->get_board()[i * 3 + j];
    }
  }
  return score;
}

float Bot::mini_max(Game *g, int depth, int is_max, move *best_move) {
  if (depth == 0 || g->is_over()) {
    return evaluate_board(g);
  }

  float minmax_score = -100 * is_max;
  std::vector<move> moves = g->possible_moves();
  for (move mv : moves) {
    Game tg = *g;
    tg.play_move(mv.first, mv.second);
    float eval = mini_max(&tg, depth - 1, -is_max, nullptr);

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
