#include <iostream>
#include "UI.h"
#include "game.h"
#include "AI.h"
#include "Framework\console.h"

double difficulty [6][4] = 
{{1, 1, 1, 0}, // for blind
{5, 4, 3, 0}, // for vision range if blind
{180, 150, 120, 180}, // for starting time limit
{150, 120, 90, 150}, // for adding to time limit for clearing stages
{1, 1, 2, 1}, // for trap damage
{0.2, 0.18, 0.18, 0.2}}; // for mob speed

void startGame(player&user, int &range, bool &blind)// start game with stats that are affected by difficulty
{
	user.timelimit = difficulty [2][user.difficulty];
	blind = difficulty [0][user.difficulty];
	range = difficulty [1][user.difficulty];
}

void addTime(player&user) // adds extra time for player when they clear a stage
{
	user.timelimit += difficulty [3][user.difficulty];
}

void trapdmg(player&user)// modify trap damage values based on difficulty
{
	user.health -= difficulty [4][user.difficulty];
}

double monSpd(player&user, mobData&mobD)// modify mob speed based on difficulty
{
	return difficulty[5][user.difficulty];
}