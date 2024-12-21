#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
// #include "../Shader.h"
// #include "../VBO.h"
// #include "../VAO.h"

#define EXPORT_CLASS class __declspec(dllexport) 

EXPORT_CLASS Object{
    public:
        Object();
        virtual ~Object();
        virtual void Display() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual Object* Instantiate();
        std::string PosXYZ();
    protected:
        float transform[3];
        std::vector<float> renderData;
        // VAO vao;
        // VBO vbo;
        // Shader shader;
};