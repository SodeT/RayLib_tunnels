#include <Block.hpp>
#include <raylib.h>
#include <iostream>
#include <Block.hpp>

Block::Block(float x, float z) 
{

        Corners[0].Position.x = x * Scale;
        Corners[0].Position.y = z * Scale;

        Corners[1].Position.x = x * Scale + Scale;
        Corners[1].Position.y = z * Scale;

        Corners[2].Position.x = x * Scale;
        Corners[2].Position.y = z * Scale + Scale;

        Corners[3].Position.x = x * Scale + Scale;
        Corners[3].Position.y = z * Scale + Scale;

}
