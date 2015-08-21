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
	bool ITaken;
	bool bomb;
	bool JTaken;
	bool Cexplode;
	bool strength;
	bool KTaken;
	bool invis;
	bool LTaken;
	COORD block;
    int timer;
};

void timer (double g_dElapsedTime, Console & g_Console);
void lives (player & user, Console & g_Console);
void divider(Console & g_Console);
//void damagetaken ( player user, bool damage );
void renderInventory ( player & user , Console & g_Console );
void point( player & user , Console & g_Console );
void selector( player & user , Console & g_Console);
void background( Console & g_Console );

#endif // _UI_H