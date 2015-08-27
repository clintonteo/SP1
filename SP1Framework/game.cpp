// This is the main file for the game logic and function
//
//
#include "item.h"
#include "game.h"
#include "Framework\console.h"
#include "map.h"
#include "UI.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "AI.h"
using std::cout;
using std::endl;
using std::cin;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

COORD consoleSize;
COORD blocks;
COORD mob;
COORD lastknown;
PMAP MapCollision;
// stage clear checker
bool init1 = 0;
bool init2 = 0;
bool extime2 = 0;
bool init3 = 0;
bool extime3 = 0;
bool init4 = 0;
bool extime4 = 0;

int range;
bool blind = 0;
bool lostlives = 0;

double Endtime;
double boostcd = 0;
double invisExp = 0;

//diffculty
const int normal = 0;
const int hard = 1;
const int insane = 2;
const int ez = 3;

//Last known Coordinates
int lastX = 0;
int lastY = 0;

player user;
int count = 0;
string name;

//Damage Trackers
bool lavadamage = 0;
bool trapdamage = 0;

//Mob Storage [Vector]
std::vector<mobData> allMobs;

// Game specific variables here
SGameChar g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 28, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_MENU;

    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 25, L"Consolas");
	//user.difficulty = normal;
	//if(user.difficulty == normal)
	//{
	//	range = 6;
	//	user.timelimit = 10;
	//}
	//if(user.difficulty == hard)
	//{
	//	range = 5;
	//	user.timelimit = 150;
	//}
	//if(user.difficulty == insane)
	//{
	//	range = 4;
	//	user.timelimit = 120;
	//}
    mob.X = 1;
	mob.Y = 2;
    if (lostlives == 0)
    {
        user.lives = 3;
    }
    user.health = 5;
    user.points = 0;
    user.select = 0;
	user.boost = 0;
    user.bomb = 0;
	user.invistaken = 0;
	user.invis = 0;
	user.invispot = 0;
	user.MedsTaken = 0;
    user.stage1 = 0;
    user.stage2 = 0;
    user.stage3 = 0;
    user.stage4 = 0;
	lastknown.X = 0;
	lastknown.Y = 0;
    std::ofstream log;
    log.open("log.txt", std::fstream::trunc);
    log.close();
	//user.timelimit = 99999;
}
//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    g_abKeyPressed[K_SELECT] = isKeyPressed(0x5A); // Z key // Select items
    g_abKeyPressed[K_USE] = isKeyPressed(VK_SPACE); // Spacebar // Use items
	g_abKeyPressed[K_RESET] = isKeyPressed(0x52); // R key // Resets the game
    g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN); // Enter Key
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
		case S_MENU: mainMenu(g_Console, user);
			break;
		case S_OPTIONS: options(g_Console, user);
			break;
		case S_HELP: help(g_Console);
			break;
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        
        case S_GAME1:
			if(init1 == 0)
			{
				g_sChar.m_cLocation.X = 3;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				allMobs.clear();
				//spawnmob(allMobs);
				init1 = 1;
			}
			
			if(user.difficulty == normal)
			{
				range = 6;
				user.timelimit = 180;
				blind = 1;
			}
			if(user.difficulty == hard)
			{
				range = 5;
				user.timelimit = 150;
				blind = 1;
			}
			if(user.difficulty == insane)
			{
				range = 4;
				user.timelimit = 120;
				blind = 1;
			}
			if(user.difficulty == ez)
			{
				user.timelimit = 180;
			}
			user.start = 1;
			gameplay(); // gameplay logic when we are in the game
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
			{
				Endtime = g_dElapsedTime;
                user.stage1 = 1;
				g_eGameState = S_SPLASHSCREEN2;
			}
            break;
		
        case S_SPLASHSCREEN2: splashStage2Wait();
			break;
		
        case S_GAME2:
			if(init2 == 0)
			{
				if(extime2 == 0)
				{
					if(user.difficulty == normal)
					{
						user.timelimit += 150;
						blind = 1;
					}
					else if(user.difficulty == hard)
					{
						user.timelimit += 120;
						blind = 1;
					}
					else if(user.difficulty == insane)
					{
						user.timelimit += 90;
						blind = 1;
					}
					else if(user.difficulty == ez)
					{
						user.timelimit += 150;
					}
					extime2 = 1;
				}
				g_sChar.m_cLocation.X = 46;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				init2 = 1;
			}
				gameplay();
				if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
				{
					Endtime = g_dElapsedTime;
                    user.stage2 = 1;
					g_eGameState = S_SPLASHSCREEN3;
				}
				break;

			case S_SPLASHSCREEN3: splashStage3Wait();
				break;

			case S_GAME3:
			if(init3 == 0)
			{
				if(extime3 == 0)
				{
					if(user.difficulty == normal)
					{
						user.timelimit += 150;
						blind = 1;
					}
					else if(user.difficulty == hard)
					{
						user.timelimit += 120;
						blind = 1;
					}
					else if(user.difficulty == insane)
					{
						user.timelimit += 90;
						blind = 1;
					}
					else if(user.difficulty == ez)
					{
						user.timelimit += 150;
					}
					extime3 = 1;
				}
				g_sChar.m_cLocation.X = 3;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				init3 = 1;
			}
			gameplay();
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
				{
					Endtime = g_dElapsedTime;
					g_eGameState = S_SPLASHSCREEN4;
				}
			break;
        
			case S_SPLASHSCREEN4: splashStage4Wait();
				break;

			case S_GAME4:
			if(init4 == 0)
			{
				if(extime4 == 0)
				{
					if(user.difficulty == normal)
					{
						user.timelimit += 150;
						blind = 1;
					}
					else if(user.difficulty == hard)
					{
						user.timelimit += 120;
						blind = 1;
					}
					else if(user.difficulty == insane)
					{
						user.timelimit += 90;
						blind = 1;
					}
					if(user.difficulty == ez)
					{
						user.timelimit += 150;
					}
					extime4 = 1;
				}
				g_sChar.m_cLocation.X = 45;
				g_sChar.m_cLocation.Y = 18;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				init4 = 1;
			}
			gameplay();
            if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
			{
				Endtime = g_dElapsedTime;
                user.stage4 = 1;
				g_eGameState = S_NAME;
			}
			break;

        case S_NAME:
            if (g_abKeyPressed[K_ENTER])
            {
                g_eGameState = S_GAMEOVER;
            }
            break;

        case S_GAMEOVER:
            if (g_abKeyPressed[K_ENTER])
            {
                g_bQuitGame = true;
            }
            break;
    }
}

