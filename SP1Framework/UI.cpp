#include <iostream>

#include "UI.h"
#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::cin;
// UI THINGY

vector<int>highscorePoints;
vector<string>highscoreNames;
vector<string>highscore;

int firstLine = 0;

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
    g_Console.writeToBuffer(54, 3, "Time Limit: ", 10);

    std::ostringstream strs;
    strs << user.timelimit; 
    string timelimit = strs.str();
    timelimit += " secs";
    g_Console.writeToBuffer(66, 3, timelimit, 10);

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

            if (g_dElapsedTime >= boostcd && user.boost == 1 && user.inventoryitems[user.select] == "Boost")
            {
                for (int find_boost = 0; find_boost <  user.inventoryitems.size(); ++find_boost)
                {
                    if (user.inventoryitems[find_boost] == "Boost")
                    {
                        g_Console.writeToBuffer(62, 10 + find_boost , " (Ready)" , 10);
                    }
                }
            }
        }

        /*if (g_dElapsedTime >= boostcd && user.boost == 1 && user.inventoryitems[user.select] == "Boost")
        {
            g_Console.writeToBuffer(62, 10 + i , "(R)" , 10);
        }*/
    }
    
}

//Points / Treasure
void point( player & user , Console & g_Console )
{
    g_Console.writeToBuffer(59, 16 , "Treasures:" , 10);

    for (int TreasureCheck = 0; TreasureCheck <= 4; ++TreasureCheck)
    {
        if (user.points == TreasureCheck)
        {
            std::ostringstream Treasure;
            Treasure << TreasureCheck; 
            string final = Treasure.str();

            g_Console.writeToBuffer(70, 16, final, 10);
        }
    }

}

//Calc. Final Score
void calculateFinal ( player & user , double Endtime )
{
    user.final_score = 0;
    if (user.stage1 == 1)
    {
        user.final_score += 1000;
        for (int time_score = 0; time_score <= (user.timelimit - Endtime); time_score += 60)
        {
            user.final_score += 50;
        }

        if (user.stage2 == 1)
        {
            user.final_score += 1000;
            for (int time_score = 0; time_score <= (user.timelimit - Endtime); time_score += 60)
            {
                user.final_score += time_score;
            }
            if (user.stage3 == 1)
            {
                user.final_score += 1000;
                for (int time_score = 0; time_score <= (user.timelimit - Endtime); time_score += 60)
                {
                    user.final_score += time_score;
                }
            }

        }
    }

    user.final_score += (user.points*500);
	if(user.difficulty == 3)
		user.final_score *=0.5;
	else if(user.difficulty == 1)
		user.final_score *=1.5;
	else if(user.difficulty == 2)
		user.final_score *= 2;
}

//Final Score
void finalscore( Console & g_Console , player & user , double Endtime , COORD c )
{
    calculateFinal ( user , Endtime);

    std::ostringstream strs;
    strs << user.final_score; 
    string final = strs.str();

    g_Console.writeToBuffer(c, final, 0xf9);
}

//Selector
void selector( player & user , Console & g_Console )
{
    g_Console.writeToBuffer(59, 13 , "Item selected: ", 10);

    if (user.inventory[user.select] == 't')
    {
        g_Console.writeToBuffer(59, 14 , user.inventoryitems[user.select] , 10);
    }
    else
    {
        g_Console.writeToBuffer(59, 14 , "No item" , 10);
    }
}

//Read Log
void readLog ( Console & g_Console , double g_dElapsedTime)
{
    vector<string>logText;
    std::fstream log ("log.txt");

    string line;

    g_Console.writeToBuffer(58, 17 , "Notifications:" , 10);
    g_Console.writeToBuffer(51, 18 , "-----------------------------" , 10);

    int i = 0;
    if (log.is_open())
    {
        while (getline (log,line))
        {
            logText.push_back(line);

            /*g_Console.writeToBuffer(52, 23 - i , line , 10);
            ++i;

            if(i == 5)
            {
                i = 0;
            }*/ 
        }
        log.close();
    }
   
    for(int counter = 0; ( counter + firstLine ) < logText.size(); ++counter)
    {
        g_Console.writeToBuffer(52, 23 - counter , logText[counter + firstLine] , 10);

        if (counter == 5)
        {
            counter = -1;
            ++firstLine;
        }
    }
 /* std::ostringstream strs;
    strs << logText.size();
    string str;
    str = strs.str();

    g_Console.writeToBuffer(52, 25, str, 10);*/
}

