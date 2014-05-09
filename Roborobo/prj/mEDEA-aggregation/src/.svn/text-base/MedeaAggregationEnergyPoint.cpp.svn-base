#include "World/EnergyPoint.h"

#include "RoboroboMain/roborobo.h"
#include "Utilities/Misc.h"
#include "Utilities/SDL_gfxPrimitives.h"

#include "World/World.h"

#include "mEDEA-aggregation/include/MedeaAggregationEnergyPoint.h"

MedeaAggregationEnergyPoint::MedeaAggregationEnergyPoint(int inUid, int inHarvestingOrganismSize, int inMargin)
{
	harvestingOrganismSize = inHarvestingOrganismSize;
	uid = inUid;
	margin = inMargin;
	gProperties.checkAndGetPropertyValue("energyPointRadius", &_radius, true);
	gProperties.checkAndGetPropertyValue("VisibleEnergyPoint", &_visible, true);

	//the energy point becomes active ones the position has been initialized
	_active = false;

	gProperties.checkAndGetPropertyValue("energyPointRespawnLagMaxValue", &energyPointRespawnLagMaxValue, true);
	MedeaAggregationSharedData::energyPointRespawnLagMaxValue = energyPointRespawnLagMaxValue;
	_respawnLag = energyPointRespawnLagMaxValue ;
	_internLagCounter = 0;
	
	_energyPointValueIsLocal = false; // use gEnergyPointValue
	_energyPointValue = MedeaAggregationSharedData::energyPointValueMax;

	_respawnMethodIsLocal = false; // use gEnergyPointRespawnLagMaxValue
	_respawnLagMaxValue = energyPointRespawnLagMaxValue; // default, not used if _respawnMethodIsLocal is true

}

void MedeaAggregationEnergyPoint::init()
{
	double x = 0.0;
	double y = 0.0;

	generatePosition(harvestingOrganismSize,margin,x,y);

	bool checkBackground = true;
	for (int xCheck = x - _radius ; xCheck < x + _radius ; xCheck++)
	{
		for (int yCheck = y - _radius ; yCheck < y + _radius; yCheck ++)
		{
			if ((sqrt ( pow (xCheck-x,2) + pow (yCheck - y,2))) < _radius)
			{
				Uint8 r, g, b;
				Uint32 pixel = getPixel32( gZoneImage, xCheck, yCheck);
				SDL_GetRGB(pixel,gZoneImage->format,&r,&g,&b); 
				if ((r== 234 && g==183 && b==31) || (r== 100 && g==140 && b==255))
				{
					checkBackground = false;
					break;
				}
			}
		}
		if (checkBackground == false) break ;
	}

	//orange : 234 183 31
	//blue : 100 140 255
	//search positions until find a new random position where there is no orange or blue stuff
	while (checkBackground == false)
	{
		generatePosition(harvestingOrganismSize,margin,x,y);
		checkBackground = true;
		for (int xCheck = x - _radius ; xCheck < x + _radius ; xCheck++)
		{
			for (int yCheck = y - _radius ; yCheck < y + _radius; yCheck ++)
			{
				if ((sqrt ( pow (xCheck-x,2) + pow (yCheck - y,2))) < _radius)
				{
					Uint8 r, g, b;
					Uint32 pixel = getPixel32( gZoneImage, xCheck, yCheck);
					SDL_GetRGB(pixel,gZoneImage->format,&r,&g,&b); 
					if ((r== 234 && g==183 && b==31) || (r== 100 && g==140 && b==255))
					{
						checkBackground = false;
						break;
					}
				}
			}
			if (checkBackground == false) break ;
		}
	} 
	_position = Point2d(x,y);

	_xCenterPixel = x;
	_yCenterPixel = y;

	_fixedLocation = true;
	_active = true;

	if ( _visible)
	{
		display();	
	}
}

MedeaAggregationEnergyPoint::~MedeaAggregationEnergyPoint()
{
	//nothing to do
}

