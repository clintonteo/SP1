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
void timer(double g_dElapsedTime, Console & g_Console, player & user)
{
    //Timer
    g_Console.writeToBuffer(61, 1, "Timer: ", 10);

    renderFramerate();

    //Time Limit
    g_Console.writeToBuffer(52, 3, "Time Limit: ", 10);
    g_Console.writeToBuffer(64, 3, user.timelimit, 10);

    //Timer Notification
    if (user.timelimit - g_dElapsedTime <= 60 && user.timelimit - g_dElapsedTime >= 59.8)
    {
        writeLog("You have a minute left!", g_dElapsedTime);
    }
}
    

//Lives & Health
void lives( player & user, Console &g_Console )
{
	g_Console.writeToBuffer(61, 5, "Lives: ", 10);

    for (int count = 0; count < user.lives; ++count)
    {
		g_Console.writeToBuffer(55 + count*4, 6, "|<3|", 43);
    }

    g_Console.writeToBuffer(61, 7, "Health: ", 10);
    for (int count = 0; count < user.health; ++count)
    {
		g_Console.writeToBuffer(55 + count*4, 8, "|HP|", 43);
    }
}

//Render Inventory
void renderInventory( player & user , Console & g_Console , double &boostcd , double g_dElapsedTime )
{
    g_Console.writeToBuffer(59 , 9, "Inventory: ", 10);

    for (int i = 0; i < user.inventoryitems.size(); ++i)
    {
        if (user.inventory[i] == 't')
        {
            g_Console.writeToBuffer(57, 10 + i , user.inventoryitems[i] , 10);
        }

        if (g_dElapsedTime >= boostcd && user.boost == 1 /*&& boostcd != -1*/)
        {
            g_Console.writeToBuffer(62, 10 + i , "(R)" , 10);
            //boostcd = -1;
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
    g_Console.writeToBuffer(51, 18 , "-----------------------------" , 10);

    int i = 0;
    if (log.is_open())
    {
        while (getline (log,line))
        {
            g_Console.writeToBuffer(52, 23 - i , line , 10);
            ++i;
            if(i == 5)
            {
                i = 0;
                //g_Console.writeToBuffer(51, 23 - i ,  "----------------" , 10);
                /*std::fstream log ("log.txt", std::fstream::app);
                log << "\n";
                log.close();*/
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

    //Check for 5th line
    /*std::fstream checklog ("log.txt");
    string last_line;
    int num = 0;
    while (getline (checklog,last_line))
    {
        ++num; 
        if (num == 5)
        {
            std::fstream log ("log.txt", std::fstream::app);

            log << "-----------------------------";

            log.close();
        }
    }*/
}   