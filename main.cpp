#include "./include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>

#include "src/Hotswap.h"
#include "src/assets/Game.h"
#include "src/assets/Object.h"
#include "src/assets/TestObj.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

GLFWwindow* InitOpenGL();
void ProcessInput(GLFWwindow* win);

Hotswap hs;

int main(){
    //setup opengl
    GLFWwindow* win = InitOpenGL(); 
    if(win == nullptr){
        return -1;
    }
    //init hotswap lib

    hs.Init();

    //run start functions for all objects
    (*(funcPtr)hs.func("Start"))(nullptr);
    GameState* state = nullptr;
    //main loop
    while(!glfwWindowShouldClose(win)){
        //don't update screen if reloading lib
        if(hs.reloadStatus() == true){continue;}
        hs.delayReloadFlag = true;

        ProcessInput(win);
        state = (GameState*)(*(funcPtr)hs.func("GetState"))(nullptr);

        //do rendering
        glClearColor(0.1f, 0.63f, 0.81f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //refresh window
        glfwSwapBuffers(win);
        glfwPollEvents();

        //sample execution of function from DLL
        (*(funcPtr)hs.func("GameUpdate"))(nullptr);
        (*(funcPtr)hs.func("Display"))(nullptr);

        hs.delayReloadFlag = false;
    }
    glfwTerminate();
    (*(funcPtr)hs.func("DestroyAllObjects"))(nullptr);
    hs.Terminate();
    return 0;
}

void ProcessInput(GLFWwindow* win){
    //ESC to quit
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);
    //pass params to Game to handle inputs
    (*(funcPtr2)hs.func("HandleInput"))(win, (void*)glfwGetKey);
}

GLFWwindow* InitOpenGL(){
    //init opengl version 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //create window
    void* win = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if(win == NULL){
        std::cout << "can't make window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent((GLFWwindow*)win); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    return (GLFWwindow*)win;
}
