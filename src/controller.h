#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <string>

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

 private:
  mutable std::string key_;

  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  void pauseGame() const;
  
};

#endif