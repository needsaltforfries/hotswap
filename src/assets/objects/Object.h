#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define OBJ_CLASS class __declspec(dllexport) 

OBJ_CLASS Object{
    public:
        Object();
        virtual ~Object();
        virtual void Start();
        virtual void Update();
        static Object* Instantiate(Object* obj);
        std::vector<float> renderData;
        std::string fragShaderPath = "shaders/default.frag";
        std::string vertShaderPath = "shaders/default.vert";
        unsigned int id = GenerateID();
        glm::vec3 position;
    private:
        unsigned int GenerateID();
};

extern "C"{
    __declspec(dllexport) Object* NewObject();
    __declspec(dllexport) Object* InstantiateObject(Object* data);
}