#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>


struct Particle {
  sf::Vector2f position;
  sf::Vector2f prev_position;
  sf::Vector2f acceleration;
  float mass = 1;
  float radius = 10.0f;
  sf::Color color = randomColor();

  Particle() = default;
  Particle(sf::Vector2f position_, float radius_)
    : position(position_)
    , prev_position(position_)
    , acceleration({0.0f, 0.0f})
    , radius(radius_)
  {}

  
  void update(float dt){
    sf::Vector2f velocity = position - prev_position;
    prev_position = position;
    position = position + velocity + acceleration * (dt * dt);
    acceleration = {};
  }
    
  void setVelocity(sf::Vector2f v, float dt) {
    prev_position = position - (v * dt);
  }

  sf::Vector2f getVelocity() {
    return position - prev_position;
  }

  sf::Color randomColor(){
    sf::Color color;
    color.r = rand() % 256;
    color.b = rand() % 256;
    color.g = rand() % 256;
    return color;
  }
};