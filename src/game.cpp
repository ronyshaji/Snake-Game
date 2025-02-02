#include "game.h"
#include <iostream>
#include <thread>
#include <mutex>
#include "SDL.h"
#include <string>
#include <fstream>
#include <string>
#include <thread>
#include "speedcontrol.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : control(new speedcontrol()),
      snake(control, grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      dist(1, 10)
{
  PlaceFood(food);
}

Game::~Game() {   
  StopSpecialFoodThread();
  delete control; 
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, specialFood_, specialFoodActive);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// Function to write the score and player's name to .txt file
void Game::writeName()
{
  std::ofstream outputFile;
  outputFile.open("Gamestatics.txt", std::ios::app);

  auto playername = control->printPlayerName();
  if (outputFile)
  {
    outputFile << "Player Name: " << playername << ", Score: " << score << std::endl;
    outputFile.close();
    std::cout << "The player Name and score was written to the file: Gamestatics.txt" << std::endl;
  }
  else
  {
    std::cerr << "File cannot be opened !!" << std::endl;
  }
}

void Game::StartSpecialFoodThread() {
  special_food_thread = std::thread(&Game::specialFoodThread, this);
}

void Game::StopSpecialFoodThread() {
    if (special_food_thread.joinable()) {
        special_food_thread.join();  // Wait for the thread to finish
    }
}


void Game::specialFoodThread() {
  while (running)
  {
    std::this_thread::sleep_for(std::chrono::seconds(dist(engine)));

    //Pause the thread till a condition is fulfilled: Needed for the game pause feature
    std::unique_lock<std::mutex> lockk(mtx);
    pauseCv.wait(lockk, [this] { return !isPaused; });

    lockk.unlock();

    SDL_Point tempfood;
    PlaceFood(tempfood);
    {
      std::lock_guard<std::mutex> lock(mtx);
      specialFood_ = tempfood;
      specialFoodActive = true;
    }
    bool overlap = false;
    { 
      std::lock_guard<std::mutex> lock(mtx);
      overlap = ((specialFood_.x == food.x) && (specialFood_.y == food.y));
    }
    if (overlap)
    {
      PlaceFood(tempfood);
      {
        std::lock_guard<std::mutex> lock(mtx);
        specialFood_ = tempfood;
      }
      specialFoodActive = true;
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    {
      std::lock_guard<std::mutex> lock(mtx);
      specialFoodActive = false;
    }
  }
}



void Game::PlaceFood(SDL_Point &point)
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y))
    { 
      std::lock_guard<std::mutex> lock(mtx);
      point.x = x;
      point.y = y;
      return;
    }
  }
}

void Game::Update()
{

  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    foodUpdate();
  }

  if ((specialFoodActive) && (specialFood_.x == new_x) && (specialFood_.y == new_y))
  {
    std::lock_guard<std::mutex> lock(mtx);
    score +=2;
    specialFoodActive = false;
  }
}

void Game::foodUpdate()
{
  PlaceFood(food);
  // Grow snake and increase speed.
  snake.GrowBody();
  snake.speed += 0.02;
}

// Selecting special food randomly
bool Game::specialFood(std::mt19937 &rng)
{
  int randNum = dist(rng);
  return (randNum <= 2);
}

// Getter function to access the private method
void Game::writeNameToFile()
{
  writeName();
}

void Game::pauseGame(bool newIsPaused)
{
  if (newIsPaused)
  {
    isPaused = true;
    std::cout << "Game paused" << std::endl;
    std::cout << "enter 'S' to continue" << std::endl;
    std::getline(std::cin, key_);
    isPaused = false;
    pauseCv.notify_all();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }