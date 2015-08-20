#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"

void item1up(PMAP MapCollision, COORD &charLocation)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y - count][charLocation.X] == 'W' || MapCollision->data[charLocation.Y - count][charLocation.X] == 'X' || MapCollision->data[charLocation.Y - count][charLocation.X] == 'Y' || MapCollision->data[charLocation.Y - count][charLocation.X] == 'Z')
		{
			stop = 1;
			break;
		}
	}
	if (stop == 0)
	{
		charLocation.Y -= 3;
	}
}
void item1left(PMAP MapCollision, COORD &charLocation)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y][charLocation.X - count] == 'W' || MapCollision->data[charLocation.Y][charLocation.X - count] == 'X' || MapCollision->data[charLocation.Y][charLocation.X - count] == 'Y' || MapCollision->data[charLocation.Y][charLocation.X - count] == 'Z')
		{
			stop = 1;
			break;
		}
	}
	if (stop == 0)
	{
		charLocation.X -= 3;
	}
}
void item1down(PMAP MapCollision, COORD &charLocation)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y + count][charLocation.X] == 'W' || MapCollision->data[charLocation.Y + count][charLocation.X] == 'X' || MapCollision->data[charLocation.Y + count][charLocation.X] == 'Y' || MapCollision->data[charLocation.Y + count][charLocation.X] == 'Z')
		{
			stop = 1;
			break;
		}
	}
	if (stop == 0)
	{
		charLocation.Y += 3;
	}
}
void item1right(PMAP MapCollision, COORD &charLocation)
{
	bool stop = 0;
	for(int count = 0; count <= 3; ++count)
	{
		if (MapCollision->data[charLocation.Y][charLocation.X + count] == 'W' || MapCollision->data[charLocation.Y][charLocation.X + count] == 'X' || MapCollision->data[charLocation.Y][charLocation.X + count] == 'Y' || MapCollision->data[charLocation.Y][charLocation.X + count] == 'Z')
		{
			stop = 1;
			break;
		}
	}
	if (stop == 0)
	{
		charLocation.X += 3;
	}
}