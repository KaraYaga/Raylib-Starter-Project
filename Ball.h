#pragma once
#include "raylib.h"
#include <iostream>
using namespace std;
//CONTAINS FUNCTIONS
class Ball
{
public:
    //Ball
    float x, y;
    int speedX, speedY;
    int radius;

    //Scoring
    int playerScore = 0;
    int aiScore = 0;

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
        if (x + radius >= GetScreenWidth())//Player 1 Score
        {
            playerScore++;
            ResetBall();
        }
        if (x - radius <= 0)//AI / Player 2 Score
        {
            aiScore++;
            ResetBall();
        }
    }
    //RESET BALL
    void ResetBall() 
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speedRandomized[2] = { -1,1 };
        speedX *= speedRandomized[GetRandomValue(0, 1)];
        speedY *= speedRandomized[GetRandomValue(0, 1)];
    }
};

