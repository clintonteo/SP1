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
#include <vector>
#include "AI.h"
#include "difficulty.h"


double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

double abilitydelay = 0;

COORD consoleSize;
COORD blocks;
COORD mob;
COORD lastknown;
PMAP MapCollision;
// stage clear checker
bool tutorial_init = 0;
bool init1 = 0;
bool extime1 = 0;
bool init2 = 0;
bool extime2 = 0;
bool init3 = 0;
bool extime3 = 0;
bool init4 = 0;
bool extime4 = 0;
bool init_name = 0;

int range;
bool blind = 0;

bool lostlives = 0;

double stopswitch = 0;
double lavastop = 0;
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
mapBool mapUpdate;
int count = 0;

//Damage Trackers
bool lavadamage = 0;
bool trapdamage = 0;

//Mob Storage [Vector]
std::vector<mobData> allMobs;

//Mr Toh
char   g_charBuffer[128];
int    g_chInput = 0;
 
bool   keydownNum[10];
bool   keydownChar[26];

int    i;
bool   enterpressed = false;

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
    mob.X = 1;
	mob.Y = 2;
    if (lostlives == 0)
    {
        user.lives = 3;
    }
    user.health = 5;
    user.points = 0;
    user.select = 0;
	mapUpdate.boost = 0;
    user.bomb = 0;
	mapUpdate.bombtaken = 0;
	mapUpdate.invistaken = 0;
	user.invis = 0;
	user.invispot = 0;
	mapUpdate.MedsTaken = 0;
    user.stage1 = 0;
    user.stage2 = 0;
    user.stage3 = 0;
    user.stage4 = 0;
	lastknown.X = 0;
	lastknown.Y = 0;
    std::ofstream log;
    log.open("log.txt", std::fstream::trunc);
    log.close();
    user.gameover = 0;
    user.name;
    //user.wroteHighScore = 0;
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
    g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE); //SPACE BAR
    g_abKeyPressed[K_BACK] = isKeyPressed(VK_BACK);
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
		case S_MENU: 
            mainMenu(g_Console, user);
            user.points = 0;
            user.final_score = 0;
            user.wroteHighScore = 0;
            user.name = "";
            user.samename = 0;
			break;
		case S_OPTIONS: options(g_Console, user);
			break;
		case S_HELP: help(g_Console, user);
			break;
		case S_HIGHSCORE: highscoreMenu( g_Console, user);
			break;
		case S_ICON: playerIcon(g_Console, user);
			break;
        case S_TUTORIAL:
            if(tutorial_init == 0)
            {
                reset();
                spawnblock(blocks);
				allMobs.clear();
				spawnmob(allMobs);
                g_sChar.m_cLocation.X = 1;
                g_sChar.m_cLocation.Y = 1;
				user.timelimit = 0;
                tutorial_init = 1;
				blind = 0;
				for(int i = 0; i < allMobs.size(); i++)
				{
					allMobs[i].movedelay = 0.3;
				}
            }
            gameplay();
            if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
			{
				tutorial_init = 0;
				g_eGameState = S_MENU;
			}
			if(g_abKeyPressed[K_ESCAPE])
			{
				tutorial_init = 0;
			}
            break;
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        
        case S_GAME1:
			if(init1 == 0)// initialise the stage such as player starting location and monster spawns
			{
				g_sChar.m_cLocation.X = 3;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				boostcd = 0;
				init1 = 1;
			}
			if (extime1 == 0)// initialise variables that are not supposed to be reset on death or pitfall trap such as treasures and time limit extensions
			{
				mapUpdate.TTaken = 0;
				startGame(user, range, blind);
				extime1 = 1;
			}
			user.start = 1;// activates the time limit
			gameplay(); // gameplay logic when we are in the game
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')// exit
			{
                writeLog("Stage Completed!" , g_dElapsedTime);
				Endtime = g_dElapsedTime;
                user.stage1 = 1;
				g_eGameState = S_SPLASHSCREEN2;
			}
            break;
		
        case S_SPLASHSCREEN2: splashNextStageWait();
			break;
		
        case S_GAME2:
			if(init2 == 0)
			{
				if(extime2 == 0)
				{
					mapUpdate.TTaken = 0;
					addTime(user);
					extime2 = 1;
				}
				g_sChar.m_cLocation.X = 46;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				for(int i = 0; i < allMobs.size(); i++)// sets mobs' move delay based on difficulty
				{
					allMobs[i].movedelay = monSpd(user, allMobs[i]);
				}
				init2 = 1;
			}
				gameplay();
				if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
				{
                    writeLog("Stage Completed!" , g_dElapsedTime);
					Endtime = g_dElapsedTime;
                    user.stage2 = 1;
					g_eGameState = S_SPLASHSCREEN3;
				}
				break;

			case S_SPLASHSCREEN3: splashNextStageWait();
				break;

			case S_GAME3:
			if(init3 == 0)
			{
				if(extime3 == 0)
				{
					mapUpdate.TTaken = 0;
					addTime(user);
					extime3 = 1;
				}
				g_sChar.m_cLocation.X = 3;
				g_sChar.m_cLocation.Y = 3;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				for(int i = 0; i < allMobs.size(); i++)
				{
					allMobs[i].movedelay = monSpd(user, allMobs[i]);
				}
				init3 = 1;
			}
			gameplay();
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
				{
                    writeLog("Stage Completed!" , g_dElapsedTime);
					Endtime = g_dElapsedTime;
                    user.stage3 = 1;
					g_eGameState = S_SPLASHSCREEN4;
				}
			break;
        
			case S_SPLASHSCREEN4: splashNextStageWait();
				break;

			case S_GAME4:
			if(init4 == 0)
			{
				if(extime4 == 0)
				{
					mapUpdate.TTaken = 0;
					addTime(user);
					extime4 = 1;
				}
				g_sChar.m_cLocation.X = 45;
				g_sChar.m_cLocation.Y = 18;
				reset();
				spawnblock(blocks);
				spawnmob(allMobs);
				for(int i = 0; i < allMobs.size(); i++)
				{
					allMobs[i].movedelay = monSpd(user, allMobs[i]);
				}
				init4 = 1;
			}
			gameplay();
            if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
			{
                writeLog("Stage Completed!" , g_dElapsedTime);
				Endtime = g_dElapsedTime;
                user.stage4 = 1;
				g_eGameState = S_NAME;
                user.gameover = 1;
			}
			break;

        case S_NAME:
            if (init_name == 0)
            {
                user.name.clear();
                init_name = 1;
            }

            if (g_abKeyPressed[K_ENTER] && user.samename != 1)
            {  
                user.wroteHighScore = 1;
                g_eGameState = S_GAMEOVER;
				stopswitch = g_dElapsedTime + 0.2;
            }

            break;

        case S_GAMEOVER:
            if (user.wroteHighScore == 1)
            {
                calculateFinal ( user , Endtime );
                highscoreWrite( user , g_Console );
                user.wroteHighScore = 0;
            }

			gameplay();
            break;
    }
}

