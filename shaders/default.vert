#version 330 core
layout (location = 0) in vec3 pos;

out vec3 newPos;

void main(){
    gl_Position = vec4(pos, 1.0);
    newPos = gl_Position.xyz;
}