#include "GameHeader.h"
#include "Game.h"
#include "Object.h"
#include "TestObj.h"

extern "C"{
    GameState* gameState = new GameState;

    EXPORT_FUNC void Init(void** params){
        //init game
        *gameState = *(GameState*)params[0];
        void* map_address = params[1];
        gameState->obj_vis_map = (std::map<unsigned int, void*>*)map_address;
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
        // std::cout << "Updating Game." << std::endl;
        Update();
        for(Object* o : gameState->objects){
            o->Update();
        }
        // std::cout << "Finished updating (" << gameState->objects.size() << ") objects." << std::endl;
        return gameState;
    }

    EXPORT_FUNC void DestroyAllObjects(){
        for(Object* o : gameState->objects){
            delete o;
        }
    }
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey){
        Controls(window, GetKey);
    }
    EXPORT_FUNC Object* GetNew(Object* obj){
        return obj->CreateNew();
    }
    EXPORT_FUNC void CopyObject(Object* to, Object* from){
        to->id = from->id;
        to->renderData = from->renderData;
        to->vertShaderPath = from->vertShaderPath;
        to->fragShaderPath = from->fragShaderPath;
    }
}
