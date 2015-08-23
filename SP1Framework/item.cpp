#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"


void item1up(PMAP MapCollision, COORD &charLocation, player&user)
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
		/*
		if (MapCollision->data[charLocation.Y - count][charLocation.X] == 'D')
		{
			user.lives -= 1;
		}*/
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
		user.bcd = 11;
	}
	else
	{
		charLocation.Y -= count - 1;
		user.bcd = 11;
	}
}
void item1left(PMAP MapCollision, COORD &charLocation,player&user)
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
		/*
		if (MapCollision->data[charLocation.Y][charLocation.X - count] == 'D')
		{
			user.lives -= 1;
		}*/
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
		user.bcd = 11;
	}
	else
	{
		charLocation.X -= count - 1;
		user.bcd = 11;
	}
}
void item1down(PMAP MapCollision, COORD &charLocation,player&user)
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
		/*if (MapCollision->data[charLocation.Y + count][charLocation.X] == 'D')
		{
			user.lives -= 1;
		}*/
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
		user.bcd = 11;
	}
	else
	{
		charLocation.Y += count - 1;
		user.bcd = 11;
	}
}
void item1right(PMAP MapCollision, COORD &charLocation,player&user)
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
		/*
		if (MapCollision->data[charLocation.Y][charLocation.X + count] == 'D')
		{
			user.lives -= 1;
		}*/
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
		user.bcd = 11;
	}
	else
	{
		charLocation.X += count - 1;
		user.bcd = 11;
	}
}

void item2(player&user)
{
	user.Cexplode = 1;
	user.bomb--;
}

void item3()
{
	//blockp(g_sChar.m_cLocation, blocks, lastknown, range, g_Console);
}