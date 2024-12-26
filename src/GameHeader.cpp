#include "GameHeader.h"
#include "Game.h"
#include "assets/GameObject.h"

extern "C"{
    GameState* gameState = nullptr;
    HMODULE* objectsLib = nullptr;
    EXPORT_FUNC void Init(void** params){
        //pull game state from main
        gameState = (GameState*)params[0];
        objectsLib = (HMODULE*)params[1];
        //generate objects the game can interface with
        if(gameState->objects.size() > 0){std::cout << "loading from prev state.\n";}
        for(Object* o : gameState->objects){
            GameObject temp = GameObject(o);
        }
        std::cout << "Initialized Game." << std::endl;
    }
    EXPORT_FUNC void GameStart(){
        //do initial stuff
        Start();
        //propogate object start functions
        std::cout << "Running (" << gameState->objects.size() << ") Start functions." << std::endl;
        for(Object* o : gameState->objects){
            o->Start();
        }
        
    }
    EXPORT_FUNC GameState* GameUpdate(){
        Update();
        for(Object* o : gameState->objects){
            o->Update();
        }
        return gameState;
    }
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey){
        Controls(window, GetKey);
    }
    EXPORT_FUNC GameState* GetGameState(){
        return gameState;
    }
    EXPORT_FUNC void SetGameState(GameState* state){
        gameState = state;
    }
    EXPORT_FUNC HMODULE* GetObjectLib(){
        return objectsLib;
    }
}
