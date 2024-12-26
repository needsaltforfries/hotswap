#pragma once

#include <vector>
#include <map>
#include "Object.h"

#define EXPORT_FUNC __declspec(dllexport) 

extern "C"{
    typedef struct struct_GameState{
        std::vector<Object*> objects;
        std::map<unsigned int, void*>* obj_vis_map;
    }GameState;
    EXPORT_FUNC GameState* GetState();
    EXPORT_FUNC void SetState(GameState* newState);
}