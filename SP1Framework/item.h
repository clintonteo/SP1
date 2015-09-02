#ifndef _ITEM_H
#define _ITEM_H

#include "map.h"
#include "item.h"
#include "game.h"

void item1up(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd);
void item1left(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd);
void item1down(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd);
void item1right(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd);
void item2(player&user);
void item3(player&user,SGameChar icon, double currentTime, double &invisexp);
void medpack(player&user);

#endif //_ITEM_H