void reset()
{
	user.select = 0;
	user.inventoryitems.clear();
    count = 0;
	mapUpdate.boost = 0;
	mapUpdate.switch1 = 0;
	mapUpdate.switch2 = 0;
	mapUpdate.switch3 = 0;
	user.bomb = 0;
	mapUpdate.bombtaken = 0;
	mapUpdate.Cexplode = 0;
	user.invispot = 0;
	user.invis = 0; // invis state

	mapUpdate.invistaken = 0;
	mapUpdate.TTaken = 0;
	mapUpdate.MedsTaken = 0;

	allMobs.clear();
	spawnblock(blocks);
	g_dBounceTime = 0;
	stopswitch = 0;
	lavastop = 0;
    user.name = "";
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
		case S_HELP: help(g_Console, user);
			break;
		case S_OPTIONS: options(g_Console, user);
			break;
		case S_MENU: mainMenu(g_Console, user);
			break;
		case S_HIGHSCORE: highscoreMenu( g_Console, user);
			break;
		case S_ICON: playerIcon(g_Console, user);
			break;
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_TUTORIAL: 
            renderTutorial();
            renderGame();
            g_Console.writeToBuffer(51, 0, "TUTORIAL", 10);
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
void splashNextStageWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime >= Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
    {
		g_eGameState = static_cast<EGAMESTATES>(g_eGameState + 1);
		g_dElapsedTime -= 3;
	}
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
				if(mapUpdate.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'Y')
			{
				if(mapUpdate.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'Z')
			{
				if(mapUpdate.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'C')
			{
				if(mapUpdate.Cexplode == 1)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else 
			{ 
				        Beep(1440, 30);
				g_sChar.m_cLocation.Y--;
			}
			g_dBounceTime = g_dElapsedTime + 0.2;
		}		
    }
    if (g_abKeyPressed[K_LEFT])
    {
        Beep(1440, 30);
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'X')
			{
				if(mapUpdate.switch1 == 1)
				{
					Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'Y')
			{
				if(mapUpdate.switch2 == 1)
				{
					Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'Z')
			{
				if(mapUpdate.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X--;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'C')
			{
				if(mapUpdate.Cexplode == 1)
				{
					g_sChar.m_cLocation.X--;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.X--;
			}
			g_dBounceTime = g_dElapsedTime + 0.2;
		}
    }
	if (g_abKeyPressed[K_DOWN])
    {
		if(MapCollision->data[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'X')
			{
				if(mapUpdate.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'Y')
			{
				if(mapUpdate.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'Z')
			{
				if(mapUpdate.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X] == 'C')
			{
				if(mapUpdate.Cexplode == 1)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.Y++;
			}
			g_dBounceTime = g_dElapsedTime + 0.2;
		}
	}
    if (g_abKeyPressed[K_RIGHT])
    {
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'W')
		{
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'X')
			{
				if(mapUpdate.switch1 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'Y')
			{
				if(mapUpdate.switch2 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'Z')
			{
				if(mapUpdate.switch3 == 1)
				{
					        Beep(1440, 30);
					g_sChar.m_cLocation.X++;
				}
			}
			else if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'C')
			{
				if(mapUpdate.Cexplode == 1)
				{
					g_sChar.m_cLocation.X++;
				}
			}
			else
			{
				        Beep(1440, 30);
				g_sChar.m_cLocation.X++;
			}
			g_dBounceTime = g_dElapsedTime + 0.2;
		}
    }
    
    //Tutorial Msg
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'a')
    {
            std::ofstream log;
            log.open("log.txt", std::fstream::trunc);
            log.close();
            writeLog("Traps and Medkits ahead" , g_dElapsedTime);
            writeLog("Traps damage you" , g_dElapsedTime);
    }

    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'b')
    {
            std::ofstream log;
            log.open("log.txt", std::fstream::trunc);
            log.close();
            writeLog("Pitfalls Ahead" , g_dElapsedTime);
            writeLog("They make you fall a level" , g_dElapsedTime);
    }
        
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'c')
    {
        std::ofstream log;
        log.open("log.txt", std::fstream::trunc);
        log.close();
        writeLog("Bomb ahead, use it" , g_dElapsedTime);
    }

    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'd')
    {
        std::ofstream log;
        log.open("log.txt", std::fstream::trunc);
        log.close();
        writeLog("Invisibility ahead, avoid enemy" , g_dElapsedTime);
    }
    

    // POINTS
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'T' && mapUpdate.TTaken == 0)
    {
        user.points += 1;
		mapUpdate.TTaken = 1; 
    }

    // SELECTON
    if ((g_abKeyPressed[K_SELECT]) && g_dElapsedTime > stopswitch)
    {
        user.select += 1;
        if (user.select >= user.inventoryitems.size())
        {
            user.select = 0;
        }
		stopswitch = g_dElapsedTime + .2;
    }

    // INVENTORY
    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I') && (mapUpdate.boost == 0)) // Boost
    {
        user.inventoryitems.push_back("Boost");
        ++count;
		//user.boost = 1;
    }

    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'J') && (user.bomb == 0) && (mapUpdate.bombtaken == 0)) // Bomb
    {
        user.inventoryitems.push_back("Bomb");
        ++count;
		//user.bomb = 1;
    }
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'L' && user.invispot == 0 && mapUpdate.invistaken == 0) //Invis
	{
        user.inventoryitems.push_back("Invis Pot");
        ++count;
	}

	//RESET (for debugging by skipping stages)
	if(g_abKeyPressed[K_RESET])
	{
		//g_eGameState = S_SPLASHSCREEN2;
        g_eGameState = static_cast<EGAMESTATES>(g_eGameState + 1);
	}

    //POINTS
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'T' && mapUpdate.TTaken == 0)
    {
        user.points += 1;
		mapUpdate.TTaken = 1; 
    }
    //Item Usage
    //-----Boost-----
    if (mapUpdate.boost == 1 && user.inventoryitems[user.select] == "Boost")
	{
		if(g_abKeyPressed[K_UP] && g_abKeyPressed[K_USE])
		{
			item1up(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd , mapUpdate);
		}
		else if(g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_USE])
		{
			item1left(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd , mapUpdate);
		}
		else if(g_abKeyPressed[K_DOWN] && g_abKeyPressed[K_USE])
		{
			item1down(MapCollision, g_sChar.m_cLocation, user, g_dElapsedTime, g_Console, boostcd , mapUpdate);
		}
		else if(g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_USE])
		{
			item1right(MapCollision, g_sChar.m_cLocation,user, g_dElapsedTime, g_Console, boostcd , mapUpdate);
		}
	}
	//-----Bomb-----
    if(user.bomb == 1 && user.inventoryitems[user.select] == "Bomb" && g_abKeyPressed[K_USE] && abilitydelay < g_dElapsedTime)
	{
		item2(user, mapUpdate, MapCollision, g_sChar.m_cLocation);
        abilitydelay = g_dElapsedTime + .2;
	}
	//-----Invis-----
	if(user.invispot == 1 && user.inventoryitems[user.select] == "Invis Pot" && g_abKeyPressed[K_USE] && abilitydelay < g_dElapsedTime)
	{
        for (int find_invis = 0; find_invis <  user.inventoryitems.size(); ++find_invis)
        {
            if (user.inventoryitems[find_invis] == "Invis Pot")
            {
                user.inventoryitems.erase(user.inventoryitems.begin() + find_invis);
                if (user.select >= user.inventoryitems.size())
                {
                    user.select = 0;
                }
                break;
            }
        }

		item3(user,g_sChar, g_dElapsedTime, invisExp);
        abilitydelay = g_dElapsedTime + .2;
		writeLog("You are invis!", g_dElapsedTime);
    }

    // respawn if player health is at 0
    if (user.health <= 0)
    {
        //g_bQuitGame = true;
        //g_eGameState = S_SPLASHSCREEN;
        --user.lives;
        user.health = 5;
        if (g_eGameState == S_TUTORIAL)
        {
            tutorial_init = 0;
        }

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
    
}
void processUserInput()
{
    // resets the game and goes back to main menu if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MENU;
		init1 = 0;
		init2 = 0;
		init3 = 0;
		init4 = 0;
		extime1 = 0;
		extime2 = 0;
		extime3 = 0;
		extime4 = 0;
		user.points = 0;
		user.start = 0;
	}
}

