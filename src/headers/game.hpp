#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <array>
#include <list>
#include <utility>
#include <vector>

namespace Fanorona {

typedef std::array<std::array<int, 3>, 3> game_board;
typedef std::pair<int, int> square;
typedef std::pair<square, square> move;

void change_max_min(int *min, int *max, int val);

class Game {

public:
  Game();
  ~Game();

  // Game initialisation and playing process
  void init_board(game_board i_board);

  game_board get_board();
  int play_move(square start, square end);

  int play_move_int(int start, int end);

  int undo_move();
  std::vector<move> possible_moves();

  void show_board();

  // Game ending process
  bool is_over();
  bool is_tie();

  int curr_player = 1;
  int winner = 0;

private:
  game_board board;
  std::list<game_board> game_history;
};

} // namespace Fanorona
#endif // !__GAME_HPP__
