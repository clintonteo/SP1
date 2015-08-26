#ifndef _UI_H
#define _UI_H
#include <string>
#include "Framework\console.h"
#include <vector>

using std::string;
using std::vector;
struct player
{
    int lives;
    int health;
    char inventory[6];
    vector<string>inventoryitems;
	bool switch1;
	bool switch2;
	bool switch3;
	bool TTaken;
    int points;
    int final_score;
    int select;
	bool boost;
	bool bomb;
	bool Cexplode;
	bool invispot;
	bool invis;
	bool invistaken;
	bool MedsTaken;
	COORD block;
	double timelimit;
	int difficulty;
    bool stage1;
    bool stage2;
    bool stage3;
    bool stage4;
};

void timer (double g_dElapsedTime, Console & g_Console, player & user);
void lives (player & user, Console & g_Console);
void divider(Console & g_Console);
//void damagetaken ( player user, bool damage );
void renderInventory ( player & user , Console & g_Console , double &boostcd , double g_dElapsedTime );
void point( player & user , Console & g_Console );
void selector( player & user , Console & g_Console);
void background( Console & g_Console );
void readLog ( Console & g_Console );
void writeLog ( string line , double time);
void finalscore ( Console & g_Console , player & user , COORD c, double Endtime);
void highscoreWrite ( player & user );
void highscoreRead ( player & user , Console & g_Console );

#endif // _UI_H