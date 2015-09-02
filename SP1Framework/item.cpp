#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"
#include <sstream>

// item1 is boost, item2 is explosive, item3 is invisible potion


void item1up(PMAP MapCollision, COORD &charLocation, player&user, double currentTime, Console & g_Console, double &boostcd, mapBool & mapUpdate) // Boost up
{
	if(currentTime >= boostcd)// check for cooldown
	{
	    bool stop = 0;
	    int count = 0;
	    for(; count <= 3; ++count)// detects if any impassable obstacle is in the way
	    {
		    if (MapCollision->data[charLocation.Y - count][charLocation.X] == 'W')
		    {
			    stop = 1;
			    break;
		    }
		    if (mapUpdate.switch1 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'X')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(mapUpdate.switch2 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'Y')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(mapUpdate.switch3 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'Z')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(mapUpdate.Cexplode == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'C')
			    {
				    stop = 1;
				    break;
			    }
		    }
	    }
	    if (stop == 0)// boosts fully if nothing blocking is detected
	    {
		    charLocation.Y -= 3;
		    boostcd = currentTime + 3;
	    }
	    else // boosts player till before the tile that is blocking the user's boost range
	    {
		    charLocation.Y -= count - 1;
		    boostcd = currentTime + 3;
	    }
	}
}

void item1left(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate)// Boost left
{
	if(currentTime >= boostcd)
	{
		bool stop = 0;
		int count = 0;
		for(; count <= 3; ++count)
		{
			if (MapCollision->data[charLocation.Y][charLocation.X - count] == 'W')
			{
				stop = 1;
				break;
			}
			if (mapUpdate.switch1 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'X')
				{
					stop = 1;
					break;
				}
			}
			if(mapUpdate.switch2 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'Y')
				{
					stop = 1;
					break;
				}
			}
			if(mapUpdate.switch3 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'Z')
				{
					stop = 1;
					break;
				}
			}
			if(mapUpdate.Cexplode == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'C')
				{
					stop = 1;
					break;
				}
			}
	}
	if (stop == 0)
	{
		charLocation.X -= 3;
		boostcd = currentTime + 3;
	}
	else
	{
		charLocation.X -= count - 1;
		boostcd = currentTime + 3;
    }
	}
}
void item1down(PMAP MapCollision, COORD &charLocation,player&user, double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate)// Boost down
{
	if(currentTime >= boostcd)
	{
	bool stop = 0;
	int count = 0;
	for(; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y + count][charLocation.X] == 'W')
		{
			stop = 1;
			break;
		}
		if (mapUpdate.switch1 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'X')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.switch2 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'Y')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.switch3 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'Z')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.Cexplode == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'C')
			{
				stop = 1;
				break;
			}
		}
	}
	if (stop == 0)
	{
		charLocation.Y += 3;
		boostcd = currentTime + 3;
	}
	else
	{
		charLocation.Y += count - 1;
		boostcd = currentTime + 3;
	}
	}
}
void item1right(PMAP MapCollision, COORD &charLocation,player&user, double currentTime, Console & g_Console, double &boostcd , mapBool & mapUpdate)// Boost right
{
	if(currentTime >= boostcd)
	{
	bool stop = 0;
	int count = 0;
	for(; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y][charLocation.X + count] == 'W')
		{
			stop = 1;
			break;
		}
		if (mapUpdate.switch1 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'X')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.switch2 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'Y')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.switch3 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'Z')
			{
				stop = 1;
				break;
			}
		}
		if(mapUpdate.Cexplode == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'C')
			{
				stop = 1;
				break;
			}
		}
	}
	if (stop == 0)
	{
		charLocation.X += 3;
		boostcd = currentTime + 3;
    }
	else
	{
		charLocation.X += count - 1;
		boostcd = currentTime + 3;
	}
	}
}

void item2(player&user , mapBool & mapUpdate, PMAP MapCollision, COORD &charLocation) // Bomb
{
	if(MapCollision->data[charLocation.Y - 1][charLocation.X] == 'C')
	{
		mapUpdate.Cexplode = 1;
		user.bomb = 0;
	}
	else if(MapCollision->data[charLocation.Y + 1][charLocation.X] == 'C')
	{
		mapUpdate.Cexplode = 1;
		user.bomb = 0;
	}
	else if(MapCollision->data[charLocation.Y][charLocation.X - 1] == 'C')
	{
		mapUpdate.Cexplode = 1;
		user.bomb = 0;
	}
	else if(MapCollision->data[charLocation.Y][charLocation.X + 1] == 'C')
	{
		mapUpdate.Cexplode = 1;
		user.bomb = 0;
	}
}

void item3(player&user,SGameChar icon, double currentTime, double &invisExp) // Invisible potion
{
	invisExp = currentTime + 5;
	user.invispot = 0;
	user.invis = 1;
}

void medpack(player&user , mapBool & mapUpdate)// Medpack
{
	if (user.health < 4)
	{
		user.health += 2;
		mapUpdate.MedsTaken = 1;
	}
	else if (user.health == 4)// to prevent players having more than 5 health
	{
		user.health += 1;
		mapUpdate.MedsTaken = 1;
	}
}