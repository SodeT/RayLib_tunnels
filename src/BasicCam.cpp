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
            Vector2 cornerPos = blocks[i].Corners[j].Position;
            float cornerAngle = GetAngle(cornerPos, Position);
            float relativeAngle = cornerAngle + Direction;

            blocks[i].Corners[j].Direction = relativeAngle;

            float distance = GetDistance(cornerPos, Position);
            blocks[i].Corners[j].Distance = distance;
        }
    }
    return;
}

void BasicCam::MapToScreen(std::vector<Block>& blocks)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            MappedCorner mCorner;
            mCorner.Distance = blocks[i].Corners[j].Distance;
            float dir = blocks[i].Corners[j].Direction;
            if (dir > 180)
                dir -= 360;
            mCorner.XOffset = HMid + dir * _fovPixels;

            blocks[i].MappedCorners[j] = mCorner;
        }
    }
    return;
}

void BasicCam::GenerateLinebuffer(std::vector<Block>& blocks)
{
    _linebuffer.clear();
    for (size_t i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float height = _depthEffect / blocks[i].MappedCorners[j].Distance;
            Line line;
            line.From = {blocks[i].MappedCorners[j].XOffset, VMid - height};
            line.To = {blocks[i].MappedCorners[j].XOffset, VMid + height};
            _linebuffer.push_back(line);
        }
    }

    return;
}

void BasicCam::OccludeCorners()
{

    return;
}

void BasicCam::HandleInput()
{

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
    else
    {
        _velocity.x *= _friction;
        _velocity.y *= _friction;

        if (abs(_velocity.x) < 0.001)
            _velocity.x = 0;
        if (abs(_velocity.y) < 0.001)
            _velocity.y = 0;
    }

    Vector2 tempPos = Position;
    tempPos.x += _velocity.x;
    tempPos.y += _velocity.y;

    int gridX = (int)tempPos.x / Scale;
    int gridY = (int)tempPos.y / Scale;

    // Collision detection in world map
    if (gridX >= 0 && gridX < WorldSize && gridY >= 0 && gridY < WorldSize)
    {
        if (World[gridY][gridX] != 1)
        {
            Position = tempPos;
        }
        else
        {
            _velocity = {0, 0};
        }
    }
    else 
    {
        Position = tempPos;   
    }

    // Rotation
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