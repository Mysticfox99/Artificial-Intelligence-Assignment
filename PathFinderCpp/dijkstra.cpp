#include "bots.h"

void cDijkstra::Build(cBotBase& bot)
{	
	//Set the cost of the position that the bot is on to 0
	cost[bot.PositionX()][bot.PositionY()] = 0;
	
	//A while loop to find the grid location with the smallest cost
	while (!(closed[gTarget.PositionX()][gTarget.PositionY()])) //set to true when we are at the target position, stop loop when at target 
	{
		int tempCost = 10000; //temporary cost that is the same as the total cost so it can be used to compare the total cost.
		//Temporary locations that contain the x and y locations.
		int tempX = 0;
		int tempY = 0;
		//Find the locations of the grid
		for (int x = 0; x < GRIDWIDTH; x++)
		{
			for (int y = 0; y < GRIDHEIGHT; y++)			
			{
				//Check if locations total cost is lower than temp cost, if the location is not closed and is not blocked.
				if ((cost[x][y] < tempCost) && !(closed[x][y]) && (gLevel.isValid(x,y)))
				{
					tempCost = cost[x][y];
					int tempX = x; 
					int tempY = y; 
				}
			}
		}
        //Close the location with the lowest cost
		closed[tempX][tempY] = true;

	    //Calculating the new cost for the 8 neighbouring positions.		
		//The for loops find the locations (up,down,left,right)
		for (int x = -1; x < 2; x++) //find left (-1) & right (1)
		{
			for (int y = -1; y < 2; y++) //find up (-1) & down (1)			
			{
				int newX = tempX + x; //this calculates the horizontal neighbour
				int newY = tempY + y; //this calculates the verticle neighbour
				//Check if neighbouring location is not blocked and if it is open
				if (gLevel.isValid(newX, newY) && (closed[newX][newY] == false)) 
				{
					//Checks if only y = 0 or if x=0 but not both
					//and if the new cost is lower than current cost
					if (((y == 0) ^ (x == 0)) && cost[newX][newY] > cost[tempX][tempY] + 1) //Checks if it is horizontal or verticle
					{
						cost[newX][newY] = cost[tempX][tempY] + 1; 
						linkX[newX][newY] = tempX;
						linkY[newX][newY] = tempY;
					}
					else if (cost[newX][tempY + y] > cost[tempX][tempY] + 1.4)
					{
						cost[newX][newY] = cost[tempX][tempY] + 1.4;
						linkX[newX][newY] = tempX;
						linkY[newX][newY] = tempY;
					}
				}
			}
		}
	}
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path 
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		//Check to make sure the start of the path does not go over the grid
		if (nextClosedX < 40 && nextClosedY < 40)
		{
			inPath[nextClosedX][nextClosedY] = true;
			int tmpX = nextClosedX;
			int tmpY = nextClosedY;
			nextClosedX = linkX[tmpX][tmpY];
			nextClosedY = linkY[tmpX][tmpY];
			if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
		}
	}
	completed = true;	
};
cDijkstra gDijkstra;


/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cAStar::Build(cBotBase& bot)
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
	
	cost[bot.PositionX()][bot.PositionY()] = 0;

	//A while loop to find the grid location with the smallest cost

	while (!closed[gTarget.PositionX()][gTarget.PositionY()]) //set to true when we are at the target position, stop loop when at target 
	{			
		int tempCost = 10000.0;
		int tempX = 0;
		int tempY = 0;		
		float heuristic = 0; //heuristic variable that changes based on the user choice
		//Find the locations of the grid
		for (int x = 0; x < GRIDWIDTH; x++)
		{
			for (int y = 0; y < GRIDHEIGHT; y++)			
			{
				float diffX = fabs(gTarget.PositionX() - x); //finding the total difference in x
				float diffY = fabs(gTarget.PositionY() - y); //finding the total difference in y			
				//Manhattan distance heuristic
				if (heuristic_choice == 1)
				{
					heuristic = diffX + diffY;
				}
				//Diagonal distance heuristic
				else if (heuristic_choice == 2)
				{
					heuristic = (diffX + diffY) - (0.6) * fmin(diffX, diffY);
				}
				//Euclidean distance heuristic
				else if (heuristic_choice == 3)
				{
					heuristic = sqrt(pow(diffX, 2) + pow(diffY, 2));
				}
				//Check if locations total cost with the heuristic is lower than temp cost, if the location is not closed and is not blocked.
				if ((cost[x][y] + heuristic < tempCost) && (closed[x][y] == false) && (gLevel.isValid(x, y)))
				{
					tempCost = cost[x][y] + heuristic;
					tempX = x;
					tempY = y;
				}
			}
		}
		
		//Close the location with the lowest cost
		closed[tempX][tempY] = true;

		//These work the same as the dijkstra class (see lines 32-59)		
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)		
			{	
				int newX = tempX + x;
				int newY = tempY + y;
				if (gLevel.isValid(newX, newY) && (closed[newX][newY] == false))
				{
					if (((x == 0) ^ (y == 0)) && cost[newX][newY]  > cost[tempX][tempY] + 1) //Checks if it is horizontal or verticle
					{
						cost[newX][newY] = cost[tempX][tempY] + 1;
						linkX[newX][newY] = tempX;
						linkY[newX][newY] = tempY;
					}
					else if (cost[newX][newY] > cost[tempX][tempY] + 1.4)
					{
						cost[newX][newY] = cost[tempX][tempY] + 1.4;
						linkX[newX][newY] = tempX;
						linkY[newX][newY] = tempY;
					}
				}
			}
		}
	}
	bool done = false;
	int nextClosedX = gTarget.PositionX(); //start of path 
	int nextClosedY = gTarget.PositionY(); //start of path	
	location_list.clear(); //clear the vector if heuristic is changed
	while (!done && nextClosedX < GRIDWIDTH && nextClosedY < GRIDHEIGHT)
	{
			//Push the position of the target into the vector
			location_list.push_back(nextClosedX);
			location_list.push_back(nextClosedY);
			inPath[nextClosedX][nextClosedY] = true;
			int tmpX = nextClosedX;
			int tmpY = nextClosedY;
			nextClosedX = linkX[tmpX][tmpY];
			nextClosedY = linkY[tmpX][tmpY];
			if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
	}
	completed = true;
	std::reverse(location_list.begin(), location_list.end());
};
cAStar gAStar;