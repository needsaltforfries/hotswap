#include "TestObj.h"

TestObj::TestObj() : Object(){

}
TestObj::~TestObj(){}

void TestObj::Display(){
    
}

void TestObj::Start(){
    std::cout << "testObj pos: " << PosXYZ() << std::endl;
}

void TestObj::Update(){
    
}

Object* TestObj::Instantiate(){
    Object* instance = new TestObj;
    GetState()->objects.push_back(instance);
    std::cout << "instantiated testobj" << std::endl;
    return instance;
}