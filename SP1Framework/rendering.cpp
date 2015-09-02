#include "game.h"
#include "map.h"
#include "AI.h"
#include "UI.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
PMAP MapRender;
PMAP Push;

unsigned const char block = 219;
unsigned const char pblock = 254;
unsigned const char grass = 58;
unsigned const char lava = 247;
unsigned const char trap = 59;
unsigned const char treasure = 36;
unsigned const char switches = 47;
unsigned const char boost = 175;
unsigned const char X = 88;
unsigned const char Y = 89;
unsigned const char Z = 90;
unsigned const char ladder = 35;
unsigned const char crack = 178;
unsigned const char bomb = 229;
unsigned const char medkit = 43;
unsigned const char pit = 48;
unsigned const char invispot = 147;
char arr[12][12];

void createMap(COORD charLocation, bool blind, int range, player &user, Console &g_Console, char* mapname, mapBool & map)
{
	MapRender = load_map(mapname);
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
			//if(charLocation.X != 0)
			//{
			for(int j = 0;j < range-Xoffset;++j)
			{
				line = MapRender->data[charLocation.Y+temprange-i];
				arr[i][j] = line[charLocation.X - temprange+Xoffset+j];
				if(line[charLocation.X-temprange+Xoffset+j] == 'W')
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, block, 0xf1);
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'D')
				{
					//colour(0xf7);
					//cout << trap;
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, trap, 0xf1);
				}else if(line[charLocation.X-temprange+Xoffset+j] == 'X' && map.switch1 == 0)
				{
					//colour(0xf1);
					//cout << "X";
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, X, 0xf1);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'Y' && map.switch2 == 0)
				{
					//colour(0xf1);
					//cout << "Y";
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, Y, 0xf1);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'Z' && map.switch3 == 0)
				{
					//colour(0xf1);
					//cout << "Z";
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, Z, 0xf1);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '1' && map.switch1 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '2' && map.switch2 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '3' && map.switch3 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'C' && map.Cexplode == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, crack, 0xfc);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == '=')
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, lava, 0xfc);
				}
				else if(line[charLocation.X-temprange+Xoffset+j] == 'H')
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, ladder, 0xfc);
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'T' && map.TTaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, treasure, 0xf6);
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'I' && map.boost == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, boost, 0xf2);
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'M' && map.MedsTaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, medkit, 0xf2);
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'P')
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, pit, 0xf1);
				}else if (line[charLocation.X-temprange+Xoffset+j] == 'J' && map.bombtaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, bomb, 0xfc);
				}
				else if (line[charLocation.X-temprange+Xoffset+j] == 'L' && user.invispot == 0 && map.invistaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, invispot, 0xf2);
				}
				else{
					g_Console.writeToBuffer(charLocation.X-temprange+Xoffset+j, charLocation.Y+temprange-i, grass, 0xf1);
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
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, block, 0xf1);
				}else if(line[charLocation.X+k] == 'D')
				{
					//colour(0xf7);
					//cout << trap;
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, trap, 0xf1);
				}
				else if(line[charLocation.X+k] == '1' && map.switch1 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X+k] == '2' && map.switch2 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X+k] == '3' && map.switch3 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, switches, 0xf8);
				}
				else if(line[charLocation.X+k] == 'X'&& map.switch1 == 0)
				{
					//colour(0xf1);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, X, 0xf1);
				}
				else if(line[charLocation.X+k] == 'Y' && map.switch2 == 0)
				{
					//colour(0xf1);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, Y, 0xf1);
				}
				else if(line[charLocation.X+k] == 'Z' && map.switch3 == 0)
				{
					//colour(0xf1);
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, Z, 0xf1);
				}
				else if(line[charLocation.X+k] == 'C' && map.Cexplode == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, crack, 0xfc);
				}
				else if(line[charLocation.X+k] == '=')
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, lava, 0xfc);
				}
				else if(line[charLocation.X+k] == 'H')
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, ladder, 0xfc);
				}
				else if (line[charLocation.X+k] == 'T' && map.TTaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i,treasure, 0xf6);
				}
				else if (line[charLocation.X+k] == 'I' && map.boost == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, boost, 0xf2);
				}
				else if (line[charLocation.X+k] == 'M' && map.MedsTaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, medkit, 0xf2);
				}
				else if (line[charLocation.X+k] == 'P')
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, pit, 0xf1);
				}else if (line[charLocation.X+k] == 'J' && map.bombtaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, bomb, 0xfc);
				}
				else if (line[charLocation.X+k] == 'L' && user.invispot == 0 && map.invistaken == 0)
				{
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i, invispot, 0xf2);
				}
				else if(charLocation.X+k < 51){
					g_Console.writeToBuffer(charLocation.X+k,charLocation.Y+temprange-i,grass, 0xf1);
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
			for(int j=0; j<MapRender->ncol; ++j)
			{
				if(MapRender->data[i][j] == 'W')
				{
					g_Console.writeToBuffer(j, i, block, 0xf1);
				}else if(MapRender->data[i][j] == 'D')
				{
					//colour(0xf7);
					//cout << trap;
					g_Console.writeToBuffer(j, i, trap, 0xf1);
				}else if(MapRender->data[i][j] == 'X' && map.switch1 == 0)
				{
					//colour(0xf1);
					//cout << "X";
					g_Console.writeToBuffer(j, i, X, 0xf1);
				}
				else if(MapRender->data[i][j] == 'Y' && map.switch2 == 0)
				{
					//colour(0xf1);
					//cout << "Y";
					g_Console.writeToBuffer(j, i, Y, 0xf1);
				}
				else if(MapRender->data[i][j] == 'Z' && map.switch3 == 0)
				{
					//colour(0xf1);
					//cout << "Z";
					g_Console.writeToBuffer(j, i, Z, 0xf1);
				}
				else if(MapRender->data[i][j] == '1' && map.switch1 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(j, i, switches, 0xf8);
				}
				else if(MapRender->data[i][j] == '2' && map.switch2 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(j, i, switches, 0xf8);
				}
				else if(MapRender->data[i][j] == '3' && map.switch3 == 0)
				{
					//colour(0xf8);
					g_Console.writeToBuffer(j, i, switches, 0xf8);
				}
				else if(MapRender->data[i][j] == '=')
				{
					g_Console.writeToBuffer(j, i, lava, 0xfc);
				}
				else if(MapRender->data[i][j] == 'H')
				{
					g_Console.writeToBuffer(j, i, ladder, 0xfc);
				}
				else if(MapRender->data[i][j] == 'C' && map.Cexplode == 0)
				{
					g_Console.writeToBuffer(j, i, crack, 0xfc);
				}
				else if(MapRender->data[i][j] == 'J' && user.bomb == 0 && map.bombtaken == 0)
				{
					g_Console.writeToBuffer(j, i, bomb, 0xfc);
				}
				else if (MapRender->data[i][j] == 'T' && map.TTaken == 0)
				{
					g_Console.writeToBuffer(j, i, treasure, 0xf6);
				}
				else if (MapRender->data[i][j] == 'I' && map.boost == 0)
				{
					g_Console.writeToBuffer(j, i, boost, 0xf2);
				}
				else if (MapRender->data[i][j] == 'L' && user.invispot == 0 && map.invistaken == 0)
				{
					g_Console.writeToBuffer(j, i, invispot, 0xf2);
				}
				else if (MapRender->data[i][j] == 'M' && map.MedsTaken == 0)
				{
					g_Console.writeToBuffer(j, i, medkit, 0xf2);
				}
				else if (MapRender->data[i][j] == 'P')
				{
					g_Console.writeToBuffer(j, i, pit, 0xf1);
				}
				else{
					g_Console.writeToBuffer(j, i, grass, 0xf1);
				}
			}
		}
	}
}
void blockp(COORD &charLocation, COORD &blocks, COORD &lastknown, int range, Console &g_Console, bool blind)
{
	//COUT BLOCK IF IN RANGE
	if(blind == 1)
	{
		if((charLocation.X - range-1 < blocks.X && charLocation.X + range+1 > blocks.X) && (charLocation.Y - range-1 < blocks.Y && charLocation.Y + range+1 > blocks.Y))
		{
			g_Console.writeToBuffer(blocks.X, blocks.Y, pblock, 0xf1);
		}
	}else
	{
		g_Console.writeToBuffer(blocks.X, blocks.Y, pblock, 0xf1);
	}
	if(charLocation.X == blocks.X - 1 && charLocation.Y == blocks.Y)
	{
		if(MapRender->data[blocks.Y][blocks.X+1] != 'W')
		{
			g_Console.writeToBuffer(51, 11, "You can push the block! LEFT", 0xf1);
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			g_Console.writeToBuffer(51, 11, "You can't push the block anymore..", 0xf1);
		}
	}else if(charLocation.X == blocks.X + 1 && charLocation.Y == blocks.Y)
	{
		if(MapRender->data[blocks.Y][blocks.X-1] != 'W')
		{
			g_Console.writeToBuffer(51, 11, "You can push the block! RIGHT", 0xf1);
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			g_Console.writeToBuffer(51, 11, "You can't push the block anymore..", 0xf1);
		}
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y +1)
	{
		if(MapRender->data[blocks.Y+1][blocks.X] != 'W')
		{
			g_Console.writeToBuffer(51, 11, "You can push the block! BOTTOM", 0xf1);
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			g_Console.writeToBuffer(51, 11, "You can't push the block anymore..", 0xf1);
		}
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y -1)
	{
		if(MapRender->data[blocks.Y+1][blocks.X] != 'W')
		{
			g_Console.writeToBuffer(51, 11, "You can push the block! TOP", 0xf1);
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
		}else
		{
			g_Console.writeToBuffer(51, 11, "You can't push the block anymore..", 0xf1);
		}
	}else if(charLocation.X != blocks.X || charLocation.Y != blocks.Y){
			lastknown.X = charLocation.X;
			lastknown.Y = charLocation.Y;
	}else if(charLocation.X == blocks.X && charLocation.Y == blocks.Y)
	{
		gotoXY(51, 11);
			g_Console.writeToBuffer(51, 11, "You are standing on the box..", 0xf1);
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
	//colour(0x0f);
	//gotoXY(51, 16);
	//cout << "Block X: " << blocks.X << " " << blocks.Y;
	//gotoXY(51, 20);
	//cout << "LastCoord: " << lastknown.X << " " << lastknown.Y;
	//gotoXY(51, 18);
	//cout << "CharCoord: " << charLocation.X << " " << charLocation.Y;
}
void spawnblock(COORD &blocks)
{
	for(int i = 0;i< MapRender->nrow;++i)
	{
		for(int j = 0; j < MapRender->ncol; ++j)
		{
			if(MapRender->data[i][j] == 'B')
			{
				blocks.X = j;
				blocks.Y = i;
			}
		}
	}
}
void spawnmob(std::vector<mobData> &allMobs)
{
	//COORD mob;
	for(int i = 0;i< MapRender->nrow;++i)
	{
		for(int j = 0; j < MapRender->ncol; ++j)
		{
			if(MapRender->data[i][j] == 'E')
			{
				mobData tempmob;
				tempmob.xqueue = 0;
				tempmob.yqueue = 0;
				tempmob.first = 0;
				tempmob.lastMC.X = 0;
				tempmob.lastMC.Y = 0;
				tempmob.delay = 0;
				tempmob.movedelay = 0;
				tempmob.MC.X = j;
				tempmob.MC.Y = i;
				tempmob.playerImmunity = 0;
				allMobs.push_back(tempmob);
			}
		}
	}
}