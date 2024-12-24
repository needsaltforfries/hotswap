#include "Shader.h"

void cerrs(unsigned int shader, std::string type){
    int success;
    char infoLog[512];
    
    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED -" << type << "\n" <<
            infoLog << std::endl;
        }
        else{
            std::cout << type << " success\n";
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR -" << type << "\n" << 
            infoLog << std::endl;
        }
    }
}

//read shader from shader file
std::string Shader::loadShader(std::string shader){
    std::string shaderSrc;
    std::string line;
    std::ifstream in(shader);
    if(!in.is_open())
        throw(errno);
    while(getline(in, line)){
        shaderSrc += line + '\n';
    }
    // std::cout << "loaded shader " << shader << std::endl;
    return shaderSrc;
}

Shader::Shader(){}

Shader::Shader(std::string vert, std::string frag){
    //steps:
        //1. get shader source code
        //2. create shader
        //3. compile shader

    //vertex shader
    std::string vertCode = loadShader(vert);
    const GLchar* vertSrc = vertCode.c_str();
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);
    cerrs(vertShader, "VERTEX");

    //fragment shader
    std::string fragCode = loadShader(frag);
    const GLchar* fragSrc = fragCode.c_str();
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);
    cerrs(fragShader, "FRAGMENT");

    //link the two shaders
    id = glCreateProgram();
    glAttachShader(id, vertShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);
    cerrs(id, "PROGRAM");

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::Activate(){
    glUseProgram(id);
}

void Shader::Delete(){
    glDeleteShader(id);
}