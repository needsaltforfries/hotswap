#include "Game.h"
#include "GameState.h"
#include "GameHeader.h"
#include "TestObj.h"

//do stuff before first update
EXPORT_FUNC void Start(){

    std::cout << "Game Start!\n";
    TestObj t;
    std::cout << "t obj temp\n";
    Object::Instantiate(&t);
    std::cout << "t instantiated\n";
}
//this function is called every update
EXPORT_FUNC void Update(){

}
//handle inputs
EXPORT_FUNC void Controls(GLFWwindow* window, GetKeyFunc GetKey){
    if(GetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        std::cout << "A Pressed, testing object: " << GetState()->objects.at(0)->PosXYZ() << std::endl;
        // std::cout << "comment this out to demonstrate hotswap" << std::endl;
    }
    if(GetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        std::cout << "Adding test object." << std::endl;
        TestObj t;
        float r0 = (rand() % 800) / 800.0 - 0.5;
        float r1 = (rand() % 800) / 800.0 - 0.5;
        float r2 = (rand() % 800) / 800.0 - 0.5;
        t.renderData = {
            r0, r1, 0,
            r1, r2, 0,
            r2, r0, 0
        };
        Object::Instantiate(&t);
    }
}
