// Game.h

#ifndef GAME_H
#define GAME_H

#include "DxLib.h"

void UpdatePositions(int& player1Y, int& player2Y, int& puckX, int& puckY, int& puckSpeedX, int& puckSpeedY, int puckRadius, int paddleRadius);
void DrawGame(int player1X, int player1Y, int player2X, int player2Y, int puckX, int puckY, int puckRadius, int paddleRadius);

#endif
