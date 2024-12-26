#include "./include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "src/Hotswap.h"
#include "src/GameHeader.h"
#include "src/assets/objects/Object.h"
#include "src/assets/objects/GameState.h"
#include "src/visualizer/ObjectVisual.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

GLFWwindow* InitOpenGL();
void ProcessInput(GLFWwindow* win);
void DisplayObjects(bool objChanged);
//map object id to visualizer

std::map<unsigned int, ObjectVisual*> obj_vis_map;
Hotswap hs;
GameState state; // state copy to sync with object lib
std::vector<Object*> objectCopy;
HMODULE objectslib;

//delete this later
void* stateAddr;
void* newStateAddr;

int main(){
    //setup opengl
    GLFWwindow* win = InitOpenGL(); 
    if(win == nullptr){
        return -1;
    }
    objectslib = LoadLibraryA("objectslib.dll");
    //init necessary functions
    hs.Init();
    funcPtr get_state = (funcPtr)GetProcAddress(objectslib, "GetState");
    GameState* newState = (GameState*)(*(funcPtr)get_state)(nullptr);
    stateAddr = newState;
    newStateAddr = newState;
    state.objects = newState->objects;
    void* game_params[] = {newState, &objectslib};
    (*(funcPtr)hs.func("Init"))(game_params);
    std::cout << "Initialized libraries.\n";

    //run start functions for all objects
    (*(funcPtr)hs.func("Start"))(nullptr);
    
    //main loop
    double prevTime = glfwGetTime();
    double dT = 0.0;
    
    while(!glfwWindowShouldClose(win)){
        //update time
        double curTime = glfwGetTime();
        dT = curTime - prevTime;
        if(dT < 1.0 / 60.0){continue;}
        prevTime = curTime;

        //don't update screen if reloading lib
        if(hs.reloadStatus() == true){
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Waiting on reload to finish.\n";
            newStateAddr = (GameState*)(*(funcPtr)hs.func("GetGameState"))(nullptr);
            std::cout << "New addr @ " << newStateAddr << "\n";
            continue;
        }
        hs.delayReloadFlag = true;
        assert(stateAddr == newStateAddr);
        //update game
        ProcessInput(win);
        (*(funcPtr)hs.func("GameUpdate"))(nullptr);
        GameState* newState = (GameState*)((*get_state)(nullptr));
        state = *newState;
        bool objChanged = (objectCopy != newState->objects);
        objectCopy = newState->objects;

        //do rendering
        glClearColor(0.1f, 0.13f, 0.11f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DisplayObjects(objChanged);

        //refresh window
        glfwSwapBuffers(win);
        glfwPollEvents();
        hs.delayReloadFlag = false;
    }

    glfwTerminate();
    hs.Terminate();
    funcPtr obj_terminate = (funcPtr)GetProcAddress(objectslib, "DestroyAllObjects");
    (*obj_terminate)(nullptr);
    for(auto i = obj_vis_map.begin(); i != obj_vis_map.end(); ++i){
        delete i->second;
    }
    FreeLibrary(objectslib);
    return 0;
}

void DisplayObjects(bool objChanged){
    //update visuals if the state has changed
    if(objChanged){
        for(Object* o : state.objects){
            if(obj_vis_map.find(o->id) == obj_vis_map.end()){
                std::cout << "Adding Object " << o->id << " to display.\n";
                ObjectVisual* objVis = new ObjectVisual;
                std::cout << "\n===Render Data===\n";
                for(float f : o->renderData){
                    std::cout << f << " ";
                }
                std::cout << "\n";
                objVis->vbo = VBO(o->renderData.size()*sizeof(float), o->renderData);
                objVis->vao = VAO(objVis->vbo);
                objVis->shader = Shader(o->vertShaderPath, o->fragShaderPath);
                obj_vis_map.insert(std::make_pair(o->id, objVis));
                std::cout << "Object visualization made" << std::endl;
            }
        }
    }
    for(auto a : obj_vis_map){
        a.second->shader.Activate();
        a.second->vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        a.second->vao.Unbind();
    }
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
    glViewport(0, 0, WIDTH, HEIGHT);
    return (GLFWwindow*)win;
}
