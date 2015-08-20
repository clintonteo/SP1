// This is the main file for the game logic and function
//
//
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
bool flipswitch1 = 0;
bool flipswitch2 = 0;
COORD charLocation;
COORD consoleSize;

PMAP MapCollision;
//Start Health
int health = 5;
int lastX = 0;
int lastY = 0;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 1;
    charLocation.Y = 1;
	// 76 17
	//15 69 23
    elapsedTime = 0.0;
	MapCollision = load_map("stage1.txt");

   /* player user;
    bool damage = 0;
    user.lives = 10;
    int * livesptr = &user.lives;*/
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
}

   

void update(double dt, player & user)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
    if (keyPressed[K_UP] && charLocation.Y > 0 && health > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y - 1][charLocation.X] != 'W')
		{
			charLocation.Y--;
		}		
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0 && health > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y][charLocation.X - 1] != 'W')
		{
			charLocation.X--;
		}
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y + 1][charLocation.X] != 'W')
		{
			if(MapCollision->data[charLocation.Y+1][charLocation.X] != 'X')
			{
				charLocation.Y++;
			}else if(flipswitch1 == 1)
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
			charLocation.X++;
		}
 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;

    // quits if player lives at 0
    if (user.lives == 0)
    {
        g_quitGame = true;    
	}

    ////TEST FOR DAMAGE
    //if (keyPressed[K_UP])
    //{
    //    user.lives -= 1;
    //}

    //TEST FOR INVENTORY
    for (int i = 1; i < 6; ++i)
    {
        user.inventory[i] = 'f';
    }
    user.inventory[0] = 't';
    user.inventory[3] = 't';
    user.inventory0 = "test item";
    user.inventory3 = "another item";

    // TEST FOR POINTS
    if (keyPressed[K_DOWN])
    {
        user.points += 1;
    }

    // TEST FOR SELECTON
    if (keyPressed[K_SELECT])
    {
        g_quitGame = true;
    }
}

//--------------------------------------------------------------
// Purpose	: Render function is to update the console screen
// Input	: void
// Output	: void
//--------------------------------------------------------------
void render( player & user )
{
    
    //UI functions
	createMap(charLocation, 1, 6, flipswitch1);

	if(MapCollision->data[charLocation.Y][charLocation.X] == '1')
	{
		flipswitch1 = 1;
		gotoXY(50, 4);
		cout << "YOU Activated X Switch!";
	}

	gotoXY(50, 3);
	if(MapCollision->data[charLocation.Y][charLocation.X] == 'D' && user.lives > 0)
	{
		cout << "You have been hurt!" << endl;
		if(lastX != charLocation.X)
		{
		user.lives--;
		lastX = charLocation.X;
		}else if(lastY != charLocation.Y)
		{
		user.lives--;
		lastY = charLocation.Y;
		}
	}else if(MapCollision->data[charLocation.Y][charLocation.X] == 'L' && user.lives > 0)
	{
		user.lives-=user.lives;
	}else
	{
		lastX = charLocation.X;
		lastY = charLocation.Y;
	}
	if(user.lives <= 0)
	{
		gotoXY(50, 4);
		cout << "YOU DIED!";
		Beep(2000, 1000);
	} 
    // render time taken to calculate this frame

    timer(elapsedTime);

    lives( user );
    renderInventory ( user );
    point( user );
}