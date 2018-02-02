#include "pitch.h"

#include <iostream>

namespace SenselessSoccer {

PitchTiled::PitchTiled(const std::string &filename, GameLib::Camera &c) : GameLib::Tileset(filename, c) {
}

void PitchTiled::Render(GameLib::Window &window) {
  GameLib::Tileset::Render(window);

  double startx = 100;
  double starty = 100;
  double endx = 100;
  double endy = 400;

  sf::Vertex vertices[4] = {sf::Vertex(sf::Vector2f(static_cast<float>(startx), static_cast<float>(starty)), sf::Color(255, 255, 255, 190)),
                            sf::Vertex(sf::Vector2f(static_cast<float>(endx), static_cast<float>(endy)), sf::Color(255, 255, 255, 190)),

                            sf::Vertex(sf::Vector2f(static_cast<float>(endx), static_cast<float>(endy)), sf::Color(255, 255, 255, 190)),
                            sf::Vertex(sf::Vector2f(static_cast<float>(endx) + 300, static_cast<float>(endy)), sf::Color(255, 255, 255, 190))};

  // 	sf::VertexArray lines (sf::Lines, 2);
  // 	lines[0].color = sf::Color (255, 255, 255, 190);
  // 	lines[1].color = sf::Color (255, 255, 255, 190);

  for (int i = 0; i < 8; ++i) {
    // 		lines[0].position = sf::Vector2f (startx, starty);
    // 		lines[1].position = sf::Vector2f (endx, endy);
    window.window.draw(vertices, 4, sf::Lines);

    startx += 0.2;
    endx += 0.2;
  }
}

} // SenselessSoccer
