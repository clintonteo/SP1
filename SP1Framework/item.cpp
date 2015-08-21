#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"


void item1up(PMAP MapCollision, COORD &charLocation, player&user)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
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
	}
	if (stop == 0)
	{
		charLocation.Y -= 3;
	}
}
void item1left(PMAP MapCollision, COORD &charLocation,player&user)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
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
	}
	if (stop == 0)
	{
		charLocation.X -= 3;
	}
}
void item1down(PMAP MapCollision, COORD &charLocation,player&user)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
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
	}
	if (stop == 0)
	{
		charLocation.Y += 3;
	}
}
void item1right(PMAP MapCollision, COORD &charLocation,player&user)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
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
	}
	if (stop == 0)
	{
		charLocation.X += 3;
	}
}