#include <iostream>
#include <vector>
#include <raylib.h>

#include <Utils.hpp>
#include <Block.hpp>
#include <BasicCam.hpp>

Color bg = {0, 0, 0, 255};
Color fg = {255, 255, 255, 255};

const int Width = 640;
const int Height = 340;
const int Mid = Width / 2;

int main() 
{
    InitWindow(Width, Height, "title");

    int world[8][8] = { {1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1}};

    std::vector<Block> blocks;

    for (int x = 0; x < 8; x++) 
    {
        for (int z = 0; z < 8; z++) 
        {
            if (world[x][z] == 1)
            {
                blocks.emplace_back(x, z);
            }
        }
    }

    while (!WindowShouldClose()) 
    {

        DrawPixel(200, 200, fg);
        DrawLine(100, 100, 200, -10, fg);
        BeginDrawing();
        ClearBackground(bg);
        EndDrawing();
    }
}