#include "AI.h"
#include "Framework\console.h"
#include "map.h"
#include "UI.h"

COORD moblastcoord;
int xqueue = 0;
int yqueue = 0;
bool first = 0;
const int moveY = 1;
const int moveX = 0;
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

	if(time - static_cast<int>(time) < 1 && time - static_cast<int>(time) > 0.4)
	{
		if(first == moveX) //Move X axis first
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
		}else if(first == moveY) //Move Y axis first
		{
			if(xqueue > 0 && yqueue == 0)
			{
				mob.X--;
				xqueue--;
			}
			if(xqueue < 0 && yqueue == 0)
			{
				mob.X++;
				xqueue++;
			}

			if(yqueue > 0)
			{
				mob.Y--;
				yqueue--;
			}else if(yqueue < 0)
			{
				mob.Y++;
				yqueue++;
			}
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
	if(time - static_cast<int>(time) < 0.4 && time - static_cast<int>(time) > 0.0 && mob.X == moblastcoord.X && mob.Y == moblastcoord.Y)
	{
	console.writeToBuffer(51, 18, "Im stuck, pls halp", 10);
	for(int i = 0; i < 5; ++i)
	{
		if(xqueue != 0)
		{
			break;
		}
		//Right Corner Stuck
		if(map->data[mob.Y][mob.X+1] == 'W' && map->data[mob.Y + 1][mob.X] == 'W')
		{
			for(int i = 1; i < 10; ++i)
			{
				if(map->data[mob.Y+1][mob.X-i] != 'W') //Check How much spaces to the left he must go to escape
				{
					//if(charLocation.Y < mob.Y)
					//{
					//	yqueue = 2;
					//	xqueue = i;
					//}else 
					//if(charLocation.Y > mob.Y)
					//{
						xqueue = i;
						yqueue = -2;
						first = moveX;
						writeLog("I'm going left then down to escape this corner", 10);
					//}
					break;
				}else if(map->data[mob.Y - i][mob.X+1] != 'W') //Check how much spaces to the top he must go to escape
				{
					yqueue = i;
					xqueue = -2;
					first = moveY;
					break;
				}
			}
		}
		//Left Bottom Stuck
		//Right Top Stuck
		if(map->data[mob.Y][mob.X + 1] == 'W' && map->data[mob.Y - 1][mob.X] == 'W')
		{
			for(int i=1; i < 10; ++i)
			{
				if(map->data[mob.Y+i][mob.X+1] != 'W')
				{
					yqueue = -i;
					xqueue = -2;
					first = moveY;
					break;
				}
			}
		}
		//Left Top Stuck
		if(map->data[mob.Y][mob.X - 1] == 'W' && map->data[mob.Y - 1][mob.X] == 'W')
		{
			for(int i=1; i < 10; ++i)
			{
				if(map->data[mob.Y+i][mob.X-1] != 'W')
				{
					yqueue = -i;
					xqueue = 2;
					first = moveY;
					break;
				}
			}
		}
		//Stuck between two empty spots on the X axis
		if((map->data[mob.Y][mob.X-1] == 'D' || map->data[mob.Y][mob.X-1] == ' ') && (map->data[mob.Y][mob.X+1] == ' ' || map->data[mob.Y][mob.X+1] == 'D'))
		{
			console.writeToBuffer(51, 19, "Im stuck, between two spaces", 10);
			//for(int i = 1; i < 10; ++i)
			//{
			//	if(charLocation.Y > mob.Y)
			//	{
			//		if(charLocation.X < mob.X) //check if the player is to the left
			//		{
			//			if(map->data[mob.Y+1][mob.X - i] != 'W') //Check if theres an exit to the bottom left
			//			{
			//				xqueue = i;
			//				yqueue = -2;
			//				//console.writeToBuffer(51, 19, "Im stuck, but i know where to go", 10);
			//				writeLog("I'm going left then down", 10);
			//				first = moveX;
			//				break;
			//			}
			//		}else if(charLocation.X > mob.X) //check if the player is to the right
			//		{						
			//			if(map->data[mob.Y+1][mob.X + i] != 'W') //Check if theres an exit to the bottom right
			//			{
			//				xqueue = -i;
			//				yqueue = -2;
			//				writeLog("I'm going right then down", 10);
			//				first = moveX;
			//				break;
			//			}
			//		}
			//		if(map->data[mob.Y+1][mob.X] == 'W')
			//		{
			//			console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
			//		}
			//	}else if(charLocation.Y < mob.Y)
			//	{
			//		if(map->data[mob.Y-1][mob.X - i] != 'W') //Check if theres an exit to the top left
			//		{
			//			xqueue = i;
			//			yqueue = 2;
			//			first = moveX;
			//			writeLog("I'm going left then above", 10);
			//			break;
			//		}else if(map->data[mob.Y-1][mob.X + i] != 'W') //Check if theres an exit to the top right
			//		{
			//			xqueue = -i;
			//			yqueue = 2;
			//			writeLog("I'm going left then above", 10);
			//			first = moveX;
			//			break;
			//		}
			//		if(map->data[mob.Y-1][mob.X] == 'W')
			//		{
			//			console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
			//		}
			//	}
			//}
			if(charLocation.X < mob.X && map->data[mob.Y][mob.X - 1] != 'W') //if player is on the left of the mob
			{
				writeLog("I'm going up one space", 10);
				int steps = 0;
				while(map->data[mob.Y][mob.X - steps] != 'W')
				{
					steps++;
					if(charLocation.X == mob.X - steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
					steps--;
				}
				xqueue = steps;
				first = moveX;
			}else if(charLocation.X > mob.X && map->data[mob.Y][mob.X + 1] != 'W') //if player is on th right of the mob
			{
				int steps = 0;
				while(map->data[mob.Y][mob.X + steps] != 'W')
				{
					steps++;
					if(charLocation.X == mob.X + steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
					steps--;
				}
				xqueue = -steps;
				//writeLog("I'm going down one space", 10);
				first = moveX;
			}
		}else if((map->data[mob.Y-1][mob.X] == 'D' || map->data[mob.Y-1][mob.X] == ' ') && (map->data[mob.Y+1][mob.X] == ' ' || map->data[mob.Y+1][mob.X] == 'D'))
		{
			console.writeToBuffer(51, 19, "Im stuck, between two Y spaces", 10);
			//for(int i = 1; i < 10; ++i)
			//{
			//	if(charLocation.X > mob.X) //If player is to the right
			//	{
			//		if(map->data[mob.Y-i][mob.X - 1] != 'W') //Check if theres an exit to the bottom left
			//		{
			//			yqueue = i;
			//			xqueue = 2;
			//			console.writeToBuffer(51, 19, "Im stuck, but i know where to go", 10);
			//			first = moveY;
			//			break;
			//		}else if(map->data[mob.Y+i][mob.X - 1] != 'W') //Check if theres an exit to the top left
			//		{
			//			yqueue = -i;
			//			xqueue = 2;
			//			first = moveY;
			//			break;
			//		}else if(map->data[mob.Y-i][mob.X + 1] != 'W') //Check if theres an exit to the bottom right
			//		{
			//			yqueue = i;
			//			xqueue = -2;
			//			first = moveY;
			//			break;
			//		}else if(map->data[mob.Y+i][mob.X + 1] != 'W') //Check if theres an exit to the top right
			//		{
			//			yqueue = -i;
			//			xqueue = -2;
			//			first = moveY;
			//			break;
			//		}
			//		if(map->data[mob.Y+1][mob.X] == 'W')
			//		{
			//			console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
			//		}
			//	}//}else if(charLocation.X < mob.X) //If player is to the left
			//	//{
			//	//	if(map->data[mob.Y+i][mob.X - 1] != 'W') //Check if theres an exit to the top left
			//	//	{
			//	//		xqueue = 2;
			//	//		yqueue = - i;
			//	//		first = moveY;
			//	//		console.writeToBuffer(51, 19, "Im stuck, but i know where to go", 10);
			//	//		break;
			//	//	}else if(map->data[mob.Y - i][mob.X + 1] != 'W') //Check if theres an exit to the top right
			//	//	{
			//	//		xqueue = -2;
			//	//		yqueue = i;
			//	//		first = moveY;
			//	//		break;
			//	//	}
			//	//	if(map->data[mob.Y-1][mob.X] == 'W')
			//	//	{
			//	//		console.writeToBuffer(51, 19, "Im stuck, theres a wall infront of me ", 10);
			//	//	}
			//	//}
			//}
			if(charLocation.Y < mob.Y && map->data[mob.Y - 1][mob.X] != 'W') //if player is above the mob
			{
				writeLog("I'm going up one space", 10);
				int steps = 0;
				while(map->data[mob.Y-steps][mob.X] != 'W')
				{
					steps++;
					if(charLocation.Y == mob.Y -steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
				steps--;
				}
				yqueue = steps;
				first = moveY;
			}else if(charLocation.Y > mob.Y && map->data[mob.Y + 1][mob.X] != 'W') //if player is below the mob
			{
				int steps = 0;
				while(map->data[mob.Y+steps][mob.X] != 'W')
				{
					steps++;
					if(charLocation.Y == mob.Y+steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
				steps--;
				}
				yqueue = -steps;
				writeLog("I'm going down one space", 10);
				first = moveY;
			}
		}
		if(mob.Y == charLocation.Y)
		{
			console.writeToBuffer(51, 9, "I am not chasing u :(", 10);
		}
	}
	}else
	{
		console.writeToBuffer(51,18,cord, 10);
	}
}