#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <iostream>
#include <vector>

class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};
//Create a bot for the AStar algorithm
class cBotAStar : public cBotBase
{
	virtual void ChooseNextGridPosition();
	int index;
};
//Create a class for the cDijkstra algorithm
class cDijkstra
{
	public:   
		virtual void Build(cBotBase& bot); //function that will calculate the path and fill the data arrays below
		bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed  
		float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location  
		int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location  
		int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location  
		bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in the final path		
		bool completed; 
 
		cDijkstra() //Default class constructors that define the class member variables
		{ 
			//The for loops initialise the variables in the data arrays for each location
			for (int x = 0; x < GRIDWIDTH; x++)		
			{
				for (int y = 0; y < GRIDHEIGHT; y++)
				{
					closed[x][y] = false;
					cost[x][y] = 10000;
					linkX[x][y] = -1;
					linkY[x][y] = -1;
					inPath[x][y] = false;
				}
			}

			completed = false; 	
		}
};
extern cDijkstra gDijkstra; //Make the global gDijkstra object external so it can be accessed in main.

//Create class for the cAStar algorithm which inherits from class cDijkstra
class cAStar : public cDijkstra
{
	public:
		virtual void Build(cBotBase& bot); //function that will calculate the path and fill the data arrays below		
		std::vector<int> location_list; //Create a vector that contains the locations that the bot will follow	
		int heuristic_choice = 0; //define the choice int which allows the user to change the heuristic
		
};
extern cAStar gAStar; //Make the global gAStar object external so it can be accessed in main.