#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"
#include <sstream>

// item1 is boost, item2 is explosive, item3 is invisible potion

void item1up(PMAP MapCollision, COORD &charLocation, player&user, double currentTime, Console & g_Console, double &boostcd)
{
	if(currentTime >= boostcd)
	{
	    bool stop = 0;
	    int count = 0;
	    for(; count <= 3; ++count)
	    {
		    if (MapCollision->data[charLocation.Y - count][charLocation.X] == 'W')
		    {
			    stop = 1;
			    break;
		    }
		    if (user.switch1 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'X')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(user.switch2 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'Y')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(user.switch3 == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'Z')
			    {
				    stop = 1;
				    break;
			    }
		    }
		    if(user.Cexplode == 0)
		    {
			    if(MapCollision->data[charLocation.Y - count][charLocation.X] == 'C')
			    {
				    stop = 1;
				    break;
			    }
		    }
	    }
	    if (stop == 0)
	    {
		    charLocation.Y -= 3;
		    boostcd = currentTime + 3;
	    }
	    else
	    {
		    charLocation.Y -= count - 1;
		    boostcd = currentTime + 3;
	    }
	}
}
void item1left(PMAP MapCollision, COORD &charLocation,player&user,double currentTime, Console & g_Console, double &boostcd)
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
			if (user.switch1 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'X')
				{
					stop = 1;
					break;
				}
			}
			if(user.switch2 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'Y')
				{
					stop = 1;
					break;
				}
			}
			if(user.switch3 == 0)
			{
				if(MapCollision->data[charLocation.Y][charLocation.X - count] == 'Z')
				{
					stop = 1;
					break;
				}
			}
			if(user.Cexplode == 0)
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
void item1down(PMAP MapCollision, COORD &charLocation,player&user, double currentTime, Console & g_Console, double &boostcd)
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
		if (user.switch1 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'X')
			{
				stop = 1;
				break;
			}
		}
		if(user.switch2 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'Y')
			{
				stop = 1;
				break;
			}
		}
		if(user.switch3 == 0)
		{
			if(MapCollision->data[charLocation.Y + count][charLocation.X] == 'Z')
			{
				stop = 1;
				break;
			}
		}
		if(user.Cexplode == 0)
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
void item1right(PMAP MapCollision, COORD &charLocation,player&user, double currentTime, Console & g_Console, double &boostcd)
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
		if (user.switch1 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'X')
			{
				stop = 1;
				break;
			}
		}
		if(user.switch2 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'Y')
			{
				stop = 1;
				break;
			}
		}
		if(user.switch3 == 0)
		{
			if(MapCollision->data[charLocation.Y][charLocation.X + count] == 'Z')
			{
				stop = 1;
				break;
			}
		}
		if(user.Cexplode == 0)
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

void item2(player&user)
{
	user.Cexplode = 1;
	user.bomb = 0;
}

void item3(player&user,SGameChar icon, double currentTime, double &invisExp)
{
	invisExp = currentTime + 5;
	user.invispot = 0;
	user.invis = 1;
}

void medpack(player&user)
{
	if (user.health < 4)
	{
		user.health += 2;
		user.MedsTaken = 1;
	}
	else if (user.health == 4)
	{
		user.health += 1;
		user.MedsTaken = 1;
	}
}