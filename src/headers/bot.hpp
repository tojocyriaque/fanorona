#ifndef __BOT_HPP__
#define __BOT_HPP__

#include "game.hpp"
namespace Fanorona {
class Bot {

public:
  Bot();
  ~Bot();
  float evaluate_board(Game *g);
  float mini_max(Game *g, int depth, int is_max, move *best_move);
};
} // namespace Fanorona

#endif
