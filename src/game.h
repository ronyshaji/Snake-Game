#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "speedcontrol.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void writeNameToFile();

  ~Game() { delete control; }

private:
  // Dynamic memory allocation for a speedcontrol class object
  speedcontrol *control;
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> dist;
  bool firstpass{false};

  int score{0};
  bool isSpecial{false};

  void PlaceFood();
  void Update();
  bool specialFood(std::mt19937 &rng);
  void foodUpdate();
  void writeName();
};

#endif