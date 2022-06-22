#include "bots.h"
#include "stdlib.h"
#include <iostream>

void cBotAStar::ChooseNextGridPosition()
{
	int last_index = gAStar.location_list.size() - 1; //get last item in vector
	if (index < last_index)
	{
		SetNext(gAStar.location_list[index+1], gAStar.location_list[index], gLevel); //move the bot to the next location
		index += 2;
	}
	else
	{
		index = 0;
	}
}