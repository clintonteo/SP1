#ifndef _ITEM_H
#define _ITEM_H

#include "map.h"
#include "item.h"
#include "game.h"

void item1up(PMAP MapCollision, COORD &charLocation,player&user,double currentTime);
void item1left(PMAP MapCollision, COORD &charLocation,player&user,double currentTime);
void item1down(PMAP MapCollision, COORD &charLocation,player&user,double currentTime);
void item1right(PMAP MapCollision, COORD &charLocation,player&user,double currentTime);
void item2(player&user);
void item3();
void item4();

#endif //_ITEM_H