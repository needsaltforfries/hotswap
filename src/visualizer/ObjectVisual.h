#pragma once

#include "VAO.h"
#include "VBO.h"
#include "Shader.h"

typedef struct object_visual_struct{
    VAO vao;
    VBO vbo;
    Shader shader;
}ObjectVisual;