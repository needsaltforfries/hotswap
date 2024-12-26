#pragma once

#include <GLFW/glfw3.h>

typedef int *(*funcPtr2) (void*, void*);
typedef int (*GetKeyFunc) (GLFWwindow*, int);

extern "C"{
    __declspec(dllexport) void Start();
    __declspec(dllexport) void Update();
    __declspec(dllexport) void Controls(GLFWwindow* window, GetKeyFunc GetKey);
}