void reset()
{
	user.select = 0;
	for(int i=0; i < 6; ++i)
	{
		user.inventory[i] = 'f';
	}
	user.inventoryitems.clear();
    count = 0;
	user.boost = 0;
	user.switch1 = 0;
	user.switch2 = 0;
	user.switch3 = 0;
	user.bomb = 0;
	user.Cexplode = 0;
	user.invispot = 0;
	user.invis = 0;
	user.invistaken = 0;
	user.TTaken = 0;
	user.MedsTaken = 0;
	allMobs.clear();
	spawnblock(blocks);
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
		case S_HELP: help(g_Console);
			break;
		case S_OPTIONS: options(g_Console, user);
			break;
		case S_MENU: mainMenu(g_Console, user);
			break;
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME1: 
			renderStage1();
			renderGame();
			g_Console.writeToBuffer(51, 0, "STAGE 1", 10);
            break;
		case S_SPLASHSCREEN2: renderSplashStage2();
			break;
		case S_GAME2:
			renderStage2();
			renderGame();
			g_Console.writeToBuffer(51, 0, "STAGE 2", 10);
			break;
		case S_SPLASHSCREEN3: renderSplashStage3();
			break;
		case S_GAME3:
			renderStage3();
			renderGame();
			g_Console.writeToBuffer(51, 0, "STAGE 3", 10);
			break;
		case S_SPLASHSCREEN4: renderSplashStage4();
			break;
		case S_GAME4:
			renderStage4();
			renderGame();
			g_Console.writeToBuffer(51, 0, "STAGE 4", 10);
			break;

        case S_NAME:
            renderEnterName();
            break;

        case S_GAMEOVER:
            renderGameover();
			break;
    }
    //renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0)// wait for 3 seconds to switch to game mode, else do nothing
	{
		g_eGameState = S_GAME1;
		g_dElapsedTime -= 3;
	}
}
void splashStage2Wait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime >= Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
    {
		g_eGameState = S_GAME2;
		g_dElapsedTime -= 3;
	}
}
void splashStage3Wait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime >= Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
	{
        g_eGameState = S_GAME3;
		g_dElapsedTime -= 3;
	}
}
void splashStage4Wait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime >= Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
	{
        g_eGameState = S_GAME4;
		g_dElapsedTime -= 3;
	}
}
void splashGameoverWait()
{
    if (g_dElapsedTime > Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_SPLASHSCREEN;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
   	if (g_abKeyPressed[K_UP])
    	{
		if(MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'X')
			{
				if(user.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'Y')
			{
				if(user.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'Z')
			{
				if(user.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'C')
			{
				if(user.Cexplode == 1)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else 
			{ 
				        Beep(1440, 30);
				g_sChar.m_cLocation.Y--;
			}
		}		
    }
    if (g_abKeyPressed[K_LEFT])
    {
        Beep(1440, 30);
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'X')
			{
				if(user.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'Y')
			{
				if(user.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'Z')
			{
				if(user.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'C')
			{
				if(user.Cexplode == 1)
				{
					g_sChar.m_cLocation.X--;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.X--;
			}
		}
    }
	if (g_abKeyPressed[K_DOWN])
    {
		if(MapCollision->data[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'X')
			{
				if(user.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'Y')
			{
				if(user.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'Z')
			{
				if(user.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'C')
			{
				if(user.Cexplode == 1)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.Y++;
			}
		}

	}
    if (g_abKeyPressed[K_RIGHT])
    {
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'X')
			{
				if(user.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'Y')
			{
				if(user.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'Z')
			{
				if(user.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'C')
			{
				if(user.Cexplode == 1)
				{
					g_sChar.m_cLocation.X++;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.X++;
			}
		}
    }

    // POINTS
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'T' && user.TTaken == 0)
    {
        user.points += 1;
		user.TTaken = 1; 
    }

    // SELECTON
    if ((g_abKeyPressed[K_SELECT])/* && (user.inventory[0] == 't') */&& (user.select < user.inventoryitems.size()))
    {
        user.select += 1;
        if (user.select >= user.inventoryitems.size()/*+1*/)
        {
            user.select = 0;
        }
    }

    // INVENTORY
    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I') && (user.boost == 0)) // Boost
    {
        user.inventory[count] = 't';
        user.inventoryitems.push_back("Boost");
        ++count;
		//user.boost = 1;
    }

    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'J') && (user.bomb == 0)) // Bomb
    {
        user.inventory[count] = 't';
        user.inventoryitems.push_back("Bomb");
        ++count;
		//user.bomb = 1;
    }
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'L' && user.invispot == 0 && user.invistaken == 0) //Invis
	{
		user.inventory[count] = 't';
        user.inventoryitems.push_back("Invis Pot");
        ++count;
	}


    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;

    // quits if player lives at 0
    if (user.health <= 0)
    {
        //g_bQuitGame = true;
        //g_eGameState = S_SPLASHSCREEN;
        --user.lives;
        user.health = 5;
        if (g_eGameState == S_GAME1)
        {
            init1 = 0;
        }
        else if (g_eGameState == S_GAME2)
        {
            init2 = 0;
        }

		else if (g_eGameState == S_GAME3)
        {
            init3 = 0;
        }
		else if (g_eGameState == S_GAME4)
        {
            init4 = 0;
        }
        lostlives = 1;
        writeLog("You lost a live!", g_dElapsedTime);
	}
	//RESET
	if(g_abKeyPressed[K_RESET])
	{
		//g_eGameState = S_SPLASHSCREEN2;
        g_eGameState = static_cast<EGAMESTATES>(g_eGameState + 1);
	}

    //POINTS
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'T' && user.TTaken == 0)
    {
        user.points += 1;
		user.TTaken = 1; 
    }

    //Use Items
    //Boost
    if (user.boost == 1 && /*user.inventory[user.select] == 't'*/ user.inventoryitems[user.select] == "Boost")
	{
		if(g_abKeyPressed[K_UP] && g_abKeyPressed[K_USE])
		{
			item1up(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd);
		}
		else if(g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_USE])
		{
			item1left(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd);
		}
		else if(g_abKeyPressed[K_DOWN] && g_abKeyPressed[K_USE])
		{
			item1down(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd);
		}
		else if(g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_USE])
		{
			item1right(MapCollision, g_sChar.m_cLocation,user, g_dElapsedTime, g_Console, boostcd);
		}
	}
	//Bomb
    if(user.bomb == 1 && user.inventoryitems[user.select] == "Bomb"/*user.inventory[user.select] == 't'*/)
	{
		int amt = user.bomb;
		if(MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'C')
		{
			if(g_abKeyPressed[K_UP] && g_abKeyPressed[K_USE])
			{
				item2(user);
				user.inventory[user.select] = 'f';
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'C')
		{
			if(g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_USE])
			{
				item2(user);
				user.inventory[user.select] = 'f';
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == 'C')
		{
			if(g_abKeyPressed[K_DOWN] && g_abKeyPressed[K_USE])
			{
				item2(user);
				user.inventory[user.select] = 'f';
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'C')
		{
			if(g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_USE])
			{
				item2(user);
				user.inventory[user.select] = 'f';
			}
		}
	}
	
	//Invis
	if(user.invispot == 1 && user.inventoryitems[user.select] == "Invis Pot")
	{
		if (g_abKeyPressed[K_USE])
		{
			item3(user,g_sChar, g_dElapsedTime, invisExp);
			user.inventory[user.select] = 'f';
			writeLog("You are invis!", g_dElapsedTime);
		}
	}
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0xff);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Tower Of Maz STAGE 1", 0xfc);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Hint: You can use boost over lava!!", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0xf9);
}

void renderSplashStage2()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2 - 9;
    g_Console.writeToBuffer(c, "STAGE 2", 0xf3);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2 - 20;
    g_Console.writeToBuffer(c, "Hint: you can move diagonally skrub", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0xf9);
}

void renderSplashStage3()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2 - 9;
    g_Console.writeToBuffer(c, "STAGE 3", 0xf3);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2 - 20;
    g_Console.writeToBuffer(c, "Hint: Arunning pls", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0xf9);
}

void renderSplashStage4()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2 - 9;
    g_Console.writeToBuffer(c, "STAGE 4", 0xf3);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2 - 20;
    g_Console.writeToBuffer(c, "This will make you ragequit, a helpful hint is below.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Hint: Press 'Esc' to quit", 0xf9);
}

