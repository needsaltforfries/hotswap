#include "Game.h"
#include "assets/objects/GameState.h"
#include "assets/GameObject.h"

//do stuff before first update
EXPORT_FUNC void Start(){
    std::cout << "Game Start!\n";
    GameObject t;
    std::cout << "t obj temp\n";
    GameObject::Instantiate(t);
    std::cout << "t instantiated\n";
}

//this function is called every update
EXPORT_FUNC void Update(){

}

//handle inputs
EXPORT_FUNC void Controls(GLFWwindow* window, GetKeyFunc GetKey){
    if(GetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        std::cout << "A Pressed. " << GameObject::Find(1).PrintPosition() << std::endl;
        std::cout << "comment this out to demonstrate hotswap" << std::endl;
    }
    if(GetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        // std::cout << "Adding test object." << std::endl;
        GameObject t;
        float r0 = (rand() % 800) / 800.0 - 0.5;
        float r1 = (rand() % 800) / 800.0 - 0.5;
        float r2 = (rand() % 800) / 800.0 - 0.5;
        t.SetRenderData({
            r0, r1, 0,
            r1, r2, 0,
            r2, r0, 0
        });
        GameObject::Instantiate(t);
    }
}
