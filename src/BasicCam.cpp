#include <raylib.h>
#include <BasicCam.hpp>
#include <stdlib.h>
#include <Utils.hpp>

BasicCam::BasicCam(float x, float z, float Fov) 
    :Position({x * Scale, z * Scale}), Fov(Fov) 
{
    _fovPixels = Width / Fov;
}

std::vector<Line> BasicCam::GetLinebuffer()
{
    return _linebuffer;
}

void BasicCam::GetCorners(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            Vector2 blockPos = blocks[i].corners[j].Position;
            float cornerAngle = GetAngle(blockPos, Position);
            float relativeAngle = cornerAngle - Direction;

            if (relativeAngle > 180)
            {
                relativeAngle -= 360;
            }

            blocks[i].corners[j].Direction = relativeAngle;

            float distance = GetDistance(blockPos, Position);
            blocks[i].corners[j].Distance = distance;
        }
    }
    return;
}

void BasicCam::MapToScreen(std::vector<Block>& blocks)
{
    _mappedCorners.clear();
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            MappedCorner corner;
            corner.Distance = blocks[i].corners[j].Distance;
            corner.XOffset = blocks[i].corners[j].Direction * _fovPixels;

            _mappedCorners.push_back(corner);
        }
    }
    return;
}

void BasicCam::GenerateLinebuffer()
{
    _linebuffer.clear();
    for (size_t i = 0; i < _mappedCorners.size(); i++)
    {
        float height = 1000 / _mappedCorners[i].Distance;
        Line line;
        line.From = {_mappedCorners[i].XOffset, Mid - height};
        line.To = {_mappedCorners[i].XOffset, Mid + height};
        _linebuffer.push_back(line);
    }


    return;
}

/*
void BasicCam::Get
*/