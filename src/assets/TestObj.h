#ifndef TEST_OBJ_H
#define TEST_OBJ_H

#include "Object.h"
#include "Game.h"

EXPORT_CLASS TestObj : public Object{
    public:
        TestObj();
        ~TestObj() override;
        void Display() override;
        void Start() override;
        void Update() override;
        Object* Instantiate() override;
};

#endif