void EnterName()
{
    if (g_abKeyPressed[K_SPACE]){ user.name += " "; }
    if (g_abKeyPressed[K_BACK]){ if(user.name.size() > 0) user.name.pop_back(); }

    // detect Numbers pressed
    for (i=0; i<10; i++)
    {
            if (keydownNum[i] == false)
            {
                    if (isKeyPressed('0'+i))
                        keydownNum[i] = true;
            }
            else // (keydownNum[i] == true)
            {
                    if (!isKeyPressed('0'+i))
                    {
                        /*g_charBuffer[g_chInput] = '0'+i;
                        ++g_chInput %= 128;*/
                        user.name += '0'+i;
                        keydownNum[i] = false;
                    }
            }
                          
            if (isKeyPressed(VK_RETURN))
            {
                    enterpressed = true;             
                    break;
            }
    }
 
    // detect A-Z pressed
    if (!enterpressed)
    {
            for (i=0; i<27; i++)
            {
                    if (keydownChar[i] == false)
                    {
                        if (isKeyPressed('A'+i))
                                keydownChar[i] = true;           
                    }
                    else
                    {
                        if (!isKeyPressed('A'+i))
                        {
                                /*g_charBuffer[g_chInput] = 'a'+i;
                                ++g_chInput %= 128;*/
                                keydownChar[i] = false;
                                user.name += 'A'+i;
                        }
                    }
                          
                    if (isKeyPressed(VK_RETURN))
                    {
                        enterpressed = true;
                        break;
                    }
            }
             
    }

    //Check for same name used.
    //checkName( user , g_Console );
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
    c.X = c.X / 2.5 - 9;
    g_Console.writeToBuffer(c, "Tower Of PuzzMaz STAGE 1", 0xfc);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2.3 - 20;
    g_Console.writeToBuffer(c, "You can use boost to cross lava, my friend.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2.8 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to return to the main menu.", 0xf9);
}

