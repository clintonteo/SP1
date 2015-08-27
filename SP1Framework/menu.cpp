#include "game.h"
#include "Framework\console.h"

extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;

using std::string;

int pointer = 0;
int &menuPointer = pointer;
int opPointer = 0;
int &optionPointer = opPointer;

void mainMenu(Console &console)
{
	string Menu[8] = {"start game","", "options","", "help","", "exit",""};

	console.writeToBuffer(30, 5, "main menu", 0xf7);

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
		menuPointer -= 1;
		if (menuPointer == -1)
		{
			menuPointer = 7;
		}
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		menuPointer += 1;
		if (menuPointer == 8)
		{
			menuPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER])
	{
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

void options(Console &console)
{
	string Options[8] = {"normal","", "hard","", "insane","", "back",""};

	console.writeToBuffer(30, 5, "options", 0xf7);

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
		optionPointer -= 1;
		if (optionPointer == -1)
		{
			optionPointer = 7;
		}
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		optionPointer += 1;
		if (optionPointer == 8)
		{
			optionPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER])
	{
		switch (optionPointer)
		{
			case 0:
				{
				
				}
				break;
			case 1:
				break;
			case 2:
				{
					
				}
				break;
			case 3:
				break;
			case 4:
				{

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