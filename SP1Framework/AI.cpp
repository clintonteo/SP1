#include "AI.h"
#include "Framework\console.h"
#include "map.h"

COORD moblastcoord;
int xqueue = 0;
int yqueue = 0;
void mobmove(COORD charLocation, COORD &mob, double time, Console &console, PMAP map)
{
	double Xdifference = charLocation.X - mob.X;
	Xdifference = sqrt(Xdifference*Xdifference); //make it positive
	double Ydifference = charLocation.Y - mob.Y;
	Ydifference = sqrt(Ydifference*Ydifference);
	char x;
	char y;
	char xlast;
	char ylast;

	string cord;

	int timer = time;

	if(timer % 2 == 0)
	{
	if(xqueue > 0)
	{
		mob.X--;
		xqueue--;
	}
	if(xqueue < 0)
	{
		mob.X++;
		xqueue++;
	}

	if(yqueue > 0 && xqueue == 0)
	{
		mob.Y--;
		yqueue--;
	}else if(yqueue < 0 && xqueue == 0)
	{
		mob.Y++;
		yqueue++;
	}	
	//Movement of AI
	if(Xdifference > Ydifference && xqueue == 0 && yqueue==0)
	{
		if(charLocation.X > mob.X)
		{
			if(map->data[mob.Y][mob.X+1] != 'W')
			{
			mob.X++;
			}
		}else if(charLocation.X < mob.X)
		{
			if(map->data[mob.Y][mob.X-1] != 'W')
			{
			mob.X--;
			}
		}
	}else if(Ydifference > Xdifference && xqueue == 0 && yqueue==0)
	{
		if(charLocation.Y > mob.Y)
		{
			if(map->data[mob.Y+1][mob.X] != 'W')
			{
				mob.Y++;
			}
		}else if(charLocation.Y < mob.Y)
		{
			if(map->data[mob.Y-1][mob.X] != 'W')
			{
				mob.Y--;
			}
		}
	}else if(Xdifference == Ydifference && xqueue == 0 && yqueue==0)
	{
		if((charLocation.Y > mob.Y) && (charLocation.X > mob.X))
		{
			if(map->data[mob.Y+1][mob.X+1] != 'W')
			{
				mob.Y++;
				mob.X++;
			}
		}else if((charLocation.Y < mob.Y) && (charLocation.X < mob.X))
		{
			if(map->data[mob.Y-1][mob.X-1] != 'W')
			{
				mob.Y--;
				mob.X--;
			}
		}else if((charLocation.Y < mob.Y) && (charLocation.X > mob.X))
		{
			if(map->data[mob.Y-1][mob.X+1] != 'W')
			{
				mob.Y--;
				mob.X++;
			}
		}else if((charLocation.Y > mob.Y) && (charLocation.X < mob.X))
		{
			if(map->data[mob.Y+1][mob.X-1] != 'W')
			{
				mob.Y++;
				mob.X--;
			}
		}
	}
	}
	console.writeToBuffer(mob,"M",10);
	x = mob.X + 48;
	cord += x;
	y = mob.Y +48;
	cord += " ";
	cord += y;
	xlast = moblastcoord.X + 48;
	ylast = moblastcoord.Y + 48;
	cord += " Last: ";
	cord += xlast;
	cord += " ";
	cord += ylast;
	if(timer %  2 == 1)
	{
		moblastcoord = mob;
	}
	if(timer % 2 == 0 && mob.X == moblastcoord.X && mob.Y == moblastcoord.Y)
	{
	console.writeToBuffer(51, 18, "Im stuck, pls halp", 10);
	for(int i = 0; i < 5; ++i)
	{
		if(xqueue != 0)
		{
			break;
		}
		//Right Bottom Stuck
		if(map->data[mob.Y][mob.X+1] == 'W')
		{
			for(int i = 1; i < 10; ++i)
			{
				if(map->data[mob.Y+1][mob.X-i] != 'W')
				{
					if(charLocation.Y < mob.Y)
					{
						yqueue = 2;
						xqueue = i;
					}else if(charLocation.Y > mob.Y)
					{
						xqueue = i;
						yqueue = -2;
					}
					break;
				}
			}
		}
		//Left Bottom Stuck
		//if(map->data[mob.Y][mob.X-1] == 'W')
		//{
		//	for(int i = 0; i < 5; ++i)
		//	{
		//		if(map->data[mob.Y+1][mob.X+i] != 'W' || map->data[mob.Y-1][mob.X+i] != 'W')
		//		{
		//			if(charLocation.Y < mob.Y)
		//			{
		//				mob.Y--;
		//				mob.X-=i;
		//			}else if(charLocation.Y > mob.Y)
		//			{
		//				mob.Y++;
		//				mob.X-=i;
		//			}
		//		}
		//	}
		//}
		//Right Top Stuck
		//Left Top Stuck
		//Stuck between two empty spots
		if((map->data[mob.Y][mob.X-1] == 'D' || map->data[mob.Y][mob.X-1] == ' ') && (map->data[mob.Y][mob.X+1] == ' ' || map->data[mob.Y][mob.X+1] == 'D'))
		{
			console.writeToBuffer(51, 19, "Im stuck, between two spaces", 10);
			for(int i = 1; i < 10; ++i)
			{
				if(charLocation.Y > mob.Y)
				{
					if(map->data[mob.Y+1][mob.X - i] != 'W') //Check if theres an exit to the bottom left
					{
						xqueue = i;
						yqueue = -2;
						console.writeToBuffer(51, 19, "Im stuck, but i know where to go", 10);
						break;
					}else if(map->data[mob.Y+1][mob.X + i] != 'W') //Check if theres an exit to the bottom right
					{
						xqueue = -i;
						yqueue = -2;
						break;
					}
					if(map->data[mob.Y+1][mob.X] == 'W')
					{
						console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
					}
				}else if(charLocation.Y < mob.Y)
				{
					if(map->data[mob.Y-1][mob.X - i] != 'W') //Check if theres an exit to the top left
					{
						xqueue = i;
						yqueue = 2;
						console.writeToBuffer(51, 19, "Im stuck, but i know where to go", 10);
						break;
					}else if(map->data[mob.Y-1][mob.X + i] != 'W') //Check if theres an exit to the top right
					{
						xqueue = -i;
						yqueue = 2;
						break;
					}
					if(map->data[mob.Y-1][mob.X] == 'W')
					{
						console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
					}
				}
			}
		}
	}
	}else
	{
		console.writeToBuffer(51,18,cord, 10);
	}
}