#ifndef __CORE_H__
#define __CORE_H__

#include <SFML/Graphics.hpp>

const int WIDTH = 600;
const int HEIGHT = 400;

void setup();
void handle_events(sf::RenderWindow &window);
void draw(sf::RenderWindow &window);

#endif // !__CORE_H__
