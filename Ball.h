#pragma once
#include "raylib.h"
#include <iostream>
using namespace std;

class Ball
{
public:
    float x, y;
    int speedX, speedY;
    int radius;

    //DRAW BALL
    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
    //MOVE BALL
    void Update()
    {
        x += speedX;
        y += speedY;

        //Check Collisions
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speedX *= -1;
        }
    }
};

