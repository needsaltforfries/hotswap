#include "VAO.h"
#include <glad/glad.h>

VAO::VAO(){}

VAO::VAO(VBO& vbo){
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.GetID());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    Unbind();
    vbo.Unbind();
}

void VAO::Bind(){
    glBindVertexArray(id);
}

void VAO::Unbind(){
    glBindVertexArray(0);
}

unsigned int VAO::GetID(){
    return id;
}
