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
    //string inventory0;
    //string inventory1;
    //string inventory2;
    //string inventory3;
    //string inventory4;
    //string inventory5;
    vector<string>inventoryitems;
	bool switch1;
	bool switch2;
	bool switch3;
	bool TTaken;
    int points;
    int select;
	bool boost;
	bool ITaken;
	bool explode;
	bool JTaken;
	bool strength;
	bool KTaken;
	bool invis;
	bool LTaken;
	COORD block;
};

void timer (double g_dElapsedTime);
void lives (player & user);
void divider();
//void damagetaken ( player user, bool damage );
void renderInventory ( player & user );
void point( player & user );
void selector( player & user );

#endif // _UI_H