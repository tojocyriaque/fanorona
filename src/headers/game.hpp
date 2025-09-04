#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <array>
#include <list>
#include <utility>
#include <vector>

namespace Fanorona {

typedef std::array<int, 9> game_board;
typedef std::pair<int, int> move;

void change_max_min(int *min, int *max, int val);

class Game {

public:
  Game();
  ~Game();

  void set_board(game_board i_board);

  game_board get_board();
  int play_move(int start, int end, int player);

  int undo_move();
  std::vector<move> possible_moves(int player);

  void show_board();

  // Game ending process
  bool is_over();

  int curr_player = 1;
  int winner = 0;

private:
  game_board board;
  std::list<game_board> game_history;
};

} // namespace Fanorona
#endif // !__GAME_HPP__
