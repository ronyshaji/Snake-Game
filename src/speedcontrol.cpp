#include <iostream>
#include <fstream>
#include <limits>
#include "speedcontrol.h"

void speedcontrol::speedSelection()
{
    // std::cout << "Welcome to Snake Game !! \nSelect the difficulty level\n 1. Easy\n 2. Hard" << std::endl;
    printMenu();
    std::cin >> selection_;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setSelection();
}

void speedcontrol::printMenu()
{
    // Clear the terminal screen (works on most systems)
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen

    // Create a border and format the output
    std::cout << "**************************************" << std::endl;
    std::cout << "*                                    *" << std::endl;
    std::cout << "*       Welcome to Snake Game !!     *" << std::endl;
    std::cout << "*                                    *" << std::endl;
    std::cout << "**************************************" << std::endl;
    std::cout << std::endl;

    // Using ASCII art symbols for the difficulty menu
    std::cout << "Select the difficulty level:\n"
              << std::endl;

    // Highlighting the options with some symbols
    std::cout << "  [1]  Easy     -  (◕‿◕)  Let's start slow!" << std::endl;
    std::cout << "  [2]  Hard     -  (╯°□°）╯  Brace yourself!" << std::endl;

    std::cout << std::endl;
    std::cout << "**************************************" << std::endl;
    std::cout << "*                                    *" << std::endl;
    std::cout << "*      Press 1 for Easy or 2 for     *" << std::endl;
    std::cout << "*        Hard. Then hit Enter!       *" << std::endl;
    std::cout << "*                                    *" << std::endl;
    std::cout << "**************************************" << std::endl;
    std::cout << std::endl;
}

void speedcontrol::setSelection()
{
    switch (selection_)
    {
    case 1:
        speed_ = 0.1f;
        break;
    case 2:
        speed_ = 0.5f;
        break;
    }
}

// Read the playerName from the keyboard
void speedcontrol::getPlayerName()
{
    std::cout << "Please Enter your name" << std::endl;
    std::getline(std::cin, playerName_);
}

std::string speedcontrol::printPlayerName()
{
    return playerName_;
}

float speedcontrol::getSpeed()
{
    return speed_;
}