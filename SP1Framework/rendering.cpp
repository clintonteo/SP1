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
PMAP Push;

const char block = 219;
const char grass = 58;
const char lava = 247;
const char trap = 59;
const char treasure = 36;
char arr[12][12];


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
				arr[i][j] = line[charLocation.X - temprange+Xoffset+j];
				if(line[charLocation.X-temprange+Xoffset+j] == 'W')
				{
					colour(0xf1);
					cout << block;
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'D')
				{
					colour(0xf7);
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
					colour(0xf8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '2' && user.switch2 == 0)
				{
					colour(0xf8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '3' && user.switch3 == 0)
				{
					colour(0xf8);
					cout << "/";
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '=')
				{
					colour(0xfC);
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
				arr[i][range+k] = line[charLocation.X+k];
				if(line[charLocation.X+k] == 'W')
				{
					colour(0xf1);
					cout << block;
				}else if(line[charLocation.X+k] == 'D')
				{
					colour(0xf7);
					cout << trap;
				}
				else if(line[charLocation.X+k] == '1' && user.switch1 == 0)
				{
					colour(0xf8);
					cout << "/";
				}
				else if(line[charLocation.X+k] == '2' && user.switch2 == 0)
				{
					colour(0xf8);
					cout << "/";
				}
				else if(line[charLocation.X+k] == '3' && user.switch3 == 0)
				{
					colour(0xf8);
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
					colour(0xfC);
					cout << lava;
				}
				else if (line[charLocation.X+k] == 'T' && user.TTaken == 0)
				{
					cout << treasure;
				}
				else if(charLocation.X+k < 51){
					colour(0xf7);
					cout << grass;
				}

			}
			}
		}
		//Arr RADAR
		//for(int i = 0; i< range*2; ++i)
		//{
		//	for(int j = 0; j < range*2; ++j)
		//	{
		//		colour(0x03);
		//		gotoXY(50+j,16+i);
		//		if(i == range && j == range)
		//		{
		//			arr[i][j] = 'A';
		//		}
		//		cout << arr[range*2-i][j];
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
					colour(1);
				cout << block;
				}else if(MapRender->data[i][j] == 'D')
				{
					colour(0xff);
					cout << trap;
				}
				else if(MapRender->data[i][j] == '1' && user.switch1 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(MapRender->data[i][j] == '2' && user.switch2 == 0)
				{
					colour(8);
					cout << "/";
				}
				else if(MapRender->data[i][j] == '3' && user.switch3 == 0)
				{
					colour(0xf8);
					cout << "/";
				}
				else if(MapRender->data[i][j] == 'X'&& user.switch1 == 0)
				{
					colour(0xf1);
					cout << "X";
				}
				else if(MapRender->data[i][j] == 'Y' && user.switch2 == 0)
				{
					colour(0xf1);
					cout << "Y";
				}
				else if(MapRender->data[i][j] == 'Z' && user.switch3 == 0)
				{
					colour(0xf1);
					cout << "";
				}
				else if(MapRender->data[i][j] == '=')
				{
					colour(0x0C);
					cout << lava;
				}
				else if (MapRender->data[i][j] == 'T' && user.TTaken == 0)
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

    //// render time taken to calculate this frame
    //gotoXY(70, 0);
    //colour(0x1A);
    //std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    //gotoXY(0, 0);
    //colour(0x59);

    //std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0xfC);
    std::cout << (char)1;
}
void blockp(COORD &charLocation, COORD &blocks, COORD &lastknown, int range)
{
	//COUT BLOCK IF IN RANGE
	if((charLocation.X - range-1 < blocks.X && charLocation.X + range+1 > blocks.X) && (charLocation.Y - range-1 < blocks.Y && charLocation.Y + range+1 > blocks.Y))
	{
	gotoXY(blocks.X, blocks.Y);
	cout << "B";
	}
	if(charLocation.X == blocks.X - 1 && charLocation.Y == blocks.Y)
	{
		if(MapRender->data[blocks.Y][blocks.X+1] != 'W')
		{
			gotoXY(51, 11);
			cout << "You can push the block! LEFT";
			cout << MapRender->data[blocks.Y][blocks.X];
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			gotoXY(51, 11);
			cout << "You can't push the block anymore..";
		}
	}else if(charLocation.X == blocks.X + 1 && charLocation.Y == blocks.Y)
	{
		if(MapRender->data[blocks.Y][blocks.X-1] != 'W')
		{
			gotoXY(51, 11);
			cout << "You can push the block! RIGHT";
			cout << MapRender->data[blocks.Y][blocks.X];
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			cout << "You can't push the block anymore..";
		}
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y +1)
	{
		if(MapRender->data[blocks.Y+1][blocks.X] != 'W')
		{
			gotoXY(51, 11);
			cout << "You can push the block! BOTTOM";
			cout << MapRender->data[blocks.Y][blocks.X];
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			cout << "You can't push the block anymore..";
		}
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y -1)
	{
		if(MapRender->data[blocks.Y+1][blocks.X] != 'W')
		{
			gotoXY(51, 11);
			cout << "You can push the block! TOP";
			cout << MapRender->data[blocks.Y][blocks.X];
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			cout << "You can't push the block anymore..";
		}
	}else if(charLocation.X != blocks.X || charLocation.Y != blocks.Y){
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y)
	{
		gotoXY(51, 11);
		cout << "You are standing on the box..";
	}
	if(charLocation.X == blocks.X && charLocation.Y == blocks.Y)
	{
		if(lastknown.X == charLocation.X -1 && lastknown.Y == charLocation.Y)
		{
			if(MapRender->data[blocks.Y][blocks.X +1] != 'W')
			{
				if(MapRender->data[blocks.Y][blocks.X] != '=')
				{
					charLocation.X -=1;
					blocks.X +=1;
				}
			}
		}
		if(lastknown.X == charLocation.X +1 && lastknown.Y == charLocation.Y)
		{
			if(MapRender->data[blocks.Y][blocks.X -1] != 'W')
			{
				if(MapRender->data[blocks.Y][blocks.X] != '=')
				{
					charLocation.X +=1;
					blocks.X -=1;
				}
			}
		}
		if((lastknown.X == charLocation.X) && (lastknown.Y == charLocation.Y-1))
		{
			if(MapRender->data[blocks.Y+1][blocks.X] != 'W')
			{
				if(MapRender->data[blocks.Y][blocks.X] != '=')
				{
					charLocation.Y -=1;
					blocks.Y +=1;
				}
			}
		}
		if((lastknown.X == charLocation.X) && (lastknown.Y == charLocation.Y+1))
		{
			if(MapRender->data[blocks.Y-1][blocks.X] != 'W')
			{
				if(MapRender->data[blocks.Y][blocks.X] != '=')
				{
				charLocation.Y +=1;
				blocks.Y -=1;
				}
			}
		}
	}
	colour(0x0f);
	gotoXY(51, 16);
	cout << "Block X: " << blocks.X << " " << blocks.Y;
	gotoXY(51, 20);
	cout << "LastCoord: " << lastknown.X << " " << lastknown.Y;
	gotoXY(51, 18);
	cout << "CharCoord: " << charLocation.X << " " << charLocation.Y;
}