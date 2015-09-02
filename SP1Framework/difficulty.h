#ifndef _DIFFICULTY_H
#define _DIFFICULTY_H

#include "UI.h"
#include "game.h"
#include "AI.h"

void startGame(player&user,int &range,bool &blind);
void addTime(player&user);
void trapdmg(player&user);
double monSpd(player&user, mobData&mobD);

#endif //_DIFFICULTY_H