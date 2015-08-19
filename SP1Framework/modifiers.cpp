
#include "game.h"
#include "Framework/console.h"
#include <iostream>
#include <fstream>
#include <string>
void map(bool blindness, COORD mapcoord, COORD charcoord, int range){//#include "game.h"
	//std::ifstream myfile;
	//myfile.open("testlevel.txt");
	//std::string line;
	//std::string lineOnPlayer;
	//std::string lineBelowPlayer;
	//std::string lineAbovePlayer;
	//gotoXY(charcoord);
	//if(blindness = 1)
	//{
	//int horX = charcoord.X-range; // Set Position X before the player 
	//int y = 0; //Number to get to the line the player is standing on
	//int lineNumber = 0; //
	//while(horX != charcoord.X+range+1)
	//{
	//	lineNumber++;
	//	if(y != charcoord.Y+range-1)
	//	{
	//		std::getline(myfile, line);
	//		if(lineNumber == charcoord.Y-1)
	//		{
	//			while(horX != charcoord.X+range+1)
	//			{
	//			lineAbovePlayer = line;
	//			gotoXY(horX, charcoord.Y-1);
	//			//mapcoord.X = horX;
	//			//mapcoord.Y = charcoord.Y-1;
	//			std::cout << lineAbovePlayer[horX];
	//			++horX;
	//			}
	//		}
	//		horX = charcoord.X-range;
	//		if(lineNumber == charcoord.Y)
	//		{
	//			while(horX != charcoord.X+range+1)
	//			{
	//			lineOnPlayer = line;
	//			gotoXY(horX, charcoord.Y);
	//			std::cout << lineOnPlayer[horX];
	//			++horX;
	//			}
	//		}
	//		horX = charcoord.X-range;
	//		if(lineNumber == charcoord.Y+1)
	//		{
	//			while(horX != charcoord.X+range+1)
	//			{
	//			lineBelowPlayer = line;
	//			gotoXY(horX, charcoord.Y+1);
	//			std::cout << lineBelowPlayer[horX];
	//			++horX;
	//			}
	//		}
	//		++y;
	//	}

	//	//if(lineNumber > charcoord.Y+range)
	//	//{
	//	//	//gotoXY(horX, charcoord.Y+range-1);
	//	//	//std::cout << lineBelowPlayer[horX];
	//	//	//gotoXY(horX, charcoord.Y);
	//	//	//std::cout << lineOnPlayer[horX];
	//	//	//gotoXY(horX, charcoord.Y-range+1);
	//	//	//std::cout << lineAbovePlayer[horX];
	//	//	++horX;
	//	//}
	//}
	//}else
	//{
	//		
	//}
	//myfile.close();
}