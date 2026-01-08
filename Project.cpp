#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
bool exitFlag;

Player* gPlayer = nullptr;  // Global pointer to Player object
GameMechs* gGameMechs = nullptr; // Global pointer to GameMechs (even if empty for now)
int main(void)
{

    Initialize();
    while(gGameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{   
    MacUILib_init();
    MacUILib_clearScreen();
    //instantiate gameMechs object
    gGameMechs = new GameMechs(30,15);
    //instantiate Player
    gPlayer = new Player(gGameMechs);
    
    objPos head = gPlayer->getPlayerPos()->getHeadElement(); // get initial head position
    gPlayer->getPlayerPos();
    gGameMechs->generateFood(gPlayer->getPlayerPos()); // generate initial food position
    gGameMechs->clearInput();
    
}

void GetInput(void)
{   
    if (MacUILib_hasChar())        
    {   //receive input
        char c = MacUILib_getChar(); 
        //modify input member of gameMechs 
        gGameMechs->setInput(c);
    }
}

void RunLogic(void)
{   
    if(gPlayer){
        //player changes direction and moves
        gPlayer->updatePlayerDir();
        gPlayer->movePlayer();
    }

    objPos head = gPlayer->getPlayerPos()->getHeadElement(); // get head position after move
    if(gPlayer){
        gPlayer->getPlayerPos();} // ensure player position is updated
    if(gGameMechs)
    {
        objPos foo = gGameMechs->getFood(); // get food position
        if(head.pos->x == foo.pos->x && head.pos->y == foo.pos->y) // check collision with food
        {
            gGameMechs->incrementScore(); 
            gGameMechs->generateFood(gPlayer->getPlayerPos());  // generate new food position
        }
    }
}

void DrawScreen(void)
{
    //instantiate snake
    objPosArrayList* snake = gPlayer->getPlayerPos();

    MacUILib_clearScreen();        
    objPos foo = gGameMechs->getFood();
    int food_x = foo.pos->x; 
    int food_y = foo.pos->y;
    char food_sym = foo.symbol;
        
    int boardsizeX = gGameMechs->getBoardSizeX();
    int boardsizeY = gGameMechs->getBoardSizeY();

    //Draw board
    for(int j = 0; j < boardsizeY; j++)
    {
        for(int i = 0; i < boardsizeX; i++)
        {
            // Draw border
            if(j == 0 || j == boardsizeY-1 || i == 0 || i == boardsizeX-1)
            {
                MacUILib_printf("#");
            }
            //Print randomly generated food
            else if(i == food_x && j == food_y)
            {
                MacUILib_printf("%c", food_sym);
            }
            //print snake (head and all segments)
            else
            {
                bool skip = false;
                for(int k = 0; k < snake->getSize(); k++) {
                    objPos segment = snake->getElement(k);
                    if(i == segment.pos->x && j == segment.pos->y) {
                        MacUILib_printf("%c", segment.symbol);
                        skip = true;
                        break;
                    }
                }
                //print whitespace 
                if(skip == false){
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");

    }
    //Print player direction
    gPlayer->printDirection();
    //get score
    int curr_score = gPlayer->getScore();
    MacUILib_printf("Score: %d\n", curr_score);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen(); 
    //Game over message
    if(gGameMechs->getLoseFlagStatus()){
        MacUILib_printf("You collided with yourself. You lost.");
    }  

    //cleanup heap variables 
    delete gPlayer;
    delete gGameMechs;

    gPlayer = nullptr;
    gGameMechs = nullptr;
    MacUILib_uninit();


}