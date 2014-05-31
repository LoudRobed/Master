#include "mEDEA-altruism/include/HullArea.h"
#include <iostream>

HullArea::HullArea(void)
{
	//nothing
}

HullArea::~HullArea(void)
{
	//nothing
}

void HullArea::reset(void)
{
	allPoints.clear();
	hullStack.clear();
}

bool HullArea::addPointToSet(Point2d toAdd)
{
	allPoints.push_back(toAdd);
	return true;
}

bool HullArea::removePointFromSet(int i)
{
	if ((unsigned)i < allPoints.size())
	{
		allPoints.erase(allPoints.begin()+i);
		return true;
	}
	else
	{
		return false;
	}
}

void HullArea::printAllPoints(void)
{
	for (unsigned i = 0 ; i < allPoints.size() ; i++)
	{
		std::cout << allPoints[i].x <<  " " << allPoints[i].y << std::endl;
	}
}

void HullArea::printHullStack(void)
{
	for (unsigned i = 0 ; i < hullStack.size() ; i++)
	{
		std::cout << hullStack[i].x <<  " " << hullStack[i].y << std::endl;
	}
}

bool HullArea::addPointToStack(Point2d toAdd)
{
	hullStack.push_back(toAdd);
	return true;
}

bool HullArea::removePointFromStack(int i)
{
	if ((unsigned)i < hullStack.size())
	{
		hullStack.erase(hullStack.begin()+i);
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<Point2d> HullArea::getAllPointsFromSet(void) const
{
	return allPoints;
}

void HullArea::computeHull(void)
{
	findLowest();
	eraseColinearsAndCoincident();
	doSort();

	/* Initialize stack. */
	hullStack.push_back(allPoints[0]);
	hullStack.push_back(allPoints[1]);

	/* Bottom two elements will never be removed. */
	unsigned int i = 2;

	while ( i < allPoints.size() ) {
		Point2d p1 = hullStack[hullStack.size()-2];
		Point2d p2 = hullStack[hullStack.size()-1];
		if ( left( p1 , p2, allPoints[i] ) ) {
			hullStack.push_back(allPoints[i]);
			i++;
		} else    
			hullStack.pop_back();
	}
}

std::vector<Point2d> HullArea::getHull(void)
{
	return hullStack;
}

void HullArea::computeHullArea(void)
{
	hullArea = 0.0;
	for(unsigned int i = 0 ; i < hullStack.size() ; i++)
	{
		int j = (i+1)%hullStack.size();
		hullArea += hullStack[i].x * hullStack[j].y;
		hullArea -= hullStack[i].y * hullStack[j].x;
	}
}

double HullArea::getHullArea(void)
{
	return hullArea;
}

void HullArea::printPostScript(void)
{
	int xmin, ymin, xmax, ymax;

	xmin = xmax = allPoints[0].x;
	ymin = ymax = allPoints[0].y;
	for (unsigned int i = 1; i < allPoints.size(); i++) {
		if      ( allPoints[i].x > xmax ) xmax = allPoints[i].x;
		else if ( allPoints[i].x < xmin ) xmin = allPoints[i].x;
		if      ( allPoints[i].y > ymax ) ymax = allPoints[i].y;
		else if ( allPoints[i].y < ymin ) ymin = allPoints[i].y;
	}

	/* PostScript header */
	std::cout << "%!PS" << std::endl;
	std::cout << "%%Creator: graham.cpp (Jean-Marc Montanier)" << std::endl;
	std::cout << "%%BoundingBox: " << (xmin*10)-10 << " " << (ymin*10)-10 << " " << (xmax*10)+10 << " " << (ymax*10)+10 << std::endl; 
	std::cout << "%%EndComments" << std::endl;
	std::cout << ".00 .00 setlinewidth" << std::endl;
	/* The +72 shifts the figure one inch from the lower left corner */

	/* Draw the points as little circles. */
	std::cout << "%%Points:" << std::endl;
	for (unsigned int i = 0; i < allPoints.size(); i++)
		std::cout << (allPoints[i].x*10) << "\t" << (allPoints[i].y*10) << "\t1  0  360\tarc\tstroke" << std::endl;

	/* Draw the polygon. */
	std::cout << "\n%%Hull:" << std::endl;
	std::cout << "newpath" << std::endl;
	std::cout << (hullStack[hullStack.size()-1].x*10) << "\t" << (hullStack[hullStack.size()-1].y*10) << "\tmoveto" << std::endl;
	for (int i = (int)(hullStack.size()-2) ; i >= 0 ; i--)
	{
		std::cout << (hullStack[i].x*10) << "\t" << (hullStack[i].y*10) << "\tlineto" << std::endl;
	}
	std::cout << "closepath stroke" << std::endl;
	std::cout << "showpage\n%%%%EOF" << std::endl;
}

/*---------------------------------------------------------------------
	FindLowest finds the rightmost lowest point and swaps with 0-th.
	The lowest point has the min y-coord, and amongst those, the
	max x-coord: so it is rightmost among the lowest.
	---------------------------------------------------------------------*/
bool HullArea::findLowest(void)
{
	int m = 0;   /* Index of lowest so far. */

	for (unsigned int i = 1; i < allPoints.size() ; i++ )
		if ( (allPoints[i].y <  allPoints[m].y) ||
				((allPoints[i].y == allPoints[m].y) && (allPoints[i].x > allPoints[m].x)) ) 
			m = i;
	swap(0,m); /* Swap P[0] and P[m] */
	return true;
}

bool HullArea::swap(int a, int b)
{
	Point2d tmp = allPoints[a];
	allPoints[a] = allPoints[b];
	allPoints[b] = tmp;
	return true;
}

/*---------------------------------------------------------------------
	Erase pair of points colinears with P[0], and coincident with themselves
	---------------------------------------------------------------------*/
bool HullArea::eraseColinearsAndCoincident(void)
{
	std::vector<Point2d>::iterator iti = allPoints.begin()+1;
	while ( (iti+1) < allPoints.end() )
	{
		std::vector<Point2d>::iterator itj = iti+1;
		bool breaked = false;
		while( itj < allPoints.end() )
		{
			int a = areaSign(allPoints[0], *iti, *itj);
			if (a == 0) /* iti and itj are collinear with P[0] */
			{ 
				/* Find the point closest from lowest right point, and remove it */
				int x =  abs( iti->x -  allPoints[0].x ) - abs( itj->x -  allPoints[0].x );
				int y =  abs( iti->y -  allPoints[0].y ) - abs( itj->y -  allPoints[0].y );

				if ( (x < 0) || (y < 0) ) 
				{
					iti = allPoints.erase(iti);
					breaked = true;
					break;
				}
				else if ( (x > 0) || (y > 0) ) 
				{
					itj = allPoints.erase(itj);
				}
				else /* points are coincident */ 
				{
					itj = allPoints.erase(itj);
				}
			}
			else
			{
				//erase move the pointer to the next element in the vector
				//if erase hasn't been called, move the pointer
				itj = itj+1;
			}
		}

		if (breaked == false)
		{
			//erase move the pointer to the next element in the vector
			//if erase hasn't been called, move the pointer
			iti = iti+1;
		}
	}
	return true;
}

bool HullArea::doSort(void) 
{
	std::sort(allPoints.begin()+1, allPoints.end(), Compare(*this));
	return true;
}

/*---------------------------------------------------------------------
	compute the area of a triangle thanks to the cross product of a two edges vector
	positive if abc are oriented counter-clockwise (c on the left of ab)
	negative if the triangle is oriented clockwise (c on the right of ab)
	return only the sign of the area
	---------------------------------------------------------------------*/
int HullArea::areaSign( Point2d a, Point2d b, Point2d c ) const
{
	//area2 : equal to 2 times the area of the triangle abc
	double area2 =	( b.x - a.x ) * (double)( c.y - a.y ) -
		( c.x - a.x ) * (double)( b.y - a.y );

	/* The area should be an integer. */
	if      ( area2 >  0.5 ) return  1;
	else if ( area2 < -0.5 ) return -1;
	else                     return  0;
}

/*---------------------------------------------------------------------
	Returns true iff c is strictly to the left of the directed
	line through a to b.
	---------------------------------------------------------------------*/
bool HullArea::left( Point2d a, Point2d b, Point2d c )
{ 
	return  areaSign( a, b, c ) > 0;
}
