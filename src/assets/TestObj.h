#ifndef TEST_OBJ_H
#define TEST_OBJ_H

#include "Object.h"
#include "GameState.h"
class TestObj : public Object{
    public:
        TestObj();
        ~TestObj() override;
        void Start() override;
        void Update() override;
        Object* CreateNew() override;
};

#endif