#pragma once
#include "Play.h"
#include "ChessDisplay.h"

void handleGameEnd(Game& game, ChessDisplay& display);
bool processInput(const String& input, Game& game, ChessDisplay& display, bool& gameRunning);
void runGameLoop(Game& game, ChessDisplay& display);
