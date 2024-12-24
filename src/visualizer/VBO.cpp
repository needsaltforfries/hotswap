#include "VBO.h"
#include <glad/glad.h>

VBO::VBO(){}
VBO::VBO(size_t rdSize, std::vector<float>& renderData){
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, rdSize, renderData.data(), GL_STATIC_DRAW);
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VBO::GetID(){
    return id;
}