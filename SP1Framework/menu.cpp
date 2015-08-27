#include "game.h"
#include "Framework\console.h"

extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern double g_dElapsedTime;

using std::string;

int pointer = 0;
int &menuPointer = pointer;
int opPointer = 0;
int &optionPointer = opPointer;
double stop;
const int normal = 0;
const int hard = 1;
const int insane = 2;

void mainMenu(Console &console)
{
	string Menu[8] = {"start game","", "difficulty","", "help","", "exit",""};

	console.writeToBuffer(30, 5, "Tower Of PuzzMaz", 0xf7);

	for (int i = 0; i < 8; ++i)
	{
		if (i == pointer)
		{
			console.writeToBuffer(30,10+i, Menu[i], 0xfb);
		}
		else
		{
			console.writeToBuffer(30, 10+i, Menu[i], 0xf7);
		}
	}
	if (g_abKeyPressed[K_UP])
	{
		stop = g_dElapsedTime + 0.2;
		menuPointer -= 1;
		if (menuPointer == -1)
		{
			menuPointer = 7;
		}
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		stop = g_dElapsedTime + 0.2;
		menuPointer += 1;
		if (menuPointer == 8)
		{
			menuPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + 0.2;
		switch (menuPointer)
		{
			case 0:
				{
					g_eGameState = S_SPLASHSCREEN;
				}
				break;
			case 1:
				break;
			case 2:
				{
					g_eGameState = S_OPTIONS;
				}
				break;
			case 3:
				break;
			case 4:
				{
					g_eGameState = S_HELP;
				}
			case 5:
				break;
			case 6:
				{
					exit();
				}
			case 7:
				break;
		}
	}
}

void options(Console &console, player&user)
{
	string Options[8] = {"normal","", "hard","", "insane","", "back",""};

	console.writeToBuffer(30, 5, "Difficulty", 0xf7);

	for (int i = 0; i < 8; ++i)
	{
		if (i == opPointer)
		{
			console.writeToBuffer(30,10+i, Options[i], 0xfb);
		}
		else
		{
			console.writeToBuffer(30, 10+i, Options[i], 0xf7);
		}
	}

	if (g_abKeyPressed[K_UP])
	{
		stop = g_dElapsedTime + 0.2;
		optionPointer -= 1;
		if (optionPointer == -1)
		{
			optionPointer = 7;
		}
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		stop = g_dElapsedTime + 0.2;
		optionPointer += 1;
		if (optionPointer == 8)
		{
			optionPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + 0.2;
		switch (optionPointer)
		{
			case 0:
				{
					user.difficulty = normal;
					g_eGameState = S_MENU;
				}
				break;
			case 1:
				break;
			case 2:
				{
					user.difficulty = hard;
					g_eGameState = S_MENU;
				}
				break;
			case 3:
				break;
			case 4:
				{
					user.difficulty = insane;
					g_eGameState = S_MENU;
				}
				break;
			case 5:
				break;
			case 6:
				{
					g_eGameState = S_MENU;
				}
			case 7:
				break;
		}
	}
}

void exit()
{
	g_bQuitGame = true;
}

void help(Console &console)
{
	console.writeToBuffer(30, 10, "test", 0xf7);
}