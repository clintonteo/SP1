#ifndef _UI_H
#define _UI_H
#include <string>
using std::string;

struct player
{
    int lives;
    char inventory[6];
    string inventory0;
    string inventory1;
    string inventory2;
    string inventory3;
    string inventory4;
    string inventory5;
    int points;
    int select;
};

enum items
{
    item1 = 1,
    item2,
    item3,
    item4,
    item5,
    item6,
};

void timer (double g_dElapsedTime);
void lives (player & user);
void divider();
//void damagetaken ( player user, bool damage );
void renderInventory ( player & user );
void point( player & user );
void selector( player & user );

#endif // _UI_H