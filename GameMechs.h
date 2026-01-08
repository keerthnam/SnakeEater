#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos foodPos; // position of the food item
        objPos food; // food object

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        objPos getFood() const; // getter method for food position
        void generateFood(objPosArrayList* snakePos); // method to generate food at a random position not occupied by the snake
        bool samePos(const objPos &b, const objPos &c) const; // method to check if two objPos positions are the same
};

#endif