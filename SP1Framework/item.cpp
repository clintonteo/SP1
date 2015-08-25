#include <iostream>
#include "map.h"
#include "item.h"
#include "game.h"
#include "Framework\console.h"
#include <sstream>

// item1 is boost, item2 is explosive

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
		    //user.bcd = 11;
		    boostcd = currentTime + 3;

            /*string cooldown;
            std::ostringstream convert;
            convert << static_cast<int>(boostcd);
            cooldown = convert.str();
            g_Console.writeToBuffer(56, 3, cooldown, 10);*/
	    }
	    else
	    {
		    charLocation.Y -= count - 1;
		    //user.bcd = 11;
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
		//user.bcd = 11;
		boostcd = currentTime + 3;
	}
	else
	{
		charLocation.X -= count - 1;
		//user.bcd = 11;
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
		//user.bcd = 11;
		boostcd = currentTime + 3;
	}
	else
	{
		charLocation.Y += count - 1;
		//user.bcd = 11;
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
		//user.bcd = 11;
		boostcd = currentTime + 3;
    }
	else
	{
		charLocation.X += count - 1;
		//user.bcd = 11;
		boostcd = currentTime + 3;
	}
	}
}

void item2(player&user)
{
	user.Cexplode = 1;
	user.bomb = 0;
}

void item3()
{
	
}