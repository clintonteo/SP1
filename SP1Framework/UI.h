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
    char inventory[6];
    vector<string>inventoryitems;
	bool switch1;
	bool switch2;
	bool switch3;
	bool TTaken;
    int points;
    int select;
	bool boost;
	bool bomb;
	bool Cexplode;
	bool strength;
	bool KTaken;
	bool invis;
	bool LTaken;
	bool MTaken;
	COORD block;
    int timer;
	double timelimit;
};

void timer (double g_dElapsedTime, Console & g_Console, player & user);
void lives (player & user, Console & g_Console);
void divider(Console & g_Console);
//void damagetaken ( player user, bool damage );
void renderInventory ( player & user , Console & g_Console );
void point( player & user , Console & g_Console );
void selector( player & user , Console & g_Console);
void background( Console & g_Console );
void readLog ( Console & g_Console );
void writeLog ( string line , double time);

#endif // _UI_H