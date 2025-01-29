#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <iostream>
#include <string>


class speedcontrol 
{
    public:
        speedcontrol() : playerName_("Player 1"){}

        void speedSelection();
        void getPlayerName();
        std::string printPlayerName();
        float getSpeed();
        
    private:
        std::string playerName_;
        int selection_;
        float speed_{0.1f};
        void printMenu();
        void setSelection();
    
     
};

#endif