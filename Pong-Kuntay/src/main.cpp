#include <iostream>
#include "raylib.h"

namespace Settings
{
    int playerScore{ 0 };
    int computerScore{ 0 };
}

class Ball
{
public:

    Ball(float posX, float posY, float speedX, float speedY, float radius)
        :m_PosX{ posX }, m_PosY{ posY }, m_SpeedX{ speedX }, m_SpeedY{ speedY }, m_Radius{ radius }
    {

    }

    void ResetBall()
    {
        m_PosX = GetScreenWidth() / 2;
        m_PosY = GetScreenHeight() / 2;

        int speed_choices[2]{ -5,5 };
        m_SpeedX = speed_choices[GetRandomValue(0, 1)];
        m_SpeedY = speed_choices[GetRandomValue(0, 1)];

    }

    void Draw() const
    {
        DrawCircle(m_PosX, m_PosY, m_Radius, WHITE);
    }

    void Update()
    {
        if (m_PosY + m_Radius >= GetScreenHeight() || m_PosY - m_Radius <= 0)
        {
            m_SpeedY *= -1;
        }

        if (m_PosX + m_Radius >= GetScreenWidth()) //COMPUTER SCORES
        {
            ResetBall();
            Settings::computerScore++;
        }
        else if (m_PosX - m_Radius <= 0) //PLAYER SCORES
        {
            ResetBall();
            Settings::playerScore++;
        }

        m_PosX += m_SpeedX;
        m_PosY += m_SpeedY;
    }

    float GetPosY() const
    {
        return m_PosY;
    }

    float GetPosX() const
    {
        return m_PosX;
    }

    float GetRadius() const
    {
        return m_Radius;
    }

    void BounceBallOnX()
    {
        m_SpeedX *= -1;
        if (m_SpeedX < 0) { m_SpeedX -= 0.5f; }
        else if (m_SpeedX > 0) { m_SpeedX += 0.5f; }

        if (m_SpeedY < 0) { m_SpeedY -= 0.5f; }
        else if (m_SpeedY > 0) { m_SpeedY += 0.5f; }
    }

private:

    float m_PosX{};
    float m_PosY{};
    float m_SpeedX{};
    float m_SpeedY{};
    float m_Radius{};
};


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
    const int screenWidth{ 1600 };
    const int screenHeight{ 900 };
    const int targetFPS{ 144 };


    InitWindow(screenWidth, screenHeight, "Pong.Kuntay");
    SetTargetFPS(targetFPS);
    Ball mainBall{ screenWidth / 2,screenHeight / 2,5,5,25.f };
    PlayerPaddle playerPaddle{ screenWidth - 35, screenHeight / 2 - 100, 35, 200, 5 };
    ComputerPaddle computerPaddle{ 0, screenHeight / 2 - 100, 35, 200 ,6 };



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
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        mainBall.Draw();
        playerPaddle.Draw();
        computerPaddle.Draw();

        DrawText(TextFormat("%i", Settings::computerScore), screenWidth / 2 - 80, 20, 80, WHITE);
        DrawText(TextFormat("%i", Settings::playerScore), screenWidth / 2 + 40, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}