void renderSplashStage2()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2.5 - 9;
    g_Console.writeToBuffer(c, "Tower Of PuzzMaz STAGE 2", 0xfc);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2.3 - 20;
    g_Console.writeToBuffer(c, "Some blocks are pushable, Player, use Strength!", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2.8 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to return to the main menu.", 0xf9);
}

void renderSplashStage3()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2.5 - 9;
    g_Console.writeToBuffer(c, "Tower Of PuzzMaz STAGE 3", 0xfc);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 3 - 20;
    g_Console.writeToBuffer(c, "Number of treasures found is directly proportional to your points.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2.8 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to return to the main menu.", 0xf9);
}

void renderSplashStage4()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2.5 - 9;
    g_Console.writeToBuffer(c, "Tower Of PuzzMaz STAGE 4", 0xfc);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 3 - 20;
    g_Console.writeToBuffer(c, "You will still be hurt if you go near a monster while invisible.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2.8 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to return to the main menu.", 0xf9);
}

void renderGameover()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X  / 2 - 9;
    g_Console.writeToBuffer(c, "GAME OVER", 0xf3);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X  / 2 - 20;
    g_Console.writeToBuffer(c, "Press Esc to return to the main menu.", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Your points are: ", 0xf9);
    c.X += 16;
    finalscore( g_Console , user , Endtime , c); //Final Score
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    
    highscoreRead ( user , g_Console );
}

void renderEnterName()
{
    bool buttonPress = 0;
    COORD c = g_Console.getConsoleSize();
    c.X = 30;
    c.Y = 13;
    g_Console.writeToBuffer(c, "Enter your name: ", 0xf9);

    EnterName();

    //Check for same name used.
    checkName( user , g_Console );
    c.Y += 1;
    g_Console.writeToBuffer(c, user.name, 0xf9);
}

void renderStage1()
{
	MapCollision = load_map("stage1.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage1.txt" , mapUpdate);
}
void renderStage2()
{
	MapCollision = load_map("stage2.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage2.txt" , mapUpdate);
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console, blind);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range, mapUpdate);
	}
}
void renderStage3()
{
	MapCollision = load_map("stage3.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage3.txt" , mapUpdate);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range, mapUpdate);
	}
}
void renderStage4()
{
	MapCollision = load_map("stage4.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "stage4.txt" , mapUpdate);
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console, blind);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range, mapUpdate);
	}
}

void renderTutorial()
{
    MapCollision = load_map("tutorial.txt");
	createMap(g_sChar.m_cLocation, blind, range, user, g_Console, "tutorial.txt" , mapUpdate);
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console, blind);
	for(unsigned int i = 0; i < allMobs.size(); ++i)
	{
		mobmove(g_sChar.m_cLocation,allMobs[i],g_dElapsedTime,g_Console, MapCollision, user, blind, range, mapUpdate);
	}
}
void renderGame()
{
    background ( g_Console );
    renderCharacter(user);  // renders the character into the buffer

    // Switch Alerts
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '1' && mapUpdate.switch1 != 1){
		mapUpdate.switch1 = 1;
        writeLog("X Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '2'  && mapUpdate.switch2 != 1)
	{
		mapUpdate.switch2 = 1;
        writeLog("Y Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '3'  && mapUpdate.switch3 != 1)
	{
		mapUpdate.switch3 = 1;
        writeLog("Z Switch Activated!", g_dElapsedTime);
	}
	// ---If boost is taken---
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I' && mapUpdate.boost == 0)
	{
		mapUpdate.boost = 1;
	}
	// ---If bomb is taken---
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'J' && mapUpdate.bombtaken == 0 && user.bomb == 0)
	{
		user.bomb = 1;
		mapUpdate.bombtaken = 1;
        writeLog("You got a bomb!", g_dElapsedTime);
	}
	// ---If invisible potion is taken---
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'L' && user.invispot == 0 && mapUpdate.invistaken == 0)
	{
		user.invispot = 1;
		mapUpdate.invistaken = 1;
        writeLog("You got an invis potion!", g_dElapsedTime);
	}
	//-----Medpack-----
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' && mapUpdate.MedsTaken == 0 && user.health != 5)
	{
		medpack(user , mapUpdate);
        writeLog("You have been healed!", g_dElapsedTime);
	}
	//-----Damage Trap----
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'D' && user.health > 0 && trapdamage == 0)// trapdamage is to prevent players to take more damage than intended
	{
		trapdmg(user);
		writeLog("You have been hurt!", g_dElapsedTime);
		trapdamage = 1;
	}
    else if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] != 'D' )
	{
		trapdamage = 0;
	}
	// -----Pitfall-----
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'P' && user.health > 0)
	{
		reset();
		if(tutorial_init == 1)// for tutorial stage
		{
			tutorial_init = 0;
		}
		else // to reset the init values for the current and previous stage
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
			g_eGameState = static_cast<EGAMESTATES>(g_eGameState - 3);// Force players back to the splashscreen of the previous stage
		}
	}

    //-----Lava-----
    if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '=' && user.health > 0 && lavadamage == 0 && g_dElapsedTime > lavastop)// lavadamage is the same purpose as trapdamage, lavastop prevents more lives being removed than intended
	{
		if(g_sChar.m_cLocation.X == blocks.X && g_sChar.m_cLocation.Y == blocks.Y)// If player is ontop of a pushable block in the lava
		{
			lavadamage = 1;
		}
		else
		{
			lavastop = g_dElapsedTime + .5;
			lavadamage = 1;
			user.health -= user.health;
		}
	}
    else
	{
		lavadamage = 0;
	}
	//----Remove all player lives if g_dElapsedTime exceeds the time limit-----
	if (g_dElapsedTime >= user.timelimit && user.start == 1)
	{
		user.lives -= user.lives;
	}

	if (user.lives <= 0)
	{
		colour(BACKGROUND_RED);
        Beep(2000, 1000);
        user.gameover = 1;
        writeLog("You died!", g_dElapsedTime);
        Endtime = g_dElapsedTime;

        g_eGameState = S_NAME;
	} 

    //Check for cooldown
    if (g_dElapsedTime >= boostcd && mapUpdate.boost == 1 && boostcd != -1)
    {
        writeLog("Boost is ready!", g_dElapsedTime);
        boostcd = -1;
    }
	//-----If invisible effect wears off-----
	if(g_dElapsedTime >= invisExp && user.invis == 1)
	{
		user.invis = 0;
		invisExp = 0;
	}
   
    //UI functions
    background ( g_Console );
    divider( g_Console) ;
    timer( g_dElapsedTime , g_Console , user);
    lives( user , g_Console);
    renderInventory ( user , g_Console , boostcd , g_dElapsedTime , mapUpdate);
    point( user , g_Console);
    selector ( user , g_Console);
    readLog ( g_Console , g_dElapsedTime);
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
    if (g_sChar.m_bActive && user.invis == 1)// change colour of player if invisible
    {
        charColor = 0x12;
    }
	else if (g_sChar.m_bActive)
	{
		charColor = 0xe0;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, user.icon, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = 72;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
    // displays the elapsed time
    ss.str("");
    ss << static_cast<int>(g_dElapsedTime) << " secs";
    c.X = 61;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str(), 10);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}