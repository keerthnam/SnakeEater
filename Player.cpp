#include "Player.h"
#include "MacUILib.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    //instantiate objPosArrayList
    playerPosList = new objPosArrayList();

    int x_start = 1;
    int y_start = 1;
    if(mainGameMechsRef)
    {
        x_start = mainGameMechsRef->getBoardSizeX() / 2;
        y_start = mainGameMechsRef->getBoardSizeY() / 2;
        if(x_start <= 0)
        {
            x_start = 1;
        }
        if(y_start <= 0)
        {
            y_start = 1;
        }
    }

    
    objPos startPos(9, 5, '*'); // starting position of the player
    playerPosList->insertHead(startPos); // insert starting position into the position list
}

Player::~Player()
{
    // delete heap members
    if(playerPosList){
        delete playerPosList;
        playerPosList = nullptr;
    }
}

bool Player::isOppositeDir(Dir a, Dir b) const
{
    if((a == UP && b == DOWN) || (a == DOWN && b == UP) ||
       (a == LEFT && b == RIGHT) || (a == RIGHT && b == LEFT)) 
    {
        return true; // checks if directions are opposite
    }
    return false;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the objPosArrayList
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
    // PPA3 input processing logic     
    char input = mainGameMechsRef->getInput();
    
    if(input != 0)  // if not null character
    {
        switch(input) //current direction
        {   //Quit key      
            case ' ':
                mainGameMechsRef->setExitTrue();
                break;
            //WSAD directions- W (up), S (down), D (right), A (left)
            case 'W': case 'w':
                if(myDir != DOWN){
                    myDir = UP;
                }      
                MacUILib_printf("UP");   
                break;
            case 'S': case 's':
                if(myDir != UP){
                    myDir = DOWN;
                }
                
                break;
            case 'A': case 'a':
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case'D': case 'd':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
                break;
        }
        mainGameMechsRef->clearInput();
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
      // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program
    objPos currentHead = playerPosList->getHeadElement();
    objPos newHead = currentHead; 

    int maxX = mainGameMechsRef->getBoardSizeX();
    int maxY = mainGameMechsRef->getBoardSizeY();

    switch(myDir){
        case LEFT:
            newHead.pos->x--;
            break;
        case RIGHT:
            newHead.pos->x++;
            break;
        case UP:
            newHead.pos->y--;
            break;
        case DOWN:
            newHead.pos->y++;
            break;
        default: 
            break;
    }

    if(newHead.pos->x == maxX-1){ //if player hits the right wall
        newHead.pos->x = 1;
    }else if(newHead.pos->x == 0){ //if player hits the left wall
        newHead.pos->x = maxX-2;
    }
    
    if(newHead.pos->y >= maxY-1){ //if player hits bottom wall
        newHead.pos->y = 1;
    }else if(newHead.pos->y == 0){ //if player hits top wall
        newHead.pos->y = maxY-2;
    }

    //check collision with snake body (itself)
    int num = playerPosList->getSize();
    for(int i = 1; i < num; i++){
        objPos segment = playerPosList->getElement(i);
        if(segment.pos->x == newHead.pos->x && segment.pos->y == newHead.pos->y){
            if(mainGameMechsRef){
                mainGameMechsRef->setLoseFlag();
                mainGameMechsRef->setExitTrue();
            }
            return;
        }

    }
    // check collision with food
    bool ate = false;
    if(mainGameMechsRef){
        objPos food = mainGameMechsRef->getFood();
        if(food.pos->x == newHead.pos->x && food.pos->y == newHead.pos->y){
            ate = true;
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->generateFood(playerPosList);
        }
    }


    // Insert new head
    playerPosList->insertHead(newHead);

    //Remove tail segment
    if(!ate){
    playerPosList->removeTail();
    }
}

int Player::getScore() const
{
    int len = playerPosList->getSize();
    return (len > 1) ? (len - 1) : 0; 
}


//displays player direction
void Player::printDirection() const
{
    MacUILib_printf("\nPlayer Direction: ");
    switch(myDir){
        case UP:
            MacUILib_printf("UP");
            break;
        case DOWN:
            MacUILib_printf("DOWN");
            break;
        case LEFT: 
            MacUILib_printf("LEFT");
            break;
        case RIGHT:
            MacUILib_printf("RIGHT");
            break;
        case STOP:
            MacUILib_printf("STOPPED");
            break;
    }
    MacUILib_printf("\n");
}