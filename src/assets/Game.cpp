#include "Game.h"
#include "Object.h"
#include "TestObj.h"

extern "C"{
    static GameState* state = (GameState*)malloc(1024);
    EXPORT_FUNC void Display(){
        //run all object display functions
        for(Object* o : state->objects){
            o->Display();
        }
    }
    EXPORT_FUNC void Start(){
        //do initial stuff
        TestObj t;
        t.Instantiate();
        std::cout << "Running (" << state->objects.size() << ") Start functions." << std::endl;

        //propogate object start functions
        for(Object* o : state->objects){
            o->Start();
        }
    }
    EXPORT_FUNC GameState* GameUpdate(){
        // std::cout << "Updating Game." << std::endl;
        for(Object* o : state->objects){
            o->Update();
        }
        // std::cout << "Finished updating (" << state->objects.size() << ") objects." << std::endl;
        return state;
    }
    EXPORT_FUNC GameState* GetState(){
        return state;
    }
    EXPORT_FUNC void SetState(GameState* newState){
        state = newState;
    }
    EXPORT_FUNC void DestroyAllObjects(){
        for(size_t i = 0; i < state->objects.size(); ++i){
            delete state->objects[i];
        }
    }
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey){
        if(GetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            std::cout << "A Pressed, testing object: " << state->objects[0]->PosXYZ() << std::endl;
            // std::cout << "comment this out to demonstrate hotswap" << std::endl;
        }
    }
}
