#include <iostream>
#include "raylib.h"
#include "Settings.h"
#include "Ball.h"

class PlayerPaddle
{
public:

    PlayerPaddle(float posX, float posY, float width, float height, int speed)
        :m_PosX{ posX }, m_PosY{ posY }, m_Width{ width }, m_Height{ height }, m_Speed{ speed }
    {
    }

    void Draw() const
    {
        DrawRectangle(m_PosX, m_PosY, m_Width, m_Height, WHITE);
    }

    void Update()
    {

        if (IsKeyDown(KEY_W) && m_PosY >= 20)
        {
            m_PosY = m_PosY - m_Speed;
        }
        if (IsKeyDown(KEY_S) && (m_PosY + m_Height) <= GetScreenHeight() - 20)
        {
            m_PosY = m_PosY + m_Speed;
        }
    }

    float GetPosX() const { return m_PosX; }
    float GetPosY() const { return m_PosY; }
    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }

protected:
    float m_PosX{};
    float m_PosY{};
    float m_Width{};
    float m_Height{};
    int m_Speed{};
};

class ComputerPaddle : public PlayerPaddle
{
public:

    ComputerPaddle(float posX, float posY, float width, float height, int speed)
        :PlayerPaddle{ posX,posY,width,height,speed }
    {
    }

    void Update(int ballPosY)
    {
        if ((m_PosY + (m_Height / 2)) < ballPosY && m_PosY + m_Height < GetScreenHeight() - 125)
        {
            m_PosY = m_PosY + m_Speed;
        }

        if ((m_PosY + (m_Height / 2)) > ballPosY && m_PosY > 125)
        {
            m_PosY = m_PosY - m_Speed;
        }
    }

};


int main()
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Pong.Kuntay");
    SetTargetFPS(Settings::targetFPS);
    Ball mainBall{Settings::screenWidth / 2,Settings::screenHeight / 2,5,5,25.f };
    PlayerPaddle playerPaddle{Settings::screenWidth - 35,Settings::screenHeight / 2 - 100, 35, 200, 5 };
    ComputerPaddle computerPaddle{ 0, Settings::screenHeight / 2 - 100, 35, 200 ,6 };



    while (WindowShouldClose() == false)
    {


        //UPDATING
        mainBall.Update();
        playerPaddle.Update();
        computerPaddle.Update(mainBall.GetPosY());

        //CHECKING FOR COLLISION WITH PLAYER
        if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(),mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ playerPaddle.GetPosX(),playerPaddle.GetPosY(),playerPaddle.GetWidth(),playerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }
        //CHECKING FOR COLLISION WITH COMPUTER
        else if (CheckCollisionCircleRec(Vector2{ mainBall.GetPosX(),mainBall.GetPosY() },
            mainBall.GetRadius(),
            Rectangle{ computerPaddle.GetPosX(),computerPaddle.GetPosY(),computerPaddle.GetWidth(),computerPaddle.GetHeight() }))
        {
            mainBall.BounceBallOnX();
        }


        //DRAWING

        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(Settings::screenWidth / 2, 0, Settings::screenWidth / 2, Settings::screenHeight, WHITE);

        mainBall.Draw();
        playerPaddle.Draw();
        computerPaddle.Draw();

        DrawText(TextFormat("%i", Settings::computerScore), Settings::screenWidth / 2 - 80, 20, 80, WHITE);
        DrawText(TextFormat("%i", Settings::playerScore), Settings::screenWidth / 2 + 40, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}