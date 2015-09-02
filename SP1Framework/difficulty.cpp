#include <iostream>
#include "UI.h"
#include "game.h"
#include "Framework\console.h"

int difficulty [5][4] = 
{{1, 1, 1, 0}, // for blind
{5, 4, 3, 0}, // for range
{180, 150, 120, 180}, // for starting time limit
{150, 120, 90, 150}, // for adding to time limit for clearing stages
{1, 1, 2, 1}}; // for trap damage

void startGame(player&user, int &range, bool &blind)
{
	user.timelimit = difficulty [2][user.difficulty];
	blind = difficulty [0][user.difficulty];
	range = difficulty [1][user.difficulty];
}

void addTime(player&user)
{
	user.timelimit += difficulty [3][user.difficulty];
}

void trapdmg(player&user)
{
	user.health -= difficulty [4][user.difficulty];
}

