#ifndef _ITEM_H
#define _ITEM_H

#include "map.h"
#include "item.h"
#include "game.h"

void item1up(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate);
void item1left(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate);
void item1down(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate);
void item1right(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate);
void item2(player&user , mapBool & mapUpdate);
void item3(player&user,SGameChar icon, double currentTime, double &invisexp);
void medpack(player&user , mapBool & mapUpdate );

#endif //_ITEM_H