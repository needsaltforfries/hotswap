#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glad/glad.h>

class Shader{
    public:
        Shader();
        Shader(std::string vertex, std::string frag);
        std::string loadShader(std::string file);
        static GLuint linkShaders();
        void Activate();
        void Delete();
        GLuint id;
};