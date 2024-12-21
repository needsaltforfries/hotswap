#pragma once

#include <iostream>
#include <vector>
#include "Object.h"
#include "../../include/GLFW/glfw3.h"

#define EXPORT_FUNC __declspec(dllexport) 

typedef int *(*funcPtr2) (void*, void*);
typedef int (*GetKeyFunc) (GLFWwindow*, int);

extern "C"{
    typedef struct struct_GameState{
        std::vector<Object*> objects;
    }GameState;
    EXPORT_FUNC void Display();
    EXPORT_FUNC void Start();
    EXPORT_FUNC GameState* GameUpdate();
    EXPORT_FUNC GameState* GetState();
    EXPORT_FUNC void SetState(GameState* newState);
    EXPORT_FUNC void DestroyAllObjects();
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey);
}