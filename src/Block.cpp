#include <Block.hpp>
#include <raylib.h>
#include <iostream>
#include <Block.hpp>

Block::Block(float x, float z) 
{

        corners[0].Position.x = x * Scale;
        corners[0].Position.y = z * Scale;

        corners[1].Position.x = x * Scale + Scale;
        corners[1].Position.y = z * Scale;

        corners[2].Position.x = x * Scale;
        corners[2].Position.y = z * Scale + Scale;

        corners[3].Position.x = x * Scale + Scale;
        corners[3].Position.y = z * Scale + Scale;

}
