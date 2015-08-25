#ifndef _AI_H
#define _AI_H

#include "Framework\console.h"
#include "map.h"

void mobmove(COORD charLocation, COORD &mob, double time, Console &console, PMAP map);

#endif // _AI_H