void MedeaAggregationEnergyPoint::display()
{
	Uint32 color;

	for (Sint16 xColor = _xCenterPixel - Sint16(_radius) ; xColor < _xCenterPixel + Sint16(_radius) ; xColor++)
	{
		for (Sint16 yColor = _yCenterPixel - Sint16(_radius) ; yColor < _yCenterPixel + Sint16 (_radius); yColor ++)
		{
			if ((sqrt ( pow (xColor-_xCenterPixel,2) + pow (yColor - _yCenterPixel,2))) < _radius)
			{
				if ((harvestingOrganismSize == -1) || (harvestingOrganismSize == 1))
				{
					//orange : 234 183 31
					color = 0xeab71fff ;
				}
				else
				{
					//blue : 100 140 255
					color = 0x648cffff ;
				}

				pixelColor(gZoneImage, xColor, yColor, color);
				pixelColor(gBackgroundImage, xColor, yColor, color);
			}
		}
	}
}

void MedeaAggregationEnergyPoint::hide()
{
	Uint32 color = 0xffffffff;
	for (Sint16 xColor = _xCenterPixel - Sint16(_radius) ; xColor < _xCenterPixel + Sint16(_radius) ; xColor++)
	{
		for (Sint16 yColor = _yCenterPixel - Sint16(_radius) ; yColor < _yCenterPixel + Sint16 (_radius); yColor ++)
		{
			if ((sqrt ( pow (xColor-_xCenterPixel,2) + pow (yColor - _yCenterPixel,2))) < _radius)
			{
				pixelColor(gZoneImage, xColor, yColor, color);
				pixelColor(gBackgroundImage, xColor, yColor, color);
			}
		}
	}
}

void MedeaAggregationEnergyPoint::step()
{
	if ( !_active ) // case: harvested. respawn delay?
	{
		_internLagCounter++;

		if ( _internLagCounter >= _respawnLag ) // Note: in current implementation, _respawnLag is equal to gEnergyPointRespawnLagMaxValue.
		{
			if ( _respawnMethodIsLocal == true )
				_respawnLag = _respawnLagMaxValue; // each energy point gets its own respawn lag
			else
				_respawnLag = energyPointRespawnLagMaxValue; // all energy points share the respawn lag value
			_energyPointValue = MedeaAggregationSharedData::energyPointValueMax;

			_internLagCounter = 0;
			_active = true;


			if ( ! _fixedLocation )
			{
				double x = (rand() % (gAreaWidth-20)) + 10;
				double y = (rand() % (gAreaHeight-20)) + 10;
				_position = Point2d(x,y);

				_xCenterPixel = x;
				_yCenterPixel = y;
			}
			if ( _visible )
			{
				display();
			}
		}
	}
	else
	{
		if ( _visible && gDisplayMode == 0 )
		{
			// NOTE: calling the display method, re-display the food image (but have
			// no impact on simulation whatsoever as food harvesting is based on 
			// computed euclidian distance btw agents and energy points). This is used
			// to guarantee a "nice and clean" display as overlapping energy points 
			// may result in cropped remaining points whenever a point is taken (ie.
			// the actual implementation implies deleting the energy point region
			// that was harvested, without any regards to overlaps).
			// IT IS IMPORTANT TO NOTE THAT SYSTEMATIC CALLS TO DISPLAY MAY 
			// SIGNIFICANTLY SLOW DOWN THE SIMULATION! As a consequence, it should
			// be called with care, and should NOT be called if not be called when
			// the simulation is running fast (e.g. batch mode).
			// Current implementation: 
			//	calls only if display mode is normal speed
			//	and if property "EnergyPoints_alwaysRender" is true
			
			if ( gEnergyPoints_alwaysRender ) // NOTE: the hide() method but be called externally (otw: displayed points may not exist anymore)
				display();
		}
	}
}

double MedeaAggregationEnergyPoint::getRadius()
{
	return _radius;
}

double MedeaAggregationEnergyPoint::getHarvestingOrganismSize()
{
	return harvestingOrganismSize;
}

void MedeaAggregationEnergyPoint::generatePosition(int inHarvestingOrganismSize, int margin, double &x, double &y)
{
	if (inHarvestingOrganismSize == -1)
	{
		x = (rand() % (gAreaWidth-20)) + 10;
		y = (rand() % (gAreaHeight-20)) + 10;
	}
	else if (inHarvestingOrganismSize == 1)
	{
		x = (rand() % ((gAreaWidth/2)-10+margin)) + 10;
		y = (rand() % (gAreaHeight-20)) + 10;
	}
	else if (inHarvestingOrganismSize == 2)
	{
		x = (rand() % ((gAreaWidth/2)-10+margin)) + ((gAreaWidth/2)-margin);
		y = (rand() % (gAreaHeight-20)) + 10;
	}
}
