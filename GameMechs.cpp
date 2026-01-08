#include "GameMechs.h"

GameMechs::GameMechs() // Initialize the game mechanics-related parameters
{
    boardSizeX = 30;
    boardSizeY = 15;
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    srand(time(NULL));
    food.setObjPos(1, 1, 'o');
    
}

GameMechs::GameMechs(int boardX, int boardY) // Initialize the game mechanics-related parameters
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    
    srand(time(NULL));
    food.setObjPos(1, 1, 'o');
}

bool GameMechs::samePos(const objPos &b, const objPos &c) const // helper function - Compares two objPos objects and returns true if their positions are the same.
{
    return (b.pos->x == c.pos->x) && (b.pos->y == c.pos->y);
}

bool GameMechs::getExitFlagStatus() const // Getter and setter of the exit flag.
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const // Getter and setter of the lose flag.
{
    return loseFlag;
}
    

char GameMechs::getInput() const // Getter and setter of the most recently collected ASCII character input from MacUILib_getChar()
{
    return input;
}

int GameMechs::getScore() const //  getter method for the game score
{
    return score;
}

void GameMechs::incrementScore() // Specialized setter for the score field. Assumption is that the score can 
                                 // only be incremented 1 at a time for every food item collected.
{
    ++score;
}

int GameMechs::getBoardSizeX() const // getter methods for board dimensions x
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const // getter methods for board dimensions y
{
    return boardSizeY;
}


void GameMechs::setExitTrue() // setter method to set the exit flag to true
{
    exitFlag = true;
}

void GameMechs::setLoseFlag() // setter method to set the lose flag to true
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input) // setter method to set the most recently collected ASCII character input from MacUILib_getChar()
{
    input = this_input;
}

void GameMechs::clearInput() // method to clear the input character after it has been processed
{
    input = 0;
}

// More methods should be added here

objPos GameMechs::getFood() const // getter method for food position
{
    return food;
}
void GameMechs::generateFood(objPosArrayList* snakePos) // method to generate food at a random position not occupied by the snake
{
    int x_min = 1; // account for border
    int y_min = 1;
    int x_max = boardSizeX - 2; // account for border
    int y_max = boardSizeY - 2; 
    int x, y;
    bool validPos = true;
    do
    {
        validPos = true;
        x = (rand() % (x_max - x_min + 1)) + x_min; // generate random x within bounds
        y = (rand() % (y_max - y_min + 1)) + y_min; // generate random y within bounds
        int b = snakePos->getSize(); // get size of snake position list
        for(int i = 0; i < b; i++){
            objPos segment = snakePos->getElement(i); // get each segment of the snake
            if(segment.pos->x == x && segment.pos->y == y) // check if the generated position matches any segment position
            { 
                validPos = false;
                break;
            }
        }

    } while (!validPos);
    food.setObjPos(x, y, 'o'); // set food position to the valid generated position
}
