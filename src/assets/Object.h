#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <memory>

#define EXPORT_CLASS class __declspec(dllexport) 

EXPORT_CLASS Object{
    public:
        Object();
        Object(Object* other);
        virtual ~Object();
        virtual void Start() = 0;
        virtual void Update() = 0;
        static Object* Instantiate(Object* obj);
        std::string PosXYZ();
        std::vector<float> renderData;
        std::string fragShaderPath = "shaders/default.frag";
        std::string vertShaderPath = "shaders/default.vert";
        unsigned int id = GenerateID();
        virtual Object* CreateNew() = 0;
    protected:
        float transform[3];
        unsigned int GenerateID();
        // VAO vao;
        // VBO vbo;
        // Shader shader;
};