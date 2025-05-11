#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "particle.hpp"
#include "physicsEngine.hpp"
#include "renderer.hpp"

int main()
{
  const int window_height = 840;
  const int window_width = 840;

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 1;
  sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "Particles", sf::Style::Default, sf::State::Windowed, settings);
  window.setFramerateLimit(60);

  Renderer renderer(window);
  Solver solver;

  std::vector<Particle> particle = solver.getObjects();

  sf::Clock timer, timerfps;
  sf::Time timeBeforeNewParticle = sf::milliseconds(100); // Used to know the time before spawning a new particle in milliseconds; 
  
  
  while(window.isOpen())
  {
    float currentTime = timerfps.restart().asSeconds();
    int fps = 1 / currentTime;

    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // change gravity
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){ // going up
      solver.changeGravity({0.0f, -1000.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){ // going down
      solver.changeGravity({0.0f, 1000.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ // going right
      solver.changeGravity({1000.0f, 0.0f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ // going left
      solver.changeGravity({-1000.0f, 0.0f});
    }
    
    // Generate new particles
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        timer.start();
        if (timeBeforeNewParticle < timer.getElapsedTime()){
          solver.addObject({110.0f, 60.0f}, 10.0f);
          solver.addObject({10.0f, 160.0f}, 10.0f);
          solver.addObject({60.0f, 110.0f}, 10.0f);
          solver.addObject({160.0f, 10.0f}, 10.0f);
          timer.restart();
        }
    }

    solver.update();
    window.clear(sf::Color::Black);
    renderer.render(solver, fps);
    window.display();
  }
}