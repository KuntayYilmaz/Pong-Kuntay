#pragma once

class Ball
{
public:
    Ball(float posX, float posY, float speedX, float speedY, float radius);

    void ResetBall();

    void Draw() const;

    void Update();

    float GetPosY() const { return m_PosY; }
    float GetPosX() const { return m_PosX; }
    float GetRadius() const { return m_Radius; }

    void BounceBallOnX();

private:

    float m_PosX{};
    float m_PosY{};
    float m_SpeedX{};
    float m_SpeedY{};
    float m_Radius{};
};