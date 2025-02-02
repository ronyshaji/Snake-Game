#ifndef CONTROLLER_H
#define CONTROLLER_H

class Game;
#include "game.h"
#include "snake.h"
#include <string>

class Controller
{
public:
Controller(Game &game);
void HandleInput(bool &running, Snake &snake) const;

private:
  bool isPaused = false;
  Game &game;

  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif