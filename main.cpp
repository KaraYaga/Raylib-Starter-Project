#include "raylib.h"
#include "Paddle1.h"
#include <iostream>
using namespace std;

//INITIALIZE
int main() {
    
    //Game States
    bool isPvP = false;
    bool playingGame = false;

    //Instances
    Ball ball;
    Paddle1 player1;
    Paddle2 player2;
    PaddleAI ai;

    //Window State
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "PONG");
    SetTargetFPS(60);

    //Font LIbrary
    Font ft = LoadFont("resources/fonts/pixantiqua.png");

    //Ball
    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    //Paddle Player1
    player1.width = 25;
    player1.height = 120;
    player1.x = 20;
    player1.y = screenHeight / 2 - player1.height / 2;
    player1.speed = 6;

    if (isPvP) 
    {
        //Paddle Player2
        player2.width = 25;
        player2.height = 120;
        player2.x = screenWidth - player2.width - 20;
        player2.y = screenHeight / 2 - player2.height / 2;
        player2.speed = 6;
    }
    else 
    {
        //Paddle AI (Replace Player2)
        ai.width = 25;
        ai.height = 120;
        ai.x = screenWidth - ai.width - 20;
        ai.y = screenHeight / 2 - ai.height / 2;
        ai.speed = 6;
    }

    //Update Loop
    while (!WindowShouldClose()) 
    {
        if (playingGame) 
        {
            //DRAWING LOOP
            BeginDrawing();

            //UPDATE LOOP
            player1.Update();
            ball.Update();
            if (isPvP)
            {
                player2.Update();
            }
            else
            {
                ai.Update(ball.y);
            }

            //Collision Detection
            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height })) 
            {
                ball.speedX *= -1;
            }
            if (isPvP) 
            {
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height }))
                {
                    ball.speedX *= -1;
                }
            }
            else 
            {
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ ai.x, ai.y, ai.width, ai.height }))
                {
                    ball.speedX *= -1;
                }
            }

            ClearBackground(BLACK);//Clears Console Background between frames
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);//Middle Line

            //SCORE
            DrawText(TextFormat("%i", ball.playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE); //Player 1 
            DrawText(TextFormat("%i", ball.aiScore), screenWidth / 4 - 20, 20, 80, WHITE); //Player 2 / AI
            
            ball.Draw();//Ball

            player1.Draw();//Player 1
            if (isPvP)
            {
                player2.Draw();//Player 2
            }
            else
            {
                ai.Draw();//Player AI
            }

            //FINISH DRAWING
            EndDrawing();
        }
        else 
        {
            BeginDrawing();
            ClearBackground(BLACK);

            DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{ 350, 75 }, 50, 3, PINK);//Title
            DrawText("Press G for MultiPlayer",  450, 400, 30, WHITE);
            DrawText("Press H for Single Player", 450, 450, 30, WHITE);

            if (IsKeyDown(KEY_G)) 
            {
                isPvP = true;
                playingGame = true;
            }
            if (IsKeyDown(KEY_H)) 
            {
                isPvP = false;
                playingGame = true;
            }


            //FINISH DRAWING
            EndDrawing();
        }
    }

    //End program and Clear
    CloseWindow();
    return 0;
}