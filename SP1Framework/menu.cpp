#include "game.h"
#include "Framework\console.h"
#include <fstream>
#include <iostream>

extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern double g_dElapsedTime;

using std::string;

int pointer = 0;
int &menuPointer = pointer;
int opPointer = 0;
int &optionPointer = opPointer;
const int normal = 0;
const int hard = 1;
const int insane = 2;
const int ez = 3;
double stop = 0;

void mainMenu(Console &console, player&user)
{
	std::fstream title ("splash.txt");
    string line;
	int i = 0;
    if (title.is_open())
    {
        while (getline (title,line))
        {
            console.writeToBuffer(10, i, line ,0xfc);
            ++i;
            if(i == 9)
            {
                i = 0;
            }
        }
        title.close();
    }

	string Menu[5] = {"Play", "Difficulty", "Instructions", "Highscore", "Exit"};

	//console.writeToBuffer(25, 5, "Tower Of PuzzMaz", 0xfc);
	if(user.difficulty == 0)
	{
		console.writeToBuffer(25, 10, "Selected difficulty is Normal.", 0xf0);
	}
	else if(user.difficulty == 1)
	{
		console.writeToBuffer(25, 10, "Selected difficulty is Hard.", 0xf0);
	}
	else if(user.difficulty == 2)
	{
		console.writeToBuffer(25, 10, "Selected difficulty is INSANITY!!!.", 0xf0);
	}
	else if(user.difficulty == 3)
	{
		console.writeToBuffer(25, 10, "Selected difficulty is Scrub. Noob.", 0xf0);
	}
	console.writeToBuffer(20, 20, "Arrow Keys to navigate, Enter to select", 0xf0);
	for (int i = 0; i < 5; ++i)
	{
		if (i == pointer)
		{
			console.writeToBuffer(30,13+i, Menu[i], 10);
		}
		else
		{
			console.writeToBuffer(30, 13+i, Menu[i], 0xf9);
		}
	}
	if (g_abKeyPressed[K_UP] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		menuPointer -= 1;
		if (menuPointer == -1)
		{
			menuPointer = 4;
		}
	}
	else if (g_abKeyPressed[K_DOWN] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		menuPointer += 1;
		if (menuPointer == 5)
		{
			menuPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		switch (menuPointer)
		{
			case 0:
				{
					g_eGameState = S_SPLASHSCREEN;
					g_dElapsedTime = 0;
				}
				break;
			case 1:
				{
					g_eGameState = S_OPTIONS;
				}
				break;
			case 2:
				{
					g_eGameState = S_HELP;
				}
				break;
			case 3:
				{
					g_eGameState = S_HIGHSCORE;
				}
				break;
			case 4:
				{
					exit();
				}
				break;
		}
	}
}

void options(Console &console, player&user)
{
	string Options[4] = {"Scrub","Normal", "Hard", "Insane" };

	console.writeToBuffer(30, 5, "Difficulty", 0xfc);
	console.writeToBuffer(15, 18, "The higher the difficulty, the smaller your vision range is ", 0xf0);
	console.writeToBuffer(15, 19, "and the less time is provided to complete the stage.", 0xf0);
	for (int i = 0; i < 4; ++i)
	{
		if (i == opPointer)
		{
			console.writeToBuffer(30,10+i, Options[i], 10);
		}
		else
		{
			console.writeToBuffer(30, 10+i, Options[i], 0xf9);
		}
	}

	if (g_abKeyPressed[K_UP] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		optionPointer -= 1;
		if (optionPointer == -1)
		{
			optionPointer = 3;
		}
	}
	else if (g_abKeyPressed[K_DOWN] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		optionPointer += 1;
		if (optionPointer == 4)
		{
			optionPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + .2;
		switch (optionPointer)
		{
			case 0:
				{
					user.difficulty = ez;
					g_eGameState = S_MENU;
				}
				break;
			case 1:
				{
					user.difficulty = normal;
					g_eGameState = S_MENU;
				}
				break;
			case 2:
				{
					user.difficulty = hard;
					g_eGameState = S_MENU;
				}
				break;
			case 3:
				{
					user.difficulty = insane;
					g_eGameState = S_MENU;
				}
				break;
		}
	}
}

void highscoreMenu(Console& g_Console, player&user)
{
	highscoreBoard (user , g_Console );
	if(g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + 0.2;
		g_eGameState = S_MENU;
	}
}

void exit()
{
	g_bQuitGame = true;
}

void help(Console &console)
{
	console.writeToBuffer(25, 5, "Instructions", 0xfc);
	console.writeToBuffer(25, 7, "Arrow keys to move.", 0xf0);
	console.writeToBuffer(25, 8, "Z to select item.", 0xf0);
	console.writeToBuffer(25, 9, "Space to use item.", 0xf0);
	console.writeToBuffer(25, 10, ": is empty space.", 0xf0);
	console.writeToBuffer(25, 11, "; is a damaging trap.", 0xf0);
	console.writeToBuffer(25, 12, "= is lava.", 0xf0);
	console.writeToBuffer(25, 13, "/ is lever to open XYZ walls.", 0xf0);
	console.writeToBuffer(25, 14, "0 is a pitfall trap.", 0xf0);
	console.writeToBuffer(25, 15, "$ is a treasure.", 0xf0);
	console.writeToBuffer(25, 16, "+ is a health pack, Heal up!.", 0xf0);
	console.writeToBuffer(25, 17, "M is a monster. Avoid him!.", 0xf0);
	console.writeToBuffer(25, 18, "# to escape.", 0xf0);
	console.writeToBuffer(25, 20, "Press Enter to return to main menu.", 0xf0);
	if(g_abKeyPressed[K_ENTER] && g_dElapsedTime > stop)
	{
		stop = g_dElapsedTime + 0.2;
		g_eGameState = S_MENU;
	}
}