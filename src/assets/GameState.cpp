#include "GameHeader.h"

extern "C"{
    extern GameState* gameState;
    EXPORT_FUNC GameState* GetState(){
        // std::cout << "gameState gotten." << std::endl;
        return gameState;
    }
    EXPORT_FUNC void SetState(GameState* newState){
        gameState = newState;
    }
}