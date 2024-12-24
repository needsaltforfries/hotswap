#version 330 core

in vec3 newPos;
out vec4 FragColor;

void main(){
    vec3 offset = vec3(0.2, 0.2, 0.2);
    FragColor = vec4((newPos + offset), 1.0f);
}