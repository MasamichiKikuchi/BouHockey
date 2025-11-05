// Game.cpp

#include "DxLib.h"
#include "Game.h"

void UpdatePositions(int& player1Y, int& player2Y, int& puckX, int& puckY, int& puckSpeedX, int& puckSpeedY, int puckRadius, int paddleRadius) {
    if (CheckHitKey(KEY_INPUT_W)) player1Y -= 5;
    if (CheckHitKey(KEY_INPUT_S)) player1Y += 5;
    if (CheckHitKey(KEY_INPUT_UP)) player2Y -= 5;
    if (CheckHitKey(KEY_INPUT_DOWN)) player2Y += 5;

    if (player1Y < paddleRadius) player1Y = paddleRadius;
    if (player1Y > 600 - paddleRadius) player1Y = 600 - paddleRadius;
    if (player2Y < paddleRadius) player2Y = paddleRadius;
    if (player2Y > 600 - paddleRadius) player2Y = 600 - paddleRadius;

    puckX += puckSpeedX;
    puckY += puckSpeedY;

    if (puckY < puckRadius || puckY > 600 - puckRadius) puckSpeedY = -puckSpeedY;
    if (puckX < puckRadius || puckX > 800 - puckRadius) puckSpeedX = -puckSpeedX;

    int dx1 = puckX - 50;
    int dy1 = puckY - player1Y;
    if (dx1 * dx1 + dy1 * dy1 <= (puckRadius + paddleRadius) * (puckRadius + paddleRadius)) {
        puckSpeedX = -puckSpeedX;
    }

    int dx2 = puckX - 750;
    int dy2 = puckY - player2Y;
    if (dx2 * dx2 + dy2 * dy2 <= (puckRadius + paddleRadius) * (puckRadius + paddleRadius)) {
        puckSpeedX = -puckSpeedX;
    }
}

void DrawGame(int player1X, int player1Y, int player2X, int player2Y, int puckX, int puckY, int puckRadius, int paddleRadius) {
    DrawCircle(puckX, puckY, puckRadius, GetColor(255, 255, 255), TRUE);
    DrawCircle(player1X, player1Y, paddleRadius, GetColor(255, 0, 0), TRUE);
    DrawCircle(player2X, player2Y, paddleRadius, GetColor(0, 0, 255), TRUE);
}
