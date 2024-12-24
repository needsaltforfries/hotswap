#pragma once

#include <vector>

class VBO{
    public:
        VBO();
        VBO(size_t rdSize, std::vector<float>& renderData);
        void Bind();
        void Unbind();
        unsigned int GetID();
    private:
        unsigned int id;
};