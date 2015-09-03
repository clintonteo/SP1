#ifndef _UI_H
#define _UI_H
#include <string>
#include "Framework\console.h"
#include <vector>

using std::string;
using std::vector;
struct player
{
	bool start;
    int lives;
    int health;
    vector<string>inventoryitems;
    int points; // Treasure
    double final_score; // Final Score
    int select;
	bool bomb; 
	bool invispot;  
	bool invis; // invis state
	COORD block;
	double timelimit;
	int difficulty;
    bool stage1;
    bool stage2;
    bool stage3;
    bool stage4;
    string name; //NAME
    bool gameover;
    bool wroteHighScore;
	char icon;
    bool samename;
	bool aniDone;
};

struct mapBool
{
    bool switch1; 
	bool switch2; 
	bool switch3; 
	bool TTaken; 
    bool boost; 
    bool bombtaken; 
	bool Cexplode; 
    bool invistaken; 
	bool MedsTaken; 
};

struct scoreboard
{
	int stage1;
	int stage2;
	int stage3;
	int stage4;
	bool pointcalcdone;
};

void timer (double g_dElapsedTime, Console & g_Console, player & user);
void lives (player & user, Console & g_Console);
void divider(Console & g_Console);
void renderInventory ( player & user , Console & g_Console , double &boostcd , double g_dElapsedTime , mapBool & map);
void point( player & user , Console & g_Console );
void selector( player & user , Console & g_Console);
void background( Console & g_Console );
void readLog ( Console & g_Console , double g_dElapsedTime );
void writeLog ( string line , double time);
void finalscore ( Console & g_Console , player & user , double Endtime, COORD c);
void calculateFinal ( player & user , double Endtime );
void highscoreWrite ( player & user , Console & g_Console );
void highscoreRead ( player & user , Console & g_Console );
void highscoreBoard ( player & user , Console & g_Console );
void checkName( player & user , Console & g_Console );
void animateScoreBoard(Console & console, player &user, scoreboard &aniScore, double time, double EndTime);

#endif // _UI_H