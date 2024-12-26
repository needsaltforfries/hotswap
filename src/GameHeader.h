#pragma once

#include <iostream>

#include "Game.h"
#include "assets/objects/GameState.h"

#include <GLFW/glfw3.h>

typedef int *(*funcPtr2) (void*, void*);
typedef int (*GetKeyFunc) (GLFWwindow*, int);

#define EXPORT_FUNC __declspec(dllexport)

extern "C"{
    EXPORT_FUNC void Init(void** params);
    EXPORT_FUNC void GameStart();
    EXPORT_FUNC GameState* GameUpdate();
    EXPORT_FUNC GameState* GetGameState();
    EXPORT_FUNC HMODULE* GetObjectLib();
    EXPORT_FUNC void SetGameState(GameState* state);
    EXPORT_FUNC void HandleInput(GLFWwindow* window, GetKeyFunc GetKey);
}