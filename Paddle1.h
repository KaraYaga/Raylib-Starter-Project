#pragma once
#include "raylib.h"
#include <iostream>
#include "Ball.h"
using namespace std;

class Paddle1
{
protected:
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
        if (IsKeyDown(KEY_W))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }
    }
};

//INHERIT FROM PADDLE1
class Paddle2 : public Paddle1
{
public:

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
};

//INHERIT FROM PADDLE  1
class PaddleAI : public Paddle1
{
public:

    //AI move to Hit Ball
    void Update(int ballY)
    {
        if (y + height / 2 > ballY)
        {
            y = y - speed;
        }
        if (y + height / 2 < ballY)
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

