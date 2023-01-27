#include <raylib.h>
#include <BasicCam.hpp>
#include <stdlib.h>
#include <Utils.hpp>
#include <cmath>

BasicCam::BasicCam(float x, float z, float Fov) 
    : Position({x * Scale, z * Scale}), Fov(Fov) 
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
            Vector2 cornerPos = blocks[i].corners[j].Position;
            float cornerAngle = GetAngle(cornerPos, Position);
            float relativeAngle = cornerAngle + Direction;

            blocks[i].corners[j].Direction = relativeAngle;

            float distance = GetDistance(cornerPos, Position);
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
            float dir = blocks[i].corners[j].Direction;
            if (dir > 180)
                dir -= 360;
            corner.XOffset = HMid + dir * _fovPixels;

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
        float height = _depthEffect / _mappedCorners[i].Distance;
        Line line;
        line.From = {_mappedCorners[i].XOffset, VMid - height};
        line.To = {_mappedCorners[i].XOffset, VMid + height};
        _linebuffer.push_back(line);
    }

    return;
}

void BasicCam::OccludeCorners()
{

    return;
}



void BasicCam::HandleInput()
{
    _velocity = {0, 0};

    if (IsKeyDown(KEY_UP))
    {
        _velocity.x = -cos(DegToRad(Direction)) * _speed;
        _velocity.y = sin(DegToRad(Direction)) * _speed;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        _velocity.x = -cos(DegToRad(Direction)) * -_speed;
        _velocity.y = sin(DegToRad(Direction)) * -_speed;
    }

    

    Position.x += _velocity.x;
    Position.y += _velocity.y;

    if (IsKeyDown(KEY_LEFT))
    {
        Direction += _rotationSpeed;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        Direction -= _rotationSpeed;
    }

    if (Direction > 360)
    {
        Direction -= 360;
    }
    else if (Direction < 0)
    {
        Direction += 360;
    }

    return;
}