#include "raylib.h"
#include <iostream>

using namespace std;
//BALL
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

//Player1 Paddle
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

//Player2 Paddle
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

class PaddleAI : public Paddle1
{
public :

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
        ai.x = screenWidth - player2.width - 20;
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

            DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{ 500, 350 }, 50, 3, PINK);//Title


            //FINISH DRAWING
            EndDrawing();
        }
    }

    //End program and Clear
    CloseWindow();
    return 0;
}