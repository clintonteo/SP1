#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

#include "map.h"


PMAP load_map(char* filename)
{
	MAP* map; 
	
	ifstream infile; 
	int nrow, ncol, i; 

	infile.open(filename); 	
	if (!infile)
	{
		cout << "Error Opening" << filename << endl ; 
		exit(1); 
	}


	if (infile.good())
	{

		// get nrow and ncol at 1st line of the file  
		infile >> nrow >> ncol; 		

		// allocate the MAP structure and memory to hold the map data 
		map = new MAP(nrow, ncol); 

		// read back the map data 
		i= 0; 
		while(infile.good())
		{
			string line; 
			getline(infile, line);
			if (line.length())
			{
				memcpy(map->data[i],line.c_str(), ncol); 
				i++;
			}
		}
	}
	infile.close(); 
	

	return map; 
}

void free_map(PMAP pmap)
{
	delete pmap; 
}