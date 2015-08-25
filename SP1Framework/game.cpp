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

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

COORD consoleSize;
COORD blocks;
COORD mob;
COORD lastknown;
PMAP MapCollision;

bool init1 = 0;
bool init2 = 0;
int range;
bool lostlives = 0;

double Endtime;
double boostcd = 0;

//diffculty
const int normal = 0;
const int hard = 1;
const int insane = 2;

//Last known Coordinates
int lastX = 0;
int lastY = 0;

player user;

// Game specific variables here
SGameChar   g_sChar;
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
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 25, L"Consolas");
	user.difficulty = insane;
	if(user.difficulty == normal)
	{
		range = 6;
		user.timelimit = 180;
	}
	else if(user.difficulty == hard)
	{
		range = 5;
		user.timelimit = 150;
	}
	else if(user.difficulty == insane)
	{
		range = 4;
		user.timelimit = 120;
	}
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
	user.MTaken = 0;
	lastknown.X = 0;
	lastknown.Y = 0;
    std::ofstream log;
    log.open("log.txt", std::fstream::trunc);
    log.close();

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
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        
        case S_GAME1:
			if(init1 == 0)
			{
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 1;
				init1 = 1;
			}
			gameplay(); // gameplay logic when we are in the game
			if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'H')
			{
				Endtime = g_dElapsedTime;
				g_eGameState = S_SPLASHSCREEN2;
			}
            break;
		
        case S_SPLASHSCREEN2: splashStage2Wait();
			break;
		
        case S_GAME2:
			if(init2 == 0)
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
				g_sChar.m_cLocation.X = 46;
				g_sChar.m_cLocation.Y = 3;
				blocks.X = 41;
				blocks.Y = 4;
				user.boost = 0;
				user.switch1 = 0;
				user.switch2 = 0;
				user.switch3 = 0;
				user.bomb = 0;
				user.invis = 0;
				user.TTaken = 0;
				user.strength = 0;
				user.MTaken = 0;
				for(int i=0; i < 6; ++i)
				{
					user.inventory[i] = 'f';
				}
				user.inventoryitems.clear();
				init2 = 1;

			}
			gameplay();
			break;
        
        case S_GAMEOVER:
            break;
    }
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
        case S_GAMEOVER:
            renderGameover();
    }
    //renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME1;
}
void splashStage2Wait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > Endtime + 3) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME2;
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
    if ((g_abKeyPressed[K_SELECT]) && (user.inventory[0] == 't'))
    {
        user.select += 1;
        if (user.select == user.inventoryitems.size()+1)
        {
            user.select = 0;
        }
    }

    // INVENTORY
    int count = 0;
    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I') && (user.boost == 0)) // Boost
    {
        user.inventory[count] = 't';
        user.inventoryitems.push_back("Boost");
        ++count;
		//user.boost = 1;
    }

    if ((MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 229) && (user.bomb == 0)) // Bomb
    {
        user.inventory[count] = 't';
        user.inventoryitems.push_back("Bomb");
        ++count;
		//user.bomb = 1;
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
        init1 = 0;
        lostlives = 1;
        writeLog("You lost a live!", g_dElapsedTime);
	}
	//RESET
	if(g_abKeyPressed[K_RESET])
	{
		g_eGameState = S_SPLASHSCREEN2;
	}

    //POINTS
    if (MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'T' && user.TTaken == 0)
    {
        user.points += 1;
		user.TTaken = 1; 
    }

    //Use Items
    //Boost
    if (user.boost == 1 && user.inventory[user.select] == 't')
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
    if(user.bomb == 1 && /*user.inventoryitems[user.select] == "Bomb"*/user.inventory[user.select] == 't')
	{
		int amt = user.bomb;
		if(MapCollision->data[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'C')
		{
			if(g_abKeyPressed[K_UP] && g_abKeyPressed[K_USE])
			{
				item2(user);
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'C')
		{
			if(g_abKeyPressed[K_LEFT] && g_abKeyPressed[K_USE])
			{
				item2(user);
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == 'C')
		{
			if(g_abKeyPressed[K_DOWN] && g_abKeyPressed[K_USE])
			{
				item2(user);
			}
		}
		if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'C')
		{
			if(g_abKeyPressed[K_RIGHT] && g_abKeyPressed[K_USE])
			{
				item2(user);
			}
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
    g_Console.writeToBuffer(c, "Tower Of Maz STAGE 1", 0xf3);
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
    g_Console.writeToBuffer(c, "Hint: You can move diagonally", 0xf9);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0xf9);
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
}

void renderStage1()
{
	MapCollision = load_map("stage1.txt");
	createMap1(g_sChar.m_cLocation, 1, range, user, g_Console);
}
void renderStage2()
{
	MapCollision = load_map("stage2.txt");
	createMap2(g_sChar.m_cLocation, 1, range, user, g_Console);
	blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console);
}
void renderGame()
{
    background ( g_Console );
    renderCharacter();  // renders the character into the buffer

    // Write Log
	mobmove(g_sChar.m_cLocation,mob,g_dElapsedTime,g_Console, MapCollision);
    // Creating Map
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '1' && user.switch1 != 1){
		user.switch1 = 1;
		//g_Console.writeToBuffer(51, 12, "You activated X Switch!", 0xf1);
        writeLog("X Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '2'  && user.switch2 != 1)
	{
		user.switch2 = 1;
		//g_Console.writeToBuffer(51, 12, "You activated Y Switch!", 0xf1);
        writeLog("Y Switch Activated!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '3'  && user.switch3 != 1)
	{
		user.switch3 = 1;
		//g_Console.writeToBuffer(51, 12, "You activated Z Switch!", 0xf1);
        writeLog("Z Switch Activated!", g_dElapsedTime);
	}

	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'I' && user.boost == 0)
	{
		user.boost = 1;
		//g_Console.writeToBuffer(51, 12, "You can now Boost!", 0xf1);
        //writeLog("You can now boost!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'J' && user.bomb == 0)
	{
		user.bomb = 1;
		//g_Console.writeToBuffer(51, 12, "You now have a bomb!", 0xf1);
        writeLog("You got a bomb!", g_dElapsedTime);
	}
	// medpack
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' && user.MTaken == 0 && user.lives != 5)
	{
		if(user.difficulty == normal || user.difficulty == hard)
		{
			if (user.health < 4)
			{
				user.health += 2;
				user.MTaken = 1;
			}
			else if (user.health == 4)
			{
				user.health += 1;
				user.MTaken = 1;
			}
		}
		else if(user.difficulty == insane)
		{
			if (user.health < 3)
			{
				user.health += 3;
				user.MTaken = 1;
			}
			else if (user.lives == 3)
			{
				user.health += 2;
				user.MTaken = 1;
			}
			else if (user.lives == 4)
			{
				user.health += 1;
				user.MTaken = 1;
			}
		}
		//g_Console.writeToBuffer(51, 12, "You are now healed!", 0xf1);
        writeLog("You have been healed!", g_dElapsedTime);
	}
	if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'D' && user.health > 0)
	{
		//g_Console.writeToBuffer(51, 12, "You have been hurt!", 0xf1);
        //writeLog("You have been hurt!", g_dElapsedTime);
		if(user.difficulty == hard || user.difficulty == normal)
		{
			if(lastX != g_sChar.m_cLocation.X)
			{
				user.health--;
				lastX = g_sChar.m_cLocation.X;
				writeLog("You have been hurt!", g_dElapsedTime);
			}
			else if(lastY != g_sChar.m_cLocation.Y)
			{
				user.health--;
				lastY = g_sChar.m_cLocation.Y;
				writeLog("You have been hurt!", g_dElapsedTime);
			}
		}
		else if(user.difficulty == insane)
		{
			if(lastX != g_sChar.m_cLocation.X)
			{
				user.health -= 2;
				lastX = g_sChar.m_cLocation.X;
				writeLog("You have been hurt!", g_dElapsedTime);
			}
			else if(lastY != g_sChar.m_cLocation.Y)
			{
				user.health -= 2;
				lastY = g_sChar.m_cLocation.Y;
				writeLog("You have been hurt!", g_dElapsedTime);
			}
		}
	}
    else if(MapCollision->data[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '=' && user.health > 0)
	{
		if(g_sChar.m_cLocation.X != blocks.X || g_sChar.m_cLocation.Y != blocks.Y)
		{
			user.health -= user.health;
		}
	}
    else
	{
		lastX = g_sChar.m_cLocation.X;
		lastY = g_sChar.m_cLocation.Y;
	}
	// time limit
	if (g_dElapsedTime >= user.timelimit)
	{
		user.lives -= user.lives;
	}
	if (user.lives <= 0)
	{
		colour(BACKGROUND_RED);
		//g_Console.writeToBuffer(51, 13, "YOU DIED", 0xf1);
        writeLog("You died!", g_dElapsedTime);
        g_eGameState = S_GAMEOVER;
		Beep(2000, 1000);
	} 

    //Check for cooldown
    /*if (g_dElapsedTime >= boostcd && user.boost == 1 && boostcd != -1)
    {
        writeLog("Boost is ready!", g_dElapsedTime);
        boostcd = -1;
    }*/
   
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

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0xfA;
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