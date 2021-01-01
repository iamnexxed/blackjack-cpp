// Install SDL, SDL_image, SDL_mixer libraries before running
// To compile and run :
// $ make
// $ ./play
// Game: BlackJack
// Author: Sudhanshu Bhamburkar

// SDL Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

// Game Dependencies
#include "GameObjects/Game.h"

// Console input/output
#include <iostream>
using namespace std;

int main()
{
    // SDL initialization
    // returns zero on success else non-zero
    // if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    // {
    //     printf("error initializing SDL: %s\n", SDL_GetError());
    // }

    Game *mainGame = new Game();
    
    // Display rules clearly
    cout << "\nDo you want to see the instructions? \n(Caution: You might be overwhelmed with words. Just sayin')\n(y/N) : ";
    char checkInstructions = '\n';
    cin >> checkInstructions;
    if (checkInstructions == 'y' || checkInstructions == 'Y')
        mainGame->ShowRules();

    mainGame->CreateGame();

    while(mainGame->isPlaying)
    {
        mainGame->PlayGame();
    } 
    
    // Clear game from memory
    delete mainGame;
    mainGame = nullptr;

    return 0;
}