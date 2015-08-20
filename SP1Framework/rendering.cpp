#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
PMAP MapRender;
const char block = 219;
const char grass = 177;
const char lava = 247;
const char trap = 178;
const char treasure = 36;

void createMap(COORD charLocation, bool blind, int range, player &user)
{
    // clear previous screen
    colour(0x0F);
    cls();
	MapRender = load_map("stage1.txt");
    //render the game

    //render test screen code (not efficient at all)
    //const WORD colors[] =   {
	   //                     0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	   //                     0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	   //                     };
	string line;
	int temprange = range;
	int Xoffset = 0;
	int Yoffset = 0;
	//gotoXY(40, 20);
	//cout << "Coordinates :" << charLocation.X << " " << charLocation.Y;
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
			// && charLocation.Y-temprange+offset >-1  charLocation.X-temprange+offset >-1
			gotoXY(charLocation.X-temprange+Xoffset, charLocation.Y+temprange-i);
			//if(charLocation.X != 0)
			//{
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
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'X' && user.switch1 == 0)
				{
					colour(0xf1);
					cout << "X";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'Y' && user.switch2 == 0)
				{
					colour(0xf1);
					cout << "Y";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'Z' && user.switch3 == 0)
				{
					colour(0xf1);
					cout << "Z";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '1' && user.switch1 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '2' && user.switch2 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '3' && user.switch3 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '=')
				{
					colour(0x0C);
					cout << lava;
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'T' && user.TTaken == 0)
				{
					cout << treasure;
				}
				else{
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
				}
				else if(line[charLocation.X+k] == '1' && user.switch1 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X+k] == '2' && user.switch2 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X+k] == '3' && user.switch3 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(line[charLocation.X+k] == 'X'&& user.switch1 == 0)
				{
					colour(0xf1);
					cout << "X";
				}
				else if(line[charLocation.X+k] == 'Y' && user.switch2 == 0)
				{
					colour(0xf1);
					cout << "Y";
				}
				else if(line[charLocation.X+k] == 'Z' && user.switch3 == 0)
				{
					colour(0xf1);
					cout << "";
				}
				else if(line[charLocation.X+k] == '=')
				{
					colour(0x0C);
					cout << lava;
				}
				else if (line[charLocation.X+k] == 'T' && user.TTaken == 0)
				{
					cout << treasure;
				}
				else{
					colour(0xf7);
					cout << grass;
				}
			}
			}
		}
		//for(int i = 0 ; i < range*2+1; ++i)
		//{
		//	gotoXY(charLocation.X-range, charLocation.Y);
		//	for(int j = 0; j < range; ++j)
		//	{
		//		cout << MapRender->data[charLocation.Y-range+i][]
		//	}
		//}
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
					cout << "D";
				}else
				{
					cout << ".";
				}
			}
		}
	}

    //// render time taken to calculate this frame
    //gotoXY(70, 0);
    //colour(0x1A);
    //std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    //gotoXY(0, 0);
    //colour(0x59);

    //std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;
}