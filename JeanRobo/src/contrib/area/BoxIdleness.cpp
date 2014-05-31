#include "area/BoxIdleness.h"
#include <iostream>

BoxIdleness::BoxIdleness(void)
{
	nbBoxWidth = 256;
	nbBoxHeight = 134;
	boxWidth = (double)gScreenWidth / (double)nbBoxWidth;
	boxHeight = (double)gScreenHeight / (double)nbBoxHeight;
	std::vector<int> tmp(nbBoxWidth,0);
	for(int i = 0 ; i < nbBoxHeight ; i++)
	{
		allBoxes.push_back(tmp);
	}
}

BoxIdleness::BoxIdleness(int nbBoxWidth, int nbBoxHeight) :
	nbBoxWidth(nbBoxWidth),
	nbBoxHeight(nbBoxHeight)
{
	boxWidth = (double)gScreenWidth / (double)nbBoxWidth;
	boxHeight = (double)gScreenHeight / (double)nbBoxHeight;
	std::vector<int> tmp(nbBoxWidth,0);
	for(int i = 0 ; i < nbBoxHeight ; i++)
	{	
		allBoxes.push_back(tmp);
	}
}

BoxIdleness::~BoxIdleness(void)
{
	//nothing
}

void BoxIdleness::reset(void)
{
	allBoxes.clear();
	std::vector<int> tmp(nbBoxWidth,0);
	for(int i = 0 ; i < nbBoxHeight ; i++)
	{
		allBoxes.push_back(tmp);
	}
}

bool BoxIdleness::addPoint(Point2d toAdd)
{
	int idLine = -1 ;
	for (int i = 0 ; i < nbBoxHeight ; i++ )
	{
		if ( ( toAdd.y >= (i * boxHeight) ) && (toAdd.y < ( (i+1) * boxHeight ) ) )
		{
			idLine = i;
			break;
		}
	}
	if ( idLine == -1)
	{
		return false;
	}

	int idRow = -1 ;
	for (int i = 0 ; i < nbBoxWidth ; i++ )
	{
		if ( ( toAdd.x >= (i * boxWidth) ) && (toAdd.x < ( (i+1) * boxWidth ) ) )
		{
			idRow = i;
			break;
		}
	}
	if ( idRow == -1)
	{
		return false;
	}

	allBoxes[idLine][idRow] += 1;
return true;
}

double BoxIdleness::getAverageBoxesIdleness(void)
{
	int sum = 0;
	for (int idLine = 0 ; idLine < nbBoxHeight ; idLine++ )
	{
		for (int idRow = 0 ; idRow < nbBoxWidth ; idRow++ )
		{
			if (allBoxes[idLine][idRow] > 0)
			{
				sum += 1;
			}
		}
	}
	return (double)sum/(double)(nbBoxWidth*nbBoxHeight);
}

std::vector< std::vector<int> > BoxIdleness::getBoxesIdleness(void)
{
	return allBoxes;
}

