#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include <thread>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const{
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::pauseGame() const
{
  std::cout << "Game paused" << std::endl;
  std::cout << "enter 'S' to continue" << std::endl;
  std::getline(std::cin, key_);
  
}

/*std::chrono::milliseconds Controller::awakeTime() const
{
  end_ = std::chrono::high_resolution_clock::now();
  duration_ = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_);
  return duration_;
}

void Controller::continueGame() const
{
  std::this_thread::sleep_for(awakeTime());
  //std::cout << awakeTime() << std::endl;;
} */


void Controller::HandleInput(bool &running, Snake &snake) const{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_p:
          std::cout << "Key P pressed" << std::endl;
          pauseGame();
          break;
      }
    }
  }
}