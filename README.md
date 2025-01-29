# CPPND: Capstone Snake Game Example

Snake Game is a simple 2D C++ based game which is inspired from a Stackoverflow post and set of ansers to the post. The game is improvised with additional features and as a part of the project, some new features are added to the Snake Game, which makes it more like a real game. It uses the SDL game programming library in order to render and display the elements of the game.

The SDL library(opens in a new tab) is widely used for Game development as a tool to abstract the hardware so you don't need to worry about working with the hardware directly. SDL manages video, audio, input devices, and other components and provides you with a simple library interface.

### Snake Game Improvements and New Features

The Snake Game has been significantly improved with the addition of new features, making it more user-friendly and interactive. The key additions are:

 - **Pause/Resume Functionality:** sers can now pause and resume the game using keyboard inputs.
 - **Player Name Input:** Ability to enter the name of the player at game start.
 - **Game Difficulty Selection:** Players can choose the difficulty level (Easy or Hard) at the beginning of the game.
 - **Score and Player Name Saving:** The player's name and score are saved to a text file, allowing users to keep track of their performance.
 - **Special Food:** 

In the following sections, we will provide a detailed explanation of the newly added features. Additionally, we will cover the C++ concepts used in this project, offering a deeper understanding of the current implementation.

#### Pause/Resume Functionality

For this feature, a new function called `pauseGame()` is added in the `controller.h` file. The logic is simple and based on the earlier implementation where a function takes input from the keyboard using `SDL_Event`. The keyboard key `'p'` is mapped to a function, such that when the key `'p'` is pressed, it pauses the game using `std::cin`, which essentially waits for input from the keyboard. This implementation is straightforward and effective for pausing the game.

```cpp
void Controller::pauseGame() const
{
  std::cout << "Game paused" << std::endl;
  std::cout << "enter 'S' to continue" << std::endl;
  std::g etline(std::cin, key_);
} 
```

#### Player Name Input

This feature allows identifying the player by capturing their name. The player's name is entered via the keyboard and stored in a `std::string`, making it available for use later, such as saving it to a text file. This functionality is implemented in the newly added file `speedcontrol.cpp` within the `getPlayerName()` function, which handles capturing the input from the user.

```cpp
void speedcontrol::getPlayerName()
{
  std::cout << "Please Enter your name" << std::endl;
  std::getline(std::cin, playerName_);
}
```
#### Game Difficulty Selection

This feature enhances the Snake Game by making the gameplay more intuitive through adjustable difficulty levels. The game asks the player to select a difficulty level at the start, which determines the initial speed of the snake. There are two difficulty levels: **Easy** and **Hard**, where the snake starts at different speeds. As the snake eats more food and grows, its speed increases.

This feature is implemented in the `speedcontrol.cpp` file. It uses several member functions and conditional statements to initialize the snake's speed based on the selected difficulty level before the game begins.


```cpp
oid speedcontrol::setSelection()
{
    switch(selection_)
    {
        case 1:
            speed_ = 0.1f;
            break;
        case 2:
            speed_ = 0.5f;
            break;
    }

}
```
To make the game more user-friendly, a nice UI is provided in the terminal when starting the game. This UI prompts the player to select the desired difficulty level in a visually appealing manner. The user can choose between **Easy** and **Hard** difficulty levels, which affect the initial speed of the snake. This enhances the overall gameplay experience by giving the player control over the game's difficulty.

<center><img src="images/snake_game_difficutly.png"/></center>

#### Score and Player Name Saving

It's always beneficial to store the player's name and score for future reference, whether to track the highest score or for historical purposes. In this project, at the end of the gameplay, the player’s name and corresponding score are written to a text file named **Gamestatics.txt**. This file is created if it doesn't exist, and if it does, the latest game details are **appended** at the end. This ensures that the latest data is always available at the bottom of the text file.

This functionality is implemented in the `game.cpp` file inside a function called `writeName()`. The function takes the player’s name from `speedcontrol.cpp` and writes it along with the score to the text file.



```cpp
void Game::writeName() 
{
  std::ofstream outputFile;
  outputFile.open("Gamestatics.txt", std::ios::app);

  auto playername = control->printPlayerName();
  if(outputFile){
    outputFile << "Player Name: " << playername << ", Score: " << score << std::endl;
    outputFile.close();
    std::cout << "The player Name and score was written to the file: Gamestatics.txt" << std::endl;
  }
  else {
    std::cerr << "File cannot be opened !!" << std::endl;
  }
}
```








This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
