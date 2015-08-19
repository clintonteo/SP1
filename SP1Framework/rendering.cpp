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
void createMap(COORD charLocation, bool blind, int range)
{
    // clear previous screen
    colour(0x0F);
    cls();
	MapRender = load_map("map.txt");
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
	gotoXY(40, 20);
	cout << "Coordinates :" << charLocation.X << " " << charLocation.Y;
	if(blind == 1)
	{
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
			if(charLocation.Y+temprange-i < 27 && charLocation.X-temprange < 79)// && charLocation.Y-temprange-Yoffset > 0)
			{
			// && charLocation.Y-temprange+offset >-1  charLocation.X-temprange+offset >-1
			gotoXY(charLocation.X-temprange+Xoffset, charLocation.Y+temprange-i);
			//if(charLocation.X != 0)
			//{
			for(int j = 0;j < range-Xoffset;++j)
			{
				line = MapRender->data[charLocation.Y+temprange-i];
				if(line[charLocation.X-temprange+Xoffset+j] == 'B')
				{
					cout << block;
				}else{
					cout << " ";
				}
			}
			//}
			for(int k = 0;k < range+1;++k)
			{
				if(charLocation.X == 0)
				{
					line = MapRender->data[charLocation.Y+temprange-i];
				}
				if(line[charLocation.X+k] == 'B')
				{
				cout << block;
				}else{
					cout << " ";
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
		for(int i=0;i<27;++i)
		{
			gotoXY(0, i);
			for(int j=0; j<79; ++j)
			{
				if(MapRender->data[i][j] == 'B')
				{
					cout << block;
				}else
				{
					cout << " ";
				}
			}
		}
	}

 //   gotoXY(charLocation);
 //   colour(0x0C);
 //   std::cout << (char)1;
	//if(blind == 1)
	//{
	//	for(int i=0;i < range*2+1;++i)
	//	{
	//		gotoXY(charLocation.X-range, charLocation.Y+range-i);
	//		for(int j = 0;j < range;++j)
	//		{

	//			cout << arr[charLocation.Y+range-i][charLocation.X-range+j];
	//		}
	//		for(int k = 0;k < range+1;++k)
	//		{
	//			cout << arr[charLocation.Y+range-i][charLocation.X+k];
	//		}
	//	}
		//if(charLocation.X - range < range)
		//{
		//	gotoXY(charLocation.X, charLocation.Y+1);
		//}else
		//{
		//gotoXY(charLocation.X-range, charLocation.Y+1);
		//}
		//for(int i = 0;i < range;++i)
		//{

		//	cout << arr[charLocation.Y+1][charLocation.X-range+i];
		//}
		//for(int i = 0;i < range+1;++i)
		//{
		//	cout << arr[charLocation.Y+1][charLocation.X+i];
		//}
	
		//if(charLocation.X - range < range)
		//{
		//	gotoXY(charLocation.X, charLocation.Y);
		//}else
		//{
		//gotoXY(charLocation.X-range, charLocation.Y);
		//}
		//for(int i = 0;i < range;++i)
		//{
		//	cout << arr[charLocation.Y][charLocation.X-range+i];
		//}
		//for(int i = 0;i < range+1;++i)
		//{
		//	cout << arr[charLocation.Y][charLocation.X+i];
		//}
		//if(charLocation.X - range < range)
		//{
		//	gotoXY(charLocation.X, charLocation.Y-1);
		//}else
		//{
		//gotoXY(charLocation.X-range, charLocation.Y-1);
		//}
		//for(int i = 0;i < range;++i)
		//{
		//	cout << arr[charLocation.Y-1][charLocation.X-range+i];
		//}
		//for(int i = 0;i < range+1;++i)
		//{
		//	cout << arr[charLocation.Y-1][charLocation.X+i];
		//}
	//}else
	//{
	//	for (int col = 0; col < 27; col++)
	//	{
	//		for(int row = 0; row < 79; row++)
	//		{
	//			cout << arr[col][row];
	//		}
	//		cout << endl;
	//	}
	//}
	/*gotoXY(20, 5);
	cout << "Element in Array: " <<arr[charLocation.Y][charLocation.X];
	gotoXY(20, 6);
	cout << "Element ID in Array: " <<static_cast<int>(arr[charLocation.Y][charLocation.X]);
	gotoXY(20, 7);
	cout << "Character Coords: " <<charLocation.X << " " << charLocation.Y;
	gotoXY(20, 8);
	cout << "Arr Element testing: " << arr[0][0];*/
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