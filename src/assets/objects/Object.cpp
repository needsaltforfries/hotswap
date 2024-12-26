#include "Object.h"
#include "GameState.h"
#include <typeinfo>
#include <chrono>

Object::Object(){
    //fill in properties
    position = glm::vec3(0, 0, 0);
    renderData = {-0.5f,-0.5f, 0.0f,
            0.5f,-0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

}
Object::~Object(){}

void Object::Start(){}
void Object::Update(){}

Object* Object::Instantiate(Object* obj){
    //create a new object and store important data
    Object* temp = new Object;
    temp->id = obj->id;
    temp->renderData = obj->renderData;
    temp->vertShaderPath = obj->vertShaderPath;
    temp->fragShaderPath = obj->fragShaderPath;
    GetState()->objects.push_back(temp);
    return temp;
}

unsigned int Object::GenerateID(){
    if(GetState()->objects.size() > 0){
        return GetState()->objects.back()->id + 1;
    }
    else
        return 1;
}

extern "C"{
    __declspec(dllexport) Object* NewObject(){
        return new Object;
    }
    __declspec(dllexport) Object* InstantiateObject(Object* data){
        return Object::Instantiate(data);
    }
}
