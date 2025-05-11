#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>

#include "physicsEngine.hpp"

class Renderer {
  public:
    Renderer(sf::RenderTarget& window_)
      : window(window_)
    {}

    void render(Solver& solver, int fps){
      const auto& objects = solver.getObjects();
      std::string num_objects = std::to_string(objects.size());

      // Display the particles
      sf::CircleShape circle(1.0f);
      circle.setOrigin({1.0f, 1.0f});
      circle.setPointCount(32);
      for (const auto& obj : objects){
        circle.setPosition(obj.position);
        circle.setScale({obj.radius, obj.radius});
        circle.setFillColor(obj.color);
        window.draw(circle);
      }

      // Display amount of particles in the simulations
      sf::Font font("arial.ttf");
      sf::Text text(font);
      text.setString("Objects : " + num_objects);
      text.setCharacterSize(20);
      text.setPosition({20.0f, 20.0f});
      text.setFillColor(sf::Color::White);
      window.draw(text);
      
      // Display FPS
      text.setString("FPS : " + std::to_string(fps));
      text.setCharacterSize(20);
      text.setPosition({20.0f, 40.0f});
      text.setFillColor(sf::Color::White);
      window.draw(text);

    }

  private:
    sf::RenderTarget& window;
};