cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

# Manually set SDL2_ttf paths
set(SDL2_TTF_INCLUDE_DIR "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/include/SDL2")  # Path to the SDL_ttf header file
set(SDL2_TTF_LIBRARY "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib/libSDL2_ttf-2.0.0.dylib")  # Path to the SDL_ttf library

# Include SDL2_ttf directory
include_directories(${SDL2_TTF_INCLUDE_DIR})

# Add the SDL2_ttf library to link
link_directories("/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib")  # Add the directory where the SDL_ttf library is located

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/speedcontrol.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES})
