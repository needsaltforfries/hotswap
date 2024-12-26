#pragma once

#include "objects/Object.h"
#include <map>

#define GAMEOBJ_CLASS class __declspec(dllexport)  

//wrapper for object
GAMEOBJ_CLASS GameObject{
    public:
        GameObject();
        GameObject(Object* data);
        virtual ~GameObject();
        virtual void Start();
        virtual void Update();
        
        void SetRenderData(std::vector<float> vertices);
        static GameObject Instantiate(GameObject& obj);
        static GameObject Find(unsigned int id);
        std::string PrintPosition();

        Object* data = nullptr;
        Object* GetData();
    private:
        static std::map<unsigned int, GameObject> objects_map;
};