#include "GameState.h"
#include "Object.h"

extern "C"{
    GameState* gameState = new GameState;
    EXPORT_FUNC GameState* GetState(){
        return gameState;
    }
    EXPORT_FUNC void SetState(GameState* newState){
        gameState = newState;
    }
    EXPORT_FUNC void DestroyAllObjects(){
        for(Object* o : gameState->objects){
            delete o;
        }
    }
}