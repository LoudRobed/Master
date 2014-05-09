/*
 *  HullArea.h
 *
 *	Compute the convex hull of a set of points
 *  	Computation done thanks to the Graham algorithm 
 * 		Inspiration : http://cs.smith.edu/~orourke/books/ftp.html
 * 		Explanation : http://softsurfer.com/Archive/algorithm_0109/algorithm_0109.htm
 * 	From the hull, deduce the area covered by the set of points
 * 		Explanation : http://softsurfer.com/Archive/algorithm_0101/algorithm_0101.htm
 *
 *  created by Jean-Marc on 03/08/2012
 *
 */

#ifndef HULLAREA_H
#define HULLAREA_H

#include <vector>
#include "Utilities/Misc.h"
#include <algorithm>

class HullArea
{
	public:
		HullArea(void);
		~HullArea(void);
		void reset(void);

		bool addPointToSet(Point2d toAdd);
		bool removePointFromSet(int i);
		std::vector<Point2d> getAllPointsFromSet(void) const;
		std::vector<Point2d> getHull(void);
		void computeHull(void);
		void computeHullArea(void);
		double getHullArea(void);
		void printPostScript(void);

	protected:
		std::vector<Point2d> allPoints;
		std::vector<Point2d> hullStack;
		double hullArea;

		/*---------------------------------------------------------------------
			the compare function is embedded in a struct because we need an object specific value:
				the lowest most right point of the set
			http://stackoverflow.com/questions/1902311/problem-sorting-using-member-function-as-comparator
		---------------------------------------------------------------------*/
		struct Compare 
		{
			Compare(const HullArea& c) : m_info(c){}
			const HullArea& m_info;
			/*---------------------------------------------------------------------
			operator: returns true if p1 < p2, or false otherwise;
			here "<" means smaller angle.  Follows the conventions of std::sort.
			---------------------------------------------------------------------*/
			bool operator () (const Point2d & p1, const Point2d & p2) 
			{
				std::vector<Point2d> localPoints = m_info.getAllPointsFromSet();
				int a = m_info.areaSign(localPoints[0], p1, p2);
				if (a > 0)
					return true;
				else if (a < 0)
					return false;
				else
					return false;		
			}
		};

		bool findLowest(void);
		bool eraseColinearsAndCoincident(void);
		bool addPointToStack(Point2d toAdd);
		bool removePointFromStack(int i);
		bool swap(int a, int b);
		bool doSort(void);
		int areaSign(Point2d a, Point2d b, Point2d c) const;
		void printAllPoints(void);
		void printHullStack(void);
		bool left( Point2d a, Point2d b, Point2d c );
};

#endif
