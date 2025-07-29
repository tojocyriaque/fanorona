#include "headers/core.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

void setup() {}

void draw(sf::RenderWindow &window) {
  window.clear(sf::Color::White);

  sf::Font font("./fonts/Hack-Regular.ttf");
  sf::Text text(font, "Bonjour SFML", 10);
  text.setFillColor(sf::Color::Blue);
  text.setPosition(sf::Vector2f({(float)WIDTH / 2 - 20, (float)HEIGHT / 2}));
  window.draw(text);

  window.display();
}

void handle_events(sf::RenderWindow &window) {
  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>())
      window.close();
  }
}
