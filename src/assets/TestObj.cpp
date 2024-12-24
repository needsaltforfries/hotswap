#include "TestObj.h"

TestObj::TestObj() : Object(){
    
}

TestObj::~TestObj(){}

void TestObj::Start(){
    std::cout << "testObj pos: " << PosXYZ() << std::endl;
}

void TestObj::Update(){
    
}

Object* TestObj::CreateNew(){
    return new TestObj;
}