// This is the main file for the game logic and function
//
//
#include "item.h"
#include "game.h"
#include "map.h"
#include "UI.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::cout;
using std::endl;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

COORD charLocation;
COORD consoleSize;
COORD blocks;
COORD lastknown;
PMAP MapCollision;

int range = 6;

//Last known Coordinates
int lastX = 0;
int lastY = 0;

player user;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(84, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 40;
    charLocation.Y = 12;
	// 76 17
	//15 69 23
    elapsedTime = 0.0;
	MapCollision = load_map("stage1.txt");
    
    user.lives = 10;
    user.points = 0;
    user.select = 1;
	user.boost = 0;
	user.ITaken = 0;
	blocks.X = 41;
	blocks.Y = 12;
	lastknown.X = 0;
	lastknown.Y = 0;
   
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    keyPressed[K_SELECT] = isKeyPressed(0x5A); // Z key
    keyPressed[K_USE] = isKeyPressed(VK_SPACE); // Spacebar // Use items
	keyPressed[K_RESET] = isKeyPressed(0x52); // R key // Resets the game
}

   

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
    if (keyPressed[K_UP] && charLocation.Y > 0 && user.lives > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y - 1][charLocation.X] != 'W')
		{
			if(MapCollision->data[charLocation.Y - 1][charLocation.X] == 'X')
			{
				if(user.switch1 == 1)
				{
					charLocation.Y--;
				}
			}
			else if (MapCollision->data[charLocation.Y - 1][charLocation.X] == 'Y')
			{
				if(user.switch2 == 1)
				{
					charLocation.Y--;
				}
			}
			else if (MapCollision->data[charLocation.Y - 1][charLocation.X] == 'Z')
			{
				if(user.switch3 == 1)
				{
					charLocation.Y--;
				}
			}
			else
			{
				charLocation.Y--;
			}
		}		
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0 && user.lives > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y][charLocation.X - 1] != 'W')
		{
			if(MapCollision->data[charLocation.Y][charLocation.X - 1] == 'X')
			{
				if(user.switch1 == 1)
				{
					charLocation.X--;
				}
			}
			else if (MapCollision->data[charLocation.Y][charLocation.X - 1] == 'Y')
			{
				if(user.switch2 == 1)
				{
					charLocation.X--;
				}
			}
			else if (MapCollision->data[charLocation.Y][charLocation.X - 1] == 'Z')
			{
				if(user.switch3 == 1)
				{
					charLocation.X--;
				}
			}
			else
			{
				charLocation.X--;
			}
		}
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y + 1][charLocation.X] != 'W')
		{
			if(MapCollision->data[charLocation.Y+1][charLocation.X] == 'X')
			{
				if(user.switch1 == 1)
				{
					charLocation.Y++;
				}
			}
			else if (MapCollision->data[charLocation.Y+1][charLocation.X] == 'Y')
			{
				if(user.switch2 == 1)
				{
					charLocation.Y++;
				}
			}
			else if (MapCollision->data[charLocation.Y+1][charLocation.X] == 'Z')
			{
				if(user.switch3 == 1)
				{
					charLocation.Y++;
				}
			}
			else
			{
				charLocation.Y++;
			}
		}

	}
    if (keyPressed[K_RIGHT]/* && charLocation.X < consoleSize.X - 1*/)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y][charLocation.X + 1] != 'W')
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + 1] == 'X')
			{
				if(user.switch1 == 1)
				{
					charLocation.X++;
				}
			}
			else if (MapCollision->data[charLocation.Y][charLocation.X + 1] == 'Y')
			{
				if(user.switch2 == 1)
				{
					charLocation.X++;
				}
			}
			else if (MapCollision->data[charLocation.Y][charLocation.X + 1] == 'Z')
			{
				if(user.switch3 == 1)
				{
					charLocation.X++;
				}
			}
			else
			{
				charLocation.X++;
			}
		}
    }

    // POINTS
    if (MapCollision->data[charLocation.Y][charLocation.X] == 'T' && user.TTaken == 0)
    {
        user.points += 1;
		user.TTaken = 1; 
    }

    // SELECTON
    if (keyPressed[K_SELECT])
    {
        user.select += 1;
        if (user.select == 7)
        {
            user.select = 1;
        }
    }

    // INVENTORY
    int count = 0;
    if ((MapCollision->data[charLocation.Y][charLocation.X] == 'I') && (user.ITaken == 0))
    {
        user.inventory[count] = 't';
        user.inventoryitems.push_back("Boost");
        ++count;
        user.ITaken = 1;
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;

    // quits if player lives at 0
    if (user.lives == 0)
    {
        g_quitGame = true;    
	}
	//RESET
	if(keyPressed[K_RESET])
	{
		init();
	}

    if (MapCollision->data[charLocation.Y][charLocation.X] == 'T' && user.TTaken == 0)
    {
        user.points += 1;
		user.TTaken = 1; 
    }

    //Boost
	if (user.boost == 1)
	{
		if(keyPressed[K_UP] && keyPressed[K_USE])
		{
			item1up(MapCollision, charLocation);
		}
		else if(keyPressed[K_LEFT] && keyPressed[K_USE])
		{
			item1left(MapCollision, charLocation);
		}
		else if(keyPressed[K_DOWN] && keyPressed[K_USE])
		{
			item1down(MapCollision, charLocation);
		}
		else if(keyPressed[K_RIGHT] && keyPressed[K_USE])
		{
			item1right(MapCollision, charLocation);
		}
	}

}

//--------------------------------------------------------------
// Purpose	: Render function is to update the console screen
// Input	: void
// Output	: void
//--------------------------------------------------------------
void render()
{
    // Creating Map
	createMap(charLocation, 1, range, user);
	blockp(charLocation, blocks, lastknown, range);
	if(MapCollision->data[charLocation.Y][charLocation.X] == '1')
	{
		user.switch1 = 1;
		gotoXY(51, 12);
		cout << "YOU Activated X Switch!";
	}
	if(MapCollision->data[charLocation.Y][charLocation.X] == '2')
	{
		user.switch2 = 1;
		gotoXY(51, 12);
		cout << "YOU Activated Y Switch!";
	}
	if(MapCollision->data[charLocation.Y][charLocation.X] == 'I' && user.ITaken == 0)
	{
		user.boost = 1;
		user.ITaken = 1;
		gotoXY(50, 12);
		cout << "You can now boost!" << user.boost;
	}
	gotoXY(51, 12);
	if(MapCollision->data[charLocation.Y][charLocation.X] == 'D' && user.lives > 0)
	{
		cout << "You have been hurt!" << endl;
		if(lastX != charLocation.X)
		{
		    user.lives--;
		    lastX = charLocation.X;
		}
        else if(lastY != charLocation.Y)
		{
		    user.lives--;
		    lastY = charLocation.Y;
		}
	}
    else if(MapCollision->data[charLocation.Y][charLocation.X] == '=' && user.lives > 0)
	{
		if(charLocation.X != blocks.X || charLocation.Y != blocks.Y)
		{
			user.lives -= user.lives;
		}
	}
    else
	{
		lastX = charLocation.X;
		lastY = charLocation.Y;
	}
	if (user.lives <= 0)
	{
		gotoXY(50, 4);
		cout << "YOU DIED!";
		Beep(2000, 1000);
	} 
   
    //UI functions
	colour(0x01);
    divider();
    timer(elapsedTime);
    lives( user );
    renderInventory ( user );
    point( user );
    selector ( user );
}