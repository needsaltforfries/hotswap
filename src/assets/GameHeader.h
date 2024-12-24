#pragma once

#include <iostream>

#include "GameState.h"
#include "Game.h"

#include "../../include/GLFW/glfw3.h"

typedef int *(*funcPtr2) (void*, void*);
typedef int (*GetKeyFunc) (GLFWwindow*, int);

extern "C"{
    EXPORT_FUNC void Init(void** params);
    EXPORT_FUNC void GameStart();
    EXPORT_FUNC GameState* GameUpdate();
    EXPORT_FUNC void DestroyAllObjects();
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey);
    EXPORT_FUNC void CopyObject(Object* to, Object* from);
}