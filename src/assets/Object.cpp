#include "Object.h"
#include "GameState.h"
#include <typeinfo>
#include <chrono>

unsigned int Object::GenerateID(){
    if(GetState()->objects.size() > 0){
        return GetState()->objects.back()->id + 1;
    }
    else
        return 1;
}

Object::Object(){
    //fill in properties
    for(int i = 0; i < 3; ++i){
        this->transform[i] = 0.0;
    }
    renderData = {-0.5f,-0.5f, 0.0f,
            0.5f,-0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

}

Object::~Object(){}

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

Object* Object::Instantiate(Object* obj){
    Object* temp = obj->CreateNew();
    temp->id = obj->id;
    temp->renderData = obj->renderData;
    temp->vertShaderPath = obj->vertShaderPath;
    temp->fragShaderPath = obj->fragShaderPath;
    GetState()->objects.push_back(temp);
    return temp;
}