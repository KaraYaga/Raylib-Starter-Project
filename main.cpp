#include "raylib.h"
#include "Paddle1.h"
#include <iostream>
using namespace std;

//INITIALIZE
int main() {

    //Game States
    bool isPvP = false;
    bool playingGame = false;
    bool gameOver = false;
    bool gameMenu = true;

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

    //Font Library
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
        // Paddle Player2
        player2.width = 25;
        player2.height = 120;
        player2.x = screenWidth - player2.width - 20;
        player2.y = screenHeight / 2 - player2.height / 2;
        player2.speed = 6;
    }
    if (!isPvP)
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
        //GAME OVER
        if (gameOver) 
        {
            playingGame = false;
            gameMenu = false;
            BeginDrawing();
            ClearBackground(BLACK);

            if (ball.playerScore >= 10) {
                DrawTextEx(ft, "PLAYER 1 WINS!", Vector2{ 475, 350 }, 50, 3, PINK);//PLAYER WIN
            }
            else if (ball.opponentScore >= 10) {
                DrawTextEx(ft, "PLAYER 2 WINS!", Vector2{ 475, 350 }, 50, 3, PINK);//AI WIN
            }
            DrawText("Press SPACE to Restart", 475, 400, 30, WHITE);

            if (IsKeyDown(KEY_SPACE)) 
            {
                playingGame = false;
                gameOver = false;
                gameMenu = true;
            }

            EndDrawing();
        }
        //MAIN MENU
        if (gameMenu) 
        {
            playingGame = false;
            gameOver = false;
            {
                BeginDrawing();
                ClearBackground(BLACK);

                DrawTextEx(ft, "PONGO BONGO GOGO GIRL!", Vector2{ 350, 75 }, 50, 3, PINK);//Title
                DrawText("Press H for MultiPlayer", 450, 400, 30, WHITE);
                DrawText("Press G for Single Player", 450, 450, 30, WHITE);
                ball.ResetScore();

                if (IsKeyDown(KEY_H))
                {
                    isPvP = true;
                    playingGame = true;
                    gameMenu = false;
                    cout << ("Multiplayer Selected");
                }
                if (IsKeyDown(KEY_G))
                {
                    isPvP = false;
                    playingGame = true;
                    gameMenu = false;
                }
                //FINISH DRAWING
                EndDrawing();
            }
        }
        //PLAYING GAME
        if (playingGame)
        {
            //PvP Player vs. Player
            if (isPvP)
            {
                //DRAWING LOOP
                BeginDrawing();

                //UPDATE LOOP
                player1.Update();
                player2.Update();
                cout << ("[DEBUG]: Player 2 Updated");
                ball.Update();
               
                // PLAYER 1 PADDLE BOUNDARIES
                if (player1.y < 0) 
                {
                    player1.y = 0;
                }
                else if (player1.y + player1.height > screenHeight) {
                    player1.y = screenHeight - player1.height;
                }
                // PLAYER 2 PADDLE BOUNDARIES
                if (player2.y < 0) 
                {
                    player2.y = 0;
                }
                else if (player2.y + player2.height > screenHeight) 
                {
                     player2.y = screenHeight - player2.height; 
                }

                //COLLISION DETECTION
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height }))
                {
                    ball.speedX *= -1;
                }
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height }))
                {
                    ball.speedX *= -1;
                }
                ClearBackground(BLACK);//Clears Console Background between frames
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);//Middle Line

                //SCORE
                DrawText(TextFormat("%i", ball.playerScore), screenWidth / 4 - 20, 20, 80, WHITE); //Player 1 
                DrawText(TextFormat("%i", ball.opponentScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE); //Player 2

                ball.Draw();//Ball
                player1.Draw();//Player 1
                player2.Draw();//Player 2
               
                // Check for game over conditions
                if (ball.playerScore >= 10 || ball.opponentScore >= 10) 
                {
                    gameOver = true;
                }

                //FINISH DRAWING
                EndDrawing();
            }
            //PvC Player vs. Computer
            if (!isPvP)
            {
                //DRAWING LOOP
                BeginDrawing();

                //UPDATE LOOP
                player1.Update();
                ai.Update(ball.y);
                ball.Update();

                // PLAYER 1 PADDLE BOUNDARIES
                if (player1.y < 0) {
                    player1.y = 0;
                }
                else if (player1.y + player1.height > screenHeight) {
                    player1.y = screenHeight - player1.height;
                }
                // AI PADDLE BOUNDARIES
                if (ai.y < 0) 
                {
                    ai.y = 0;
                }
                else if (ai.y + ai.height > screenHeight) 
                {
                    ai.y = screenHeight - ai.height;
                }
                
                //Collision Detection
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height }))
                {
                    ball.speedX *= -1;
                }
                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ ai.x, ai.y, ai.width, ai.height }))
                {
                    ball.speedX *= -1;
                }

                ClearBackground(BLACK);//Clears Console Background between frames
                DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);//Middle Line

                //SCORE
                DrawText(TextFormat("%i", ball.playerScore), screenWidth / 4 - 20, 20, 80, WHITE); //Player 1 
                DrawText(TextFormat("%i", ball.opponentScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE); //AI

                ball.Draw();//Ball
                player1.Draw();//Player 1
                ai.Draw();//Player AI

                // Check for game over conditions
                if (ball.playerScore >= 10 || ball.opponentScore >= 10) 
                {
                    gameOver = true;
                }

                //FINISH DRAWING
                EndDrawing();
            }
        }
    }

    //End program and Clear
    CloseWindow();
    return 0;
};