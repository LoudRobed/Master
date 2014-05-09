/*
 *  BoxIdleness.h
 *
 *	Compute the idleness of boxes covering the world area
 *  Each time a robot goes in a box, its score is increased by one. The averageIdlenessm is the average of all the boxes of the environment
 *
 *  created by Jean-Marc on 03/08/2012
 *
 */

#ifndef BOXIDLENESS_H
#define BOXIDLENESS_H

#include <vector>
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"

class BoxIdleness
{
	public:
		BoxIdleness(void);
		BoxIdleness(int nbBoxWidth, int nbBoxHeight);
		~BoxIdleness(void);
		void reset(void);

		bool addPoint(Point2d toAdd);
		double getAverageBoxesIdleness(void);
		std::vector< std::vector<int> > getBoxesIdleness(void);

	protected:
		double boxWidth;
		double boxHeight;
		int nbBoxWidth;
		int nbBoxHeight;
		std::vector< std::vector<int> > allBoxes;

};

#endif
