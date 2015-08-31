#include "AI.h"
#include "Framework\console.h"
#include "map.h"
#include "UI.h"

const int moveY = 1;
const int moveX = 0;
//PROBLEMS TO BE FIXED
//TOP LEFT TELEPORTS
//TOP RIGHT COLLISION BUG
void mobmove(COORD &charLocation, mobData &mobD, double time, Console &console, PMAP map, player &user, bool blind, int range)
{
	double Xdifference = charLocation.X - mobD.MC.X;
	Xdifference = sqrt(Xdifference*Xdifference); //make it positive
	double Ydifference = charLocation.Y - mobD.MC.Y;
	Ydifference = sqrt(Ydifference*Ydifference);
	char x;
	char y;
	char xlast;
	char ylast;

	string cord;

	int timer = time;

	//if(time - static_cast<int>(time) < 1 && time - static_cast<int>(time) > 0.4)
	if(timer % 2 == 0)
	{
		if(mobD.first == moveX) //Move X axis mobD.first
		{
			if(mobD.xqueue > 0)
			{
				mobD.MC.X--;
				mobD.xqueue--;
			}
			if(mobD.xqueue < 0)
			{
				mobD.MC.X++;
				mobD.xqueue++;
			}

			if(mobD.yqueue > 0 && mobD.xqueue == 0)
			{
				mobD.MC.Y--;
				mobD.yqueue--;
			}else if(mobD.yqueue < 0 && mobD.xqueue == 0)
			{
				mobD.MC.Y++;
				mobD.yqueue++;
			}
		}else if(mobD.first == moveY) //Move Y axis mobD.first
		{
			if(mobD.xqueue > 0 && mobD.yqueue == 0)
			{
				mobD.MC.X--;
				mobD.xqueue--;
			}
			if(mobD.xqueue < 0 && mobD.yqueue == 0)
			{
				mobD.MC.X++;
				mobD.xqueue++;
			}

			if(mobD.yqueue > 0)
			{
				mobD.MC.Y--;
				mobD.yqueue--;
			}else if(mobD.yqueue < 0)
			{
				mobD.MC.Y++;
				mobD.yqueue++;
			}
		}
	//Movement of AI
	if(Xdifference > Ydifference && mobD.xqueue == 0 && mobD.yqueue==0)
	{
		if(charLocation.X > mobD.MC.X)
		{
			if(map->data[mobD.MC.Y][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y][mobD.MC.X] == 'D')
			{
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y][mobD.MC.X+1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y][mobD.MC.X+1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y][mobD.MC.X+1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.X++;
			}
		}else if(charLocation.X < mobD.MC.X)
		{
			if(map->data[mobD.MC.Y][mobD.MC.X-1] == ' ' || map->data[mobD.MC.Y][mobD.MC.X-1] == 'D')
			{
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y][mobD.MC.X-1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y][mobD.MC.X-1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y][mobD.MC.X-1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.X--;
			}
		}
	}else if(Ydifference > Xdifference && mobD.xqueue == 0 && mobD.yqueue==0)
	{
		if(charLocation.Y > mobD.MC.Y)
		{
			if(map->data[mobD.MC.Y+1][mobD.MC.X] == ' ' && map->data[mobD.MC.Y+1][mobD.MC.X] != 'D')
			{
				mobD.MC.Y++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y++;
			}
		}else if(charLocation.Y < mobD.MC.Y)
		{
			if(map->data[mobD.MC.Y-1][mobD.MC.X] == ' ' || map->data[mobD.MC.Y-1][mobD.MC.X] == 'D')
			{
				mobD.MC.Y--;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y--;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y--;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y--;
			}
		}
	}else if(Xdifference == Ydifference && mobD.xqueue == 0 && mobD.yqueue==0)
	{
		if((charLocation.Y > mobD.MC.Y) && (charLocation.X > mobD.MC.X))
		{
			if(map->data[mobD.MC.Y+1][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y+1][mobD.MC.X+1] == 'D')
			{
				mobD.MC.Y++;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X+1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X+1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X+1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X++;
			}
			writeLog("Diagonal Down and Right",1);
		}else if((charLocation.Y < mobD.MC.Y) && (charLocation.X < mobD.MC.X))
		{
			if(map->data[mobD.MC.Y-1][mobD.MC.X-1] == ' ' || map->data[mobD.MC.Y-1][mobD.MC.X-1] == 'D')
			{
				mobD.MC.Y--;
				mobD.MC.X--;
			}else if (map->data[mobD.MC.Y-1][mobD.MC.X-1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X--;
			}else if (map->data[mobD.MC.Y-1][mobD.MC.X-1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X--;
			}else if (map->data[mobD.MC.Y-1][mobD.MC.X-1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X--;
			}
		}else if((charLocation.Y < mobD.MC.Y) && (charLocation.X > mobD.MC.X))
		{
			if(map->data[mobD.MC.Y-1][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y-1][mobD.MC.X+1] == 'D')
			{
				mobD.MC.Y--;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X+1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X+1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X++;
			}else if(map->data[mobD.MC.Y-1][mobD.MC.X+1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y--;
				mobD.MC.X++;
			}
		}else if((charLocation.Y > mobD.MC.Y) && (charLocation.X < mobD.MC.X))
		{
			if(map->data[mobD.MC.Y+1][mobD.MC.X-1] == ' ' || map->data[mobD.MC.Y+1][mobD.MC.X-1] == 'D')
			{
				mobD.MC.Y++;
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X-1] == 'X' && user.switch1 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X-1] == 'Y' && user.switch2 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X--;
			}else if(map->data[mobD.MC.Y+1][mobD.MC.X-1] == 'Z' && user.switch3 == 1)
			{
				mobD.MC.Y++;
				mobD.MC.X--;
			}
		}
	}
	}
	if(blind == 0)
	{
	console.writeToBuffer(mobD.MC,"M",10);
	}else if(blind == 1)
	{
		if((charLocation.X - range-1 < mobD.MC.X && charLocation.X + range+1 > mobD.MC.X) && (charLocation.Y - range-1 < mobD.MC.Y && charLocation.Y + range+1 > mobD.MC.Y))
		{
				console.writeToBuffer(mobD.MC,"M",10);
		}
	}
	if(timer %  2 == 1)
	{
		mobD.lastMC = mobD.MC;
	}
	//if(time - static_cast<int>(time) < 0.4 && time - static_cast<int>(time) > 0.0 && mobD.MC.X == mobD.lastMC.X && mobD.MC.Y == mobD.lastMC.Y)
	if(timer % 2 == 1 && mobD.MC.X == mobD.lastMC.X && mobD.lastMC.Y == mobD.MC.Y)
	{
	for(int i = 0; i < 5; ++i)
	{
		if(mobD.xqueue != 0)
		{
			break;
		}
		//Right Corner Stuck
		if(map->data[mobD.MC.Y][mobD.MC.X+1] == 'W' && map->data[mobD.MC.Y + 1][mobD.MC.X] == 'W')
		{
			for(int i = 1; i < 5; ++i)
			{
				if(map->data[mobD.MC.Y+1][mobD.MC.X-i] == ' ' || map->data[mobD.MC.Y+1][mobD.MC.X-i] == 'D') //Check How much spaces to the left he must go to escape
				{
						mobD.xqueue = i;
						mobD.yqueue = -2;
						mobD.first = moveX;
					break;
				}else if(map->data[mobD.MC.Y - i][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y - i][mobD.MC.X+1] == 'D') //Check how much spaces to the top he must go to escape
				{
					mobD.yqueue = i;
					mobD.xqueue = -2;
					mobD.first = moveY;
					break;
				}
			}
		}
		//Left Bottom Stuck
		if(map->data[mobD.MC.Y][mobD.MC.X-1] == 'W' && map->data[mobD.MC.Y+1][mobD.MC.X] == 'W')
		{
			for(int i = 1; i < 5; ++i)
			{
				if(map->data[mobD.MC.Y+1][mobD.MC.X + i] == ' ' || map->data[mobD.MC.Y+1][mobD.MC.X + i] == 'D')
				{
					mobD.xqueue = -i;
					mobD.yqueue = -2;
					mobD.first = moveX;
					break;
				}else if(map->data[mobD.MC.Y - i][mobD.MC.X - 1] == ' ' || map->data[mobD.MC.Y - i][mobD.MC.X - 1] == 'D')
				{
					mobD.yqueue = i;
					mobD.xqueue = 2;
					mobD.first = moveY;
					break;
				}
			}
		}
		//Right Top Stuck
		if(map->data[mobD.MC.Y][mobD.MC.X + 1] == 'W' && map->data[mobD.MC.Y - 1][mobD.MC.X] == 'W')
		{
			for(int i=1; i < 5; ++i)
			{
				if(map->data[mobD.MC.Y+i][mobD.MC.X] == 'W')
				{
					break;
				}
				if(map->data[mobD.MC.Y+i][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y+i][mobD.MC.X+1] == 'D')
				{
					mobD.yqueue = -i;
					for(int j=1; j<3;++j)
					{
						if(map->data[mobD.MC.Y+i][mobD.MC.X+j] == ' ' || map->data[mobD.MC.Y+i][mobD.MC.X+j] == 'D')
						{
							mobD.xqueue = -j;
							break;
						}
					}
					mobD.first = moveY;
					break;
				}else if(map->data[mobD.MC.Y-1][mobD.MC.X-i] == ' ' || map->data[mobD.MC.Y-1][mobD.MC.X-i] == 'D')
				{
					if(map->data[mobD.MC.Y][mobD.MC.X-i] == 'W')
					{
						break;
					}
					mobD.xqueue = i;
					for(int j=1;j<3;++j)
					{
						if(map->data[mobD.MC.Y-j][mobD.MC.X-i] == ' ' || map->data[mobD.MC.Y-j][mobD.MC.X-i] == 'D')
						{
							mobD.yqueue = j;
						}else{break;}
					}
				}
			}
		}
		//Left Top Stuck
		if(map->data[mobD.MC.Y][mobD.MC.X - 1] == 'W' && map->data[mobD.MC.Y - 1][mobD.MC.X] == 'W')
		{
			for(int i=1; i < 25; ++i)
			{
				if(mobD.MC.Y + i < map->nrow)
				{
					if(map->data[mobD.MC.Y +i][mobD.MC.X] == 'W')
					{
						break;
					}
					if(map->data[mobD.MC.Y+i][mobD.MC.X-1] == ' ' || map->data[mobD.MC.Y+i][mobD.MC.X-1] == 'D')
					{
						mobD.yqueue = -i;
						mobD.first = moveY;
						for(int j=1; j < 3; ++j)
						{
							if(map->data[mobD.MC.Y+i][mobD.MC.X-j] == ' ' || map->data[mobD.MC.Y+i][mobD.MC.X-j] == 'D')
							{
								mobD.xqueue = j;
								break;
							}
						}
						break;
					}
				}
				
				if(mobD.MC.X + i < map->ncol)
				{
					if(map->data[mobD.MC.Y][mobD.MC.X+i] == 'W')
					{
					break;
					}

						if(map->data[mobD.MC.Y-1][mobD.MC.X+i] == ' ' || map->data[mobD.MC.Y-1][mobD.MC.X+i] == 'D')
						{
							mobD.xqueue = -i;
							mobD.first = moveX;
							for(int j=1;j<3;++j)
							{
								if(map->data[mobD.MC.Y-j][mobD.MC.X+i] == ' ' || map->data[mobD.MC.Y-j][mobD.MC.X+i] == 'D')
								{
									mobD.yqueue = j;
									break;
								}
							}
							break;
						}
					
				}
			}
		}
		//Stuck between two empty spots on the X axis
		if((map->data[mobD.MC.Y][mobD.MC.X-1] == 'D' || map->data[mobD.MC.Y][mobD.MC.X-1] == ' ') && (map->data[mobD.MC.Y][mobD.MC.X+1] == ' ' || map->data[mobD.MC.Y][mobD.MC.X+1] == 'D'))
		{
			if(charLocation.X < mobD.MC.X && (map->data[mobD.MC.Y][mobD.MC.X - 1] == ' ' || map->data[mobD.MC.Y][mobD.MC.X - 1] == 'D')) //if player is on the left of the mob
			{
				int steps = 0;
				while(map->data[mobD.MC.Y][mobD.MC.X - steps] == ' ' || map->data[mobD.MC.Y][mobD.MC.X - steps] == 'D')
				{
					steps++;
					if(charLocation.X == mobD.MC.X - steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
					steps--;
				}
				mobD.xqueue = steps;
				mobD.first = moveX;
			}else if(charLocation.X > mobD.MC.X && (map->data[mobD.MC.Y][mobD.MC.X + 1] == ' ' || map->data[mobD.MC.Y][mobD.MC.X + 1] == 'D')) //if player is on th right of the mob
			{
				int steps = 0;
				while(map->data[mobD.MC.Y][mobD.MC.X + steps] == ' ' || map->data[mobD.MC.Y][mobD.MC.X + steps] == 'D')
				{
					steps++;
					if(charLocation.X == mobD.MC.X + steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
					steps--;
				}
				mobD.xqueue = -steps;
				//writeLog("I'm going down one space", 10);
				mobD.first = moveX;
			}
		}else if((map->data[mobD.MC.Y-1][mobD.MC.X] == 'D' || map->data[mobD.MC.Y-1][mobD.MC.X] == ' ') && (map->data[mobD.MC.Y+1][mobD.MC.X] == ' ' || map->data[mobD.MC.Y+1][mobD.MC.X] == 'D'))
		{
			if(charLocation.Y < mobD.MC.Y && (map->data[mobD.MC.Y - 1][mobD.MC.X] == ' ' || map->data[mobD.MC.Y - 1][mobD.MC.X] == 'D')) //if player is above the mob
			{
				int steps = 0;
				while(map->data[mobD.MC.Y-steps][mobD.MC.X] == ' ' || map->data[mobD.MC.Y-steps][mobD.MC.X] == 'D')
				{
					steps++;
					if(charLocation.Y == mobD.MC.Y -steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
				steps--;
				}
				mobD.yqueue = steps;
				mobD.first = moveY;
			}else if(charLocation.Y > mobD.MC.Y && (map->data[mobD.MC.Y + 1][mobD.MC.X] == ' ' || map->data[mobD.MC.Y + 1][mobD.MC.X] == 'D')) //if player is below the mob
			{
				int steps = 0;
				while(map->data[mobD.MC.Y+steps][mobD.MC.X] == ' ' || map->data[mobD.MC.Y+steps][mobD.MC.X] == 'D')
				{
					steps++;
					if(charLocation.Y == mobD.MC.Y+steps)
					{
						break;
					}
				}
				if(steps > 1)
				{
				steps--;
				}
				mobD.yqueue = -steps;
				mobD.first = moveY;
			}
		}
	}
	}
}