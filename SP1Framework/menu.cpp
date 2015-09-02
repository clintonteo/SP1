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
int hPointer = 0;
int &helpPointer = hPointer;
const int normal = 0;
const int hard = 1;
const int insane = 2;
const int ez = 3;
double stopmenu = 0;

void mainMenu(Console &console, player&user)
{
	int i = 0;
	std::fstream frame1 ("frame1.txt");
	string sframe1;
	if (frame1.is_open())
	{
		if (g_dElapsedTime > 1 && g_dElapsedTime < 2)
		{
			while (getline(frame1,sframe1))
			{
				console.writeToBuffer(10, i, sframe1, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
		}
		frame1.close();
	}
	std::fstream frame2 ("frame2.txt");
	string sframe2;
	if (frame2.is_open())
	{
		if (g_dElapsedTime > 2 && g_dElapsedTime < 3)
		{	
			while (getline(frame2,sframe2))
			{
				console.writeToBuffer(10, i, sframe2, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
		}
		frame2.close();
	}
	std::fstream frame3 ("frame3.txt");
	string sframe3;
	if (frame3.is_open())
	{
		if (g_dElapsedTime > 3 && g_dElapsedTime < 4)
		{
			while (getline(frame3,sframe3))
			{
				console.writeToBuffer(10, i, sframe3, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
		}
		frame3.close();
	}
	std::fstream frame4 ("frame4.txt");
	string sframe4;
	if (frame4.is_open())
	{
		if (g_dElapsedTime > 4 && g_dElapsedTime < 5)
		{
			while (getline(frame4,sframe4))
			{
				console.writeToBuffer(10, i, sframe4, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
		}
		frame4.close();
	}
	std::fstream frame5 ("frame5.txt");
	string sframe5;
	if (frame5.is_open())
	{
		if (g_dElapsedTime > 5 && g_dElapsedTime < 6)
		{
			while (getline(frame5,sframe5))
			{
			console.writeToBuffer(10, i, sframe5, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
			frame5.close();
		}
	}
	std::fstream frame6 ("frame6.txt");
	string sframe6;
	if (frame6.is_open())
	{
		if (g_dElapsedTime > 6 && g_dElapsedTime < 7)
		{
			while (getline(frame6,sframe6))
			{
				console.writeToBuffer(10, i, sframe6, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
			frame6.close();
		}
	}
	std::fstream frame7 ("frame7.txt");
	string sframe7;
	if (frame7.is_open())
	{
		if (g_dElapsedTime > 7 && g_dElapsedTime < 8)
		{
			while (getline(frame7,sframe7))
			{
				console.writeToBuffer(10, i, sframe7, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
		}
		frame7.close();
	}
	std::fstream frame8 ("frame8.txt");
	string sframe8;
	if (frame8.is_open())
	{
		if (g_dElapsedTime > 8 && g_dElapsedTime < 9)
		{
			while (getline(frame8,sframe8))
			{
				console.writeToBuffer(10, i, sframe8, 0xfc);
				++i;
				if (i == 9)
				{
					i = 0;
				}
			}
			frame8.close();
		}
	}
	std::fstream title ("splash.txt");
    string line;
    if (title.is_open())
    {
		if (g_dElapsedTime > 9)
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
	}

	if(g_dElapsedTime < 9)
	{
		console.writeToBuffer(29, 15, "Press <SPACE> to skip", 0xf0);
		if(g_abKeyPressed[K_SPACE])
		{
			g_dElapsedTime = 9;
		}
	}

	string Menu[5] = {"Play", "Difficulty", "Instructions", "Highscore", "Exit"};

	if (g_dElapsedTime > 9)
	{
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
		if (g_abKeyPressed[K_UP] && g_dElapsedTime > stopmenu)
		{
			stopmenu = g_dElapsedTime + .2;
			menuPointer -= 1;
			if (menuPointer == -1)
			{
				menuPointer = 4;
			}
		}
		else if (g_abKeyPressed[K_DOWN] && g_dElapsedTime > stopmenu)
		{
			stopmenu = g_dElapsedTime + .2;
			menuPointer += 1;
			if (menuPointer == 5)
			{
				menuPointer = 0;
			}
		}
		else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stopmenu)
		{
			stopmenu = g_dElapsedTime + .2;
			switch (menuPointer)
			{
				case 0:
					{
						g_eGameState = S_SPLASHSCREEN;
						g_dElapsedTime = 0;
						user.lives = 3;
						user.health = 5;
						stopmenu = 0;
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

	if (g_abKeyPressed[K_UP] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
		optionPointer -= 1;
		if (optionPointer == -1)
		{
			optionPointer = 3;
		}
	}
	else if (g_abKeyPressed[K_DOWN] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
		optionPointer += 1;
		if (optionPointer == 4)
		{
			optionPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
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
	if(g_abKeyPressed[K_ENTER] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + 0.2;
		g_eGameState = S_MENU;
	}
}

void exit()
{
	g_bQuitGame = true;
}

void help(Console &console, player&user)
{
	string Help[2] = {"Tutorial", "Back"};

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
	//console.writeToBuffer(25, 20, "Press Enter to return to main menu.", 0xf0);

	for (int i = 0; i < 2; ++i)
	{
		if (i == hPointer)
		{
			console.writeToBuffer(30,20+i, Help[i], 10);
		}
		else
		{
			console.writeToBuffer(30, 20+i, Help[i], 0xf9);
		}
	}

	if (g_abKeyPressed[K_UP] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
		helpPointer -= 1;
		if (helpPointer == -1)
		{
			helpPointer = 1;
		}
	}
	else if (g_abKeyPressed[K_DOWN] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
		helpPointer += 1;
		if (helpPointer == 2)
		{
			helpPointer = 0;
		}
	}
	else if (g_abKeyPressed[K_ENTER] && g_dElapsedTime > stopmenu)
	{
		stopmenu = g_dElapsedTime + .2;
		switch (helpPointer)
		{
			case 0:
				{
					g_eGameState = S_TUTORIAL;
					user.lives = 5;
					user.health = 5;
					g_dElapsedTime = 0;
					stopmenu = 0;
				}
				break;
			case 1:
				{
					g_eGameState = S_MENU;
				}
				break;
		}
	}
}