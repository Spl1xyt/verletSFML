#pragma once

#include <cmath>

#include "particle.hpp"

class Solver{
  public:

    Solver() = default;
    
    void changeGravity(sf::Vector2f newGravity){
      gravity = newGravity;
    }

    void addObject(sf::Vector2f position, float radius){
      Particle newParticle = Particle(position, radius);
      newParticle.setVelocity({1.0f, 0.0f}, 1.0f);
      objects.push_back(newParticle);
    }

    void update(){
      float step_dt = dt / sub_steps;
      for (int i = 0; i < sub_steps; i++){
        updateObjects(step_dt);
      }
    }

    std::vector<Particle>& getObjects(){
      return objects;
    }

  private:
    const int window_height = 840;
    const int window_width = 840;
    float dt = 1.0f / 60;
    float sub_steps = 8;
    std::vector<Particle> objects;
    sf::Vector2f gravity = {0.0f, 1000.0f};

    void updateObjects(float dt){
      applyForces();
      applyCollision();
      applyConstraint();
      for (auto& obj : objects)
        obj.update(dt);
    }

    void applyForces(){ // apply the gravity to particles
      for (auto& obj : objects){
        obj.acceleration += gravity;
      }
    }

    // Apply the boundaries of the window to particles
    void applyConstraint(){
      for (auto& obj : objects){
        const float restitution = 0.8f;
        sf::Vector2f velocity = obj.getVelocity();
        sf::Vector2f dx = {-velocity.x, velocity.y * restitution};
        sf::Vector2f dy = {velocity.x * restitution, -velocity.y};
        sf::Vector2f npos = obj.position;
        if (obj.position.x < obj.radius) { // Bounche left
          npos.x = obj.radius;
          obj.position = npos;
          obj.setVelocity(dx, 1.0f);
        }
        if (obj.position.x > window_width - obj.radius) { // Bounce right
          npos.x = window_width - obj.radius;
          obj.position = npos;
          obj.setVelocity(dx, 1.0f);
        }
        if (obj.position.y < obj.radius) { // Bounce top
          npos.y = obj.radius;
          obj.position = npos;
          obj.setVelocity(dy, 1.0f);
        }

        if (obj.position.y > window_height - obj.radius) { // Bounce bottom
          npos.y = window_height - obj.radius;
          obj.position = npos;
          obj.setVelocity(dy, 1.0f);
        }
      }
    }

    // Apply the collision between every particles
    void applyCollision(){
      int num_objects = objects.size();
      for (int i = 0; i < num_objects; i++){
        Particle& obj_1 = objects[i];
        for (int j = 0; j < num_objects; j++){
          if (i != j){
            Particle& obj_2 = objects[j];
            sf::Vector2f v = obj_2.position - obj_1.position; 
            float dist = sqrt(v.x * v.x + v.y * v.y);
            if (dist < obj_1.radius + obj_2.radius){
              sf::Vector2f d = v / dist;
              float total_mass = obj_1.mass + obj_2.mass;
              float penetration = (obj_1.radius + obj_2.radius) - dist;

              obj_1.position -= d * (obj_2.mass / total_mass) * penetration;
              obj_2.position += d * (obj_1.mass / total_mass) * penetration;
            }
          }
        }
      }
    }
};