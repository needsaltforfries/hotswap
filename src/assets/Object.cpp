#include "Object.h"

Object::Object(){
    //fill in properties
    for(int i = 0; i < 3; ++i){
        this->transform[i] = 0.0;
    }
    renderData = {-0.5f,-0.5f, 0.0f,
            0.5f,-0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
    // shader = Shader("../shaders/default.vert", "../shaders/default.frag");
}
Object::~Object(){}

void Object::Display(){
    // vbo = VBO(sizeof(renderData.data()), renderData);
    // glUseProgram(shader.id);
    // glBindVertexArray(vao.GetID());
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Object::Start(){

}

void Object::Update(){
    std::cout << "updating object" << std::endl;
}

std::string Object::PosXYZ(){
    std::string val;
    std::ostringstream oss;  // Create an output string stream
    oss << transform[0] << " " << transform[1] << " " << transform[2];  // Add the values to the stream
    val = oss.str();  // Convert the stream to a string
    return val;
}

Object* Object::Instantiate(){
    std::cerr << "Can't instantiate abstract Object" << std::endl;
    return nullptr;
}