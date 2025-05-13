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
      Particle newParticle = Particle(position, radius, id);
      newParticle.setVelocity({1.0f, 0.0f}, 1.0f);
      id++;
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
    const static int window_height   = 1500;
    const static int window_width    = 1500;
    const static int grid_x          = window_width / 10.0f;
    const static int grid_y          = window_height / 10.0f;

    int id                           = 0;
    float dt                         = 1.0f / 60;
    float sub_steps                  = 8;

    sf::Vector2f gravity             = {0.0f, 1000.0f};

    std::vector<Particle> objects;

    std::vector<int> grid[grid_x][grid_y];


    void updateObjects(float dt){
      applyForces();
      updateGrid();
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
      for (int i = 0; i < grid_x; i++){
        for (int j = 0; j < grid_y; j++){
          std::vector<Particle> neighbors = getNeighbors(i, j); 
          int num_objects = neighbors.size();
          for (int k = 0; k < grid[i][j].size(); k++){
            Particle& obj_1 = objects[grid[i][j][k]];
            for (int l = 0; l < num_objects; l++){
              Particle& obj_2 = objects[neighbors[l].id];
              if (obj_1.id != obj_2.id){
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
      }
    }

    void updateGrid(){
      for (int i = 0; i < grid_x; i++){
        for (int j = 0; j < grid_y; j++){
          grid[i][j].clear();
        }
      }

      for (auto& obj : objects){
        const int i = static_cast<int>(obj.position.x / 20.0f);
        const int j = static_cast<int>(obj.position.y / 20.0f);
        if (i < 0 || i >= grid_x || j < 0 || j >= grid_y) continue;
        grid[i][j].push_back(obj.id);
      }
    }

    std::vector<Particle> getNeighbors(int x, int y){
      std::vector<Particle> newObjects;
      const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0, 0};
      const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1, 0};
      for (int dir = 0; dir < 9; dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && nx < grid_x && ny >= 0 && ny < grid_y){
          for (int id : grid[nx][ny])
            newObjects.push_back(objects[id]);
        }
      }
      return newObjects;
    }
};