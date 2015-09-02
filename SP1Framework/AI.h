#ifndef _AI_H
#define _AI_H

#include "Framework\console.h"
#include "map.h"

struct mobData
{
	COORD MC;
	COORD lastMC;
	COORD direction;
	int xqueue;
	int yqueue;
	bool first;
	bool playerImmunity;
	double delay;
	double movedelay;
};

void mobmove(COORD &charLocation, mobData &mobD, double time, Console &console, PMAP map, player &user, bool blind, int range);
void spawnmob(std::vector<mobData> &mob);

#endif // _AI_H