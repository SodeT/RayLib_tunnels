#include <iostream>
#include <vector>
#include <raylib.h>
#include <unistd.h>

#include <Utils.hpp>
#include <Block.hpp>
#include <BasicCam.hpp>

Color bg = {0, 0, 0, 255};
Color fg = {255, 255, 255, 255};

int main() 
{
    InitWindow(Width, Height, "title");
/*
    int world[8][8] = { {1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1}};
*/
    int world[8][8] = { {1, 0, 1, 0, 1, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}};
    std::vector<Block> blocks;

    for (int y = 0; y < 8; y++) 
    {
        for (int x = 0; x < 8; x++) 
        {
            if (world[y][x] == 1)
            {
                blocks.emplace_back(x, y);
            }
        }
    }

    BasicCam cam(3, 3, 70);

    while (!WindowShouldClose()) 
    {

        cam.GetCorners(blocks);
        cam.MapToScreen(blocks);
        cam.GenerateLinebuffer();
        std::vector<Line> linebuffer = cam.GetLinebuffer();

        for (size_t i = 0; i < linebuffer.size(); i++)
        {
            Line line = linebuffer[i];
            DrawLine(line.From.x, line.From.y, line.To.x, line.To.y, fg);
        }

        std::cout << cam.Direction << "\n";
        cam.Direction += 1;
        if (cam.Direction > 180)
        {
            cam.Direction -= 360;
        }
        //cam.Position.x += 0.01;
        //cam.Position.x -= 1;
        cam.Direction = (int)cam.Direction % 360;



        usleep((16.666 - GetFrameTime()) * 1000 * 1); // cap fps to 60
                                    //             ^  this is some slowmo
        BeginDrawing();
        ClearBackground(bg);
        EndDrawing();
    }
}