#pragma once

#include "VBO.h"

class VAO{
    public:
        VAO();
        VAO(VBO& vbo);
        void Bind();
        void Unbind();
        unsigned int GetID();
    private:
        unsigned int id;
};