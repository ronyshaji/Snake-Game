#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "speedcontrol.h"

//forward declaration
class Controller;

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void writeNameToFile();
  void StartSpecialFoodThread();
  void StopSpecialFoodThread();
  void specialFoodThread();
  void pauseGame(bool isPaused);
  
private:
  // Dynamic memory allocation for a speedcontrol class object
  speedcontrol *control;
  Snake snake;
  SDL_Point food;
  SDL_Point specialFood_;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> dist;
  std::mutex mtx;
  bool specialFoodActive{false};
  bool running = true;
  std::thread special_food_thread; 
  bool isPaused = false;
  std::condition_variable pauseCv;
  std::string key_;

  int score{0};

  void PlaceFood(SDL_Point &point);
  void Update();
  bool specialFood(std::mt19937 &rng);
  void foodUpdate();
  void writeName();
  
};

#endif