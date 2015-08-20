#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
PMAP MapRender;
const char block = 219;
const char grass = 177;
const char lava = 247;
const char trap = 178;
std::vector<string> notification;
void createMap(COORD charLocation, bool blind, int range, bool switch1)
{
	MapRender = load_map("stage1.txt");
	string line;
	int temprange = range;
	int Xoffset = 0;
	int Yoffset = 0;
	if(blind == 1)
	{
		//Set Offset when player is near the Edge of the screen
		if(charLocation.X < temprange)
		{
			Xoffset = temprange - charLocation.X;
		}
		if(charLocation.Y < temprange)
		{
			Yoffset = temprange - charLocation.Y;
		}

		for(int i=0;i < range*2+1-Yoffset;++i)
		{
			//Cout Char Elements Before the player (X-axis)
			if(charLocation.Y+temprange-i < MapRender->nrow && charLocation.X-temprange < MapRender->ncol)
			{
			gotoXY(charLocation.X-temprange+Xoffset, charLocation.Y+temprange-i);
			for(int j = 0;j < range-Xoffset;++j)
			{
				line = MapRender->data[charLocation.Y+temprange-i];
				if(line[charLocation.X-temprange+Xoffset+j] == 'W')
				{
					colour(1);
					cout << block;
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'D')
				{
					colour(0xff);
					cout << trap;
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'X' && switch1 == 0)
				{
					colour(0xf1);
					cout << "X";
				}else if(line[charLocation.X-temprange+Xoffset+j] == '1')
				{
					colour(8);
					cout << "/";
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'L')
				{
					colour(0x0C);
					cout << lava;
				}else{
					colour(0xf7);
					cout << grass;
				}
			}
			//Cout Char Elements After the player (Y-axis)
			for(int k = 0;k < range+1;++k)
			{
				if(charLocation.X == 0)
				{
					line = MapRender->data[charLocation.Y+temprange-i];
				}
				if(line[charLocation.X+k] == 'W')
				{
					colour(1);
				cout << block;
				}else if(line[charLocation.X+k] == 'D')
				{
					colour(0xff);
					cout << trap;
				}else if(line[charLocation.X+k] == '1')
				{
					colour(8);
					cout << "/";
				}else if(line[charLocation.X+k] == 'X'&& switch1 == 0)
				{
					colour(0xf1);
					cout << "X";
				}else if(line[charLocation.X+k] == 'L')
				{
					colour(0x0C);
					cout << lava;
				}else{
					colour(0xf7);
					cout << grass;
				}
			}
			}
		}
	}else
	{
		//Cout the whole map
		for(int i=0;i<MapRender->nrow;++i)
		{
			gotoXY(0, i);
			for(int j=0; j<MapRender->ncol; ++j)
			{
				if(MapRender->data[i][j] == 'W')
				{
					cout << block;
				}else if(MapRender->data[i][j] == 'D')
				{
					cout << "™";
				}else
				{
					cout << ".";
				}
			}
		}
	}
}