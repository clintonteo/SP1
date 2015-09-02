#include <iostream>
#include "UI.h"
#include "game.h"
#include "Framework\console.h"

//diffculty
const int normal = 0;
const int hard = 1;
const int insane = 2;
const int ez = 3;


void startGame(player&user, int &range, bool &blind)
{
	if(user.difficulty == normal)
	{
		user.timelimit = 180;
		blind = 1;
		range = 5;
	}
	if(user.difficulty == hard)
	{
		user.timelimit = 150;
		blind = 1;
		range = 4;
	}
	if(user.difficulty == insane)
	{
		user.timelimit = 120;
		blind = 1;
		range = 3;
	}
	if(user.difficulty == ez)
	{
		user.timelimit = 180;
		blind = 0;
	}
}

void addTime(player&user)
{
	if(user.difficulty == normal)
	{
		user.timelimit += 150;
	}
	else if(user.difficulty == hard)
	{
		user.timelimit += 120;
	}
	else if(user.difficulty == insane)
	{
		user.timelimit += 90;
	}
	else if(user.difficulty == ez)
	{
		user.timelimit += 150;
	}
}