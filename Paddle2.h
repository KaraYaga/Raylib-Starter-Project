#pragma once
#include "raylib.h"
#include "Ball.h"
#include <iostream>

//CONTAINS FUNCTIONS
class Paddle2
{
public:
    //Boundaries
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    //DRAW PADDLE
    void Draw()
    {
        DrawRectangle(x, y, width, height, PINK);
    }

    //MOVE PADDLE
    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        LimitMovement();
    }
    //RESET
    void ResetPaddle()
    {
        y = 800 / 2 - height / 2;
    }
};