#ifndef _MAP_H__
#define _MAP_H__

#include "Framework\timer.h"
#include "Framework\console.h"
#include "UI.h"

typedef struct sMap
{
	int		nrow, ncol;
	char**	data; 

	// constructor 
	sMap(int row, int col)
	{
		int i; 
		nrow = row; 	
		ncol = col; 
		data = new char*[nrow]; 
		for (i=0; i<nrow; i++)
			data[i] = new char[ncol+1]; 
	}

	// destructor 
	~sMap()
	{ 
		int i=0; 

		nrow = ncol = 0; 

		for (i=0; i<nrow; i++)
			delete [] data[i]; 

		delete [] data; 
	}
}
MAP, * PMAP; 


// ==========================================================================
// load map function 
//
//	input	:	char* filename		: filename of map 
//
//	out		:	MAP* MAP pointer	: Pointer to is Map data structure 
//
// 
// Remark	:	Apllication need to call the free_map function to release the 
//				memory for 
//
// ==========================================================================
PMAP load_map(char* filename);

void free_map(PMAP pmap);
void createMap1(COORD charLocation, bool blind, int range, player &user, Console &g_Console); //Creates Map for Output
void createMap2(COORD charLocation, bool blind, int range, player &user, Console &g_Console); //Creates Map for Output
void createMap3(COORD charLocation, bool blind, int range, player &user, Console &g_Console);
void blockp(COORD &charLocation, COORD &blocks, COORD &lastknown, int range, Console &g_Console);
void spawnblock(COORD &blocks);




#endif 