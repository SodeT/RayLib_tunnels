#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <Utils.hpp>
#include <raylib.h>

class Block 
{
    
public:
    Corner corners[4];
    Block(float x, float z);
};

#endif