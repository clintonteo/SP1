#include <iostream>

#include "UI.h"
#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>


using std::cout;
using std::endl;
using std::string;
// UI THINGY

//Background
void background( Console & g_Console )
{
    for (int y_axis = 0; y_axis < 28; ++y_axis)
    {
        for (int x_axis = 50; x_axis < 80; ++x_axis)
        {
            g_Console.writeToBuffer(x_axis, y_axis, " ", 01);
        }
    }
}


//Divider
void divider(Console & g_Console)
{
    for (int i = 0; i < 28; ++i)
    {
		g_Console.writeToBuffer(50, i, "|", 0);
    }
}



//Timer Notification
void timer(double g_dElapsedTime, Console & g_Console)
{
    //Timer
    g_Console.writeToBuffer(61, 1, "Timer: ", 10);

    renderFramerate();

    //g_Console.writeToBuffer(61, 3, "Cooldown: ", 10);

    /*if ((g_dElapsedTime >= 120) && (g_dElapsedTime <= 130))
    {
        g_Console.writeToBuffer(56, 3, "You have 7mins left! ", 10);
    }
    if ((g_dElapsedTime >= 500) && (g_dElapsedTime <= 510))
    {
        g_Console.writeToBuffer(56, 3, "You have 4mins left! ", 10);
    }
    if ((g_dElapsedTime >= 480) && (g_dElapsedTime <= 490))
    {
        g_Console.writeToBuffer(56, 3, "You have 1min left! ", 10);
    }*/
}
    

//Lives
void lives( player & user, Console &g_Console )
{
	g_Console.writeToBuffer(61, 5, "Lives: ", 10);

    for (int count = 0; count < user.lives; ++count)
    {
		g_Console.writeToBuffer(57 + count*3, 6, "|HP|", 43);
    }
}

//Render Inventory
void renderInventory( player & user , Console & g_Console )
{
    g_Console.writeToBuffer(59 , 7, "Inventory: ", 10);

    for (int i = 0; i < user.inventoryitems.size(); ++i)
    {
        if (user.inventory[i] == 't')
        {
            g_Console.writeToBuffer(59, 8 + i , user.inventoryitems[i] , 10);
        }
    }
    
}

//Points
void point( player & user , Console & g_Console )
{
    g_Console.writeToBuffer(61, 15 , "Points:" , 10);

    if (user.TTaken == 1)
    {
        if (user.points == 1)
        {
            g_Console.writeToBuffer(61, 16 , "1" , 10);
        }
        if (user.points == 2)
        {
            g_Console.writeToBuffer(61, 16 , "2" , 10);
        }
        if (user.points == 3)
        {
            g_Console.writeToBuffer(61, 16 , "3" , 10);
        }
        if (user.points == 4)
        {
            g_Console.writeToBuffer(61, 16 , "4" , 10);
        }
    }
    else
    {
        g_Console.writeToBuffer(61, 16 , "0" , 10);
    }
}

//Selector
void selector( player & user , Console & g_Console )
{
    g_Console.writeToBuffer(59, 12 , "Item selected: ", 10);

    if (user.inventory[user.select] == 't')
    {
        g_Console.writeToBuffer(59, 13 , user.inventoryitems[user.select] , 10);
    }
    else
    {
        g_Console.writeToBuffer(59, 13 , "No item" , 10);
    }
}

//Read Log
void readLog ( Console & g_Console )
{
    std::fstream log ("log.txt");

    string line;

    g_Console.writeToBuffer(58, 17 , "Notifications:" , 10);

    int i = 0;
    if (log.is_open())
    {
        while (getline (log,line))
        {
            g_Console.writeToBuffer(51, 25 - i , line , 10);
            ++i;
            if(i == 5)
            {
                i = 0;
            }
        }
        log.close();
    }

    /*for (int i = 0; i <= 5; ++i)
    {
        getline (log, line);
        g_Console.writeToBuffer(51, 18 + i , line , 10);

        if (i == 5)
        {
            i = 0;
        }
    }*/
}

//Write Log
void writeLog ( string line , double time) 
{
    std::fstream log ("log.txt", std::fstream::app);

    log << line << "@" << time << "\n";
    log.close();
}