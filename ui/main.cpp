#include "headers/core.hpp"

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Fanorona");
  setup();
  while (window.isOpen()) {
    handle_events(window);
    draw(window);
  }
  return 0;
}
