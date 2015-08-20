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
COORD charLocation;
COORD consoleSize;

PMAP MapCollision;

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
    charLocation.X = 32;
    charLocation.Y = 25;
	// 76 17
	//15 69 23
    elapsedTime = 0.0;
	MapCollision = load_map("map.txt");

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
	//char arr[27][79];
	//std::ifstream myfile;
	//myfile.open("testlevel.txt");
	//std::string line;
	//for(int i=0;i<27;++i)
	//{
	//	getline(myfile, line);
	//	for(int j=0;j<79;++j)
	//	{
	//		if(line[j] == -90)
	//		{
	//		arr[i][j] = 219;
	//		}else
	//		{
	//			arr[i][j] = 255;
	//		}
	//	}
	//}
	//gotoXY(0, 0);
	//myfile.close();
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y - 1][charLocation.X] != 'B')
		{
			charLocation.Y--;
		}		
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y][charLocation.X - 1] != 'B')
		{
			charLocation.X--;
		}
    }
	//if(g_abKeyPressed[K_LEFT] && g_cCharLocation.X == 0)
	//{
	//	Beep(1440, 30);
	//	g_cCharLocation.X += g_cConsoleSize.X -1; 
	//}
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y + 1][charLocation.X] != 'B')
		{
			charLocation.Y++;
		}	
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
		if(MapCollision->data[charLocation.Y][charLocation.X + 1] != 'B')
		{
			charLocation.X++;
		}
 
    }
	//if(g_abKeyPressed[K_RIGHT] && g_cCharLocation.X == g_cConsoleSize.X - 1)
	//{
	//	Beep(1440, 30);
	//	g_cCharLocation.X = 0; 
	//}
	//if(g_abKeyPressed[K_TEST] && g_abKeyPressed[K_RIGHT] && g_cCharLocation.X < g_cConsoleSize.X - 1)
	//{
	//	Beep(1440, 30);
	//	g_cCharLocation.X += 10;
	//	while(g_cCharLocation.X > g_cConsoleSize.X -1)
	//	{
	//		g_cCharLocation.X--;
	//	}
	//}
    
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;

    // quits if player lives at 0
    if (user.lives == 0)
    {
        g_quitGame = true;
    }

    //TEST FOR DAMAGE
    if (keyPressed[K_UP])
    {
        user.lives -= 1;
    }

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
	createMap(charLocation, 1, 10);
    
    //UI functions
    timer(elapsedTime);

    lives( user );
    renderInventory ( user );
    point( user );
}