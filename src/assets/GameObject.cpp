#include "GameObject.h"
#include "../GameHeader.h"
#include <cassert>

typedef void *(*funcPtr) (void *);

std::map<unsigned int, GameObject> GameObject::objects_map;

GameObject::GameObject(){
    //make a new object
    HMODULE* obj_dll = GetObjectLib();
    FARPROC proc = GetProcAddress(*obj_dll, "NewObject");
    assert(proc);
    data = (Object*)(*(funcPtr)proc)(nullptr);
}

GameObject::GameObject(Object* data){
    data = data;
}

GameObject::~GameObject(){}

void GameObject::Start(){
    std::cout << PrintPosition() << std::endl;
}

void GameObject::Update(){
    
}

void GameObject::SetRenderData(std::vector<float> vertices){
    data->renderData = vertices;
}

GameObject GameObject::Instantiate(GameObject& t){
    HMODULE* obj_dll = GetObjectLib();
    FARPROC proc = GetProcAddress(*obj_dll, "InstantiateObject");
    assert(proc);
    t.data = (Object*)(*(funcPtr)proc)(t.data);
    std::cout << t.data->id << std::endl;
    objects_map.insert(std::make_pair(t.data->id, t));
    return t;
}

GameObject GameObject::Find(unsigned int id){
    return objects_map[id];
}

std::string GameObject::PrintPosition(){
    std::string temp = "";
    temp += "Position of (" + std::to_string(data->id) + "): " +
        std::to_string(data->position.x) + " " +
        std::to_string(data->position.y) + " " +
        std::to_string(data->position.z) + " ";
    return temp;
}