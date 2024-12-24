#pragma once

class vObj{
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual vObj* GetObj() = 0;
};