void renderGameover()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2 - 9;
    g_Console.writeToBuffer(c, "GAME OVER", 0xf3);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2 - 20;
    g_Console.writeToBuffer(c, "TRY AGAIN NEXT TIME. COME BACK.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Your points are: ", 0xf9);
    c.X += 16;
    finalscore( g_Console , user , c , Endtime); //Final Score
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    
    /*c.X = 30;
    c.Y = 13;
    g_Console.writeToBuffer(c, "Enter your name: ", 0xf9);*/
    cin >> name;

    highscoreWrite( user , g_Console , c , name);
    highscoreRead ( user , g_Console , c );

    //highscore( highscorePoints , highscoreNames , user );
}

void renderEnterName()
{
    COORD c = g_Console.getConsoleSize();
    c.X = 30;
    c.Y = 13;
    g_Console.writeToBuffer(c, "Enter your name: ", 0xf9);
    /*if (g_abKeyPressed[K_SELECT])
    {
        name += "K";
    }*/
}

void renderStage1()
{
	MapCollision = load_map("stage1.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage1.txt");
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range);
	}
}
void renderStage2()
{
	MapCollision = load_map("stage2.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage2.txt");
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console, blind);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range);
	}
}
void renderStage3()
{
	MapCollision = load_map("stage3.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage3.txt");
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range);
	}
}
void renderStage4()
{
	MapCollision = load_map("stage4.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage4.txt");
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console, blind);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range);
	}
}
void renderGame()
{
    background ( g_Console );
    renderCharacter(user);  // renders the character into the buffer

    // Write Log
	//mobmove(g_sChar.m_cLocation,mob,g_dElapsedTime,g_Console, MapCollision);
    // Creating Map
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '1' && user.switch1 != 1){
		user.switch1 = 1;
        writeLog("X Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '2'  && user.switch2 != 1)
	{
		user.switch2 = 1;
        writeLog("Y Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '3'  && user.switch3 != 1)
	{
		user.switch3 = 1;
        writeLog("Z Switch Activated!", g_dElapsedTime);
	}

	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I' && user.boost == 0)
	{
		user.boost = 1;
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'J' && user.bombtaken == 0 && user.bomb == 0)
	{
		user.bomb = 1;
		user.bombtaken = 1;
        writeLog("You got a bomb!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'L' && user.invispot == 0 && user.invistaken == 0)
	{
		user.invispot = 1;
		user.invistaken = 1;
        writeLog("You got an invis potion!", g_dElapsedTime);
	}
	// medpack
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' && user.MedsTaken == 0 && user.health != 5)
	{
		if(user.difficulty == normal || user.difficulty == hard || user.difficulty == ez)
		{
			if (user.health < 4)
			{
				user.health += 2;
				user.MedsTaken = 1;
			}
			else if (user.health == 4)
			{
				user.health += 1;
				user.MedsTaken = 1;
			}
		}
		else if(user.difficulty == insane)
		{
			if (user.health < 3)
			{
				user.health += 3;
				user.MedsTaken = 1;
			}
			else if (user.lives == 3)
			{
				user.health += 2;
				user.MedsTaken = 1;
			}
			else if (user.lives == 4)
			{
				user.health += 1;
				user.MedsTaken = 1;
			}
		}
        writeLog("You have been healed!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'D' && user.health > 0 && trapdamage == 0)
	{
        //writeLog("You have been hurt!", g_dElapsedTime);
		if(user.difficulty == hard || user.difficulty == normal || user.difficulty == ez)
		{
				user.health--;
				writeLog("You have been hurt!", g_dElapsedTime);
				trapdamage = 1;
		}
		else if(user.difficulty == insane)
		{
				user.health -= 2;
				writeLog("You have been hurt!", g_dElapsedTime);
				trapdamage = 1;
		}
	}else if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] != 'D' )
	{
		trapdamage = 0;
	}
	// pitfall
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'P' && user.health > 0)
	{
		if (init4 == 1)
		{
			init4 = 0;
			init3 = 0;
		}
		else if(init3 == 1)
		{
			init3 = 0;
			init2 = 0;
		}
		else if(init2 == 1)
		{
			init2 = 0;
			init1 = 0;
		}
		g_eGameState = static_cast<EGAMESTATES>(g_eGameState - 2);
	}
    if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '=' && user.health > 0 && lavadamage == 0)
	{
		if(g_sChar.m_cLocation.X == blocks.X && g_sChar.m_cLocation.Y == blocks.Y)
		{
			lavadamage = 1;
		}
		else
		{
			user.health -= user.health;
			lavadamage = 1;
		}
	}
    else
	{
		lavadamage = 0;
	}
	// time limit
	if (g_dElapsedTime >= user.timelimit && user.start == 1)
	{
		user.lives -= user.lives;
	}
	if (user.lives <= 0)
	{
		colour(BACKGROUND_RED);
		//g_Console.writeToBuffer(51, 13, "YOU DIED", 0xf1);
        writeLog("You died!", g_dElapsedTime);
        Endtime = g_dElapsedTime;
        g_eGameState = S_NAME;
		Beep(2000, 1000);
	} 

    //Check for cooldown
    if (g_dElapsedTime >= boostcd && user.boost == 1 && boostcd != -1)
    {
        writeLog("Boost is ready!", g_dElapsedTime);
        boostcd = -1;
    }
	if(g_dElapsedTime >= invisExp && user.invis == 1)
	{
		user.invis = 0;
	}
   
    //UI functions
    background ( g_Console );
    divider( g_Console) ;
    timer( g_dElapsedTime , g_Console , user);
    lives( user , g_Console);
    renderInventory ( user , g_Console , boostcd , g_dElapsedTime);
    point( user , g_Console);
    selector ( user , g_Console);
    readLog ( g_Console );
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter(player&user)
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive && user.invis == 1)
    {
        charColor = 0;
    }
	else if (g_sChar.m_bActive)
	{
		charColor = 0xfC;
	}
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = 72;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 59;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str(), 10);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}