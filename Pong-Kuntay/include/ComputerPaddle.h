#pragma once
#include "Paddle.h"

class ComputerPaddle : public Paddle
{
public:

    ComputerPaddle(float posX, float posY, float width, float height, int speed);

    void Update(int ballPosY);

};