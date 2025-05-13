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
      sf::Font font("arial.ttf");
      sf::Text text(font);

      // Display the particles
      sf::CircleShape circle(1.0f);
      circle.setOrigin({1.0f, 1.0f});
      circle.setPointCount(32);
      for (const auto& obj : objects){
        circle.setPosition(obj.position);
        circle.setScale({obj.radius, obj.radius});
        circle.setFillColor(obj.color);
        window.draw(circle);


        // Temp to introduce grid partition
        //
        //
        // text.setString(std::to_string(obj.id));
        // text.setPosition({obj.position.x - 10.0f, obj.position.y - 10.0f});
        // text.setCharacterSize(15);
        // text.setFillColor(sf::Color::White);
        // window.draw(text);
      }

      // Display amount of particles in the simulations
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

      // Temp to introduce grid partition
      //
      //
      // for (int i = 0; i < 840 / 20; i++){
      //   for (int j = 0; j < 840 / 20; j++){
      //     sf::RectangleShape rect({20.0f, 20.0f});
      //     rect.setPosition({i * 20.0f, j * 20.0f});
      //     rect.setOutlineColor(sf::Color::White);
      //     rect.setOutlineThickness(0.5f);
      //     rect.setFillColor(sf::Color::Transparent);
      //     window.draw(rect);
      //   }
      // }

    }

  private:
    sf::RenderTarget& window;
};