//Write Log
void writeLog ( string line , double time) 
{
    std::fstream log ("log.txt", std::fstream::app);

    log << line << " @" << static_cast<int>(time) << "secs" << "\n";

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

//Highscore Read & Write
void highscoreWrite ( player & user , Console & g_Console ) // NEW HIGHSCORE
{
    string line;
    string name;
    int score = 0;

    std::fstream HighScore ("highscore.txt", std::fstream::app);

    if(HighScore.good())
	{
        HighScore << "\n" << user.name << " " << user.final_score;
    }

    HighScore.close();

    std::fstream HighScoreArrange ("highscore.txt");
    
    while (HighScoreArrange.good())
    {
        HighScoreArrange >> name >> score;
        highscorePoints.push_back(score);
        highscoreNames.push_back(name);
    }
    HighScoreArrange.close();

    std::ofstream T_OldHighscore;
    T_OldHighscore.open("highscore.txt", std::fstream::trunc);
    T_OldHighscore.close();

    for (int Counter = 0; Counter < highscorePoints.size(); ++Counter)
    {
        for (int SecondCounter = Counter + 1; SecondCounter < highscorePoints.size(); ++SecondCounter)
        {
            if (highscorePoints[SecondCounter] >= highscorePoints[Counter])
            {
                int temp = highscorePoints[Counter];
                highscorePoints[Counter] = highscorePoints[SecondCounter];
                highscorePoints[SecondCounter] = temp;

                string tempName = highscoreNames[Counter];
                highscoreNames[Counter] = highscoreNames[SecondCounter];
                highscoreNames[SecondCounter] = tempName;
            }
        }
    }

    std::fstream HighScoreFinal ("highscore.txt", std::fstream::app);
    if(HighScoreFinal.good())
	{
        for (int counter = 0; counter < highscorePoints.size(); ++counter)
        {
            HighScoreFinal << highscoreNames[counter] << " " << highscorePoints[counter] << "\n";
        }
    }
    HighScoreFinal.close();
}
void highscoreRead ( player & user , Console & g_Console )
{
    std::fstream highscore ("highscore.txt");
    //highscore.open("highscore.txt");

    string line;

    int i = 1;

    g_Console.writeToBuffer(30, 15 , "LEADERBOARDS" , 0xf9);

    if (highscore.is_open())
    {  
        while (getline (highscore,line))
        {
            std::ostringstream strs;
            strs << i;
            string rank = strs.str();
            g_Console.writeToBuffer(20, 15 + i , rank , 0xf9);
            g_Console.writeToBuffer(30, 15 + i , line , 0xf9);
            ++i;
            if(i == 10)
            {
                break;
            }
        }
        highscore.close();
    }
}
void highscoreBoard ( player & user , Console & g_Console )
{
    std::fstream highscore ("highscore.txt");
    //highscore.open("highscore.txt");

    string line;

    int i = 1;

    g_Console.writeToBuffer(30, 5 , "LEADERBOARDS" , 0xfc);

    if (highscore.is_open())
    {  
        while (getline (highscore,line))
        {
            std::ostringstream strs;
            strs << i;
            string rank = strs.str();
            g_Console.writeToBuffer(20, 7 + i , rank , 0xf9);
            g_Console.writeToBuffer(30, 7 + i , line , 0xf9);
            ++i;
            if(i == 10)
            {
                break;
            }
        }
        highscore.close();
    }
}

// Check if name already used. <--IN PROGRESS-->
void checkName( player & user , Console & g_Console ) 
{
    std::fstream highscoreCheck ("highscore.txt");

    string name;
    int score = 0;

    while ( highscoreCheck.good() )
    {
        highscoreCheck >> name >> score;
        if (name == user.name && name.size() > 0 && user.name.size() > 0)
        {
            g_Console.writeToBuffer(30, 16 , "CURRENT name taken. Please change." , 0xf9);
            user.samename = 1;
        }
    }
    highscoreCheck.close();
}
