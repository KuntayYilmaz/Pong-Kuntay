#pragma once
#include "raylib.h"

class Paddle
{
public:

    Paddle(float posX, float posY, float width, float height, int speed);

    void Draw() const;

    void Update();

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