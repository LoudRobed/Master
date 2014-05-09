#include "World/EnergyPoint.h"

#include "RoboroboMain/roborobo.h"
#include "Utilities/Misc.h"
#include "Utilities/SDL_gfxPrimitives.h"

#include "World/World.h"

#include "mEDEA-comm/include/MedeaCommEnergyPoint.h"

MedeaCommEnergyPoint::MedeaCommEnergyPoint(void)
{
	double x = (rand() % (gAreaWidth-20)) + 10;
	double y = (rand() % (gAreaHeight-20)) + 10;

	gProperties.checkAndGetPropertyValue("energyPointRadius", &_radius, true);


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
		x = (rand() % (gAreaWidth-20)) + 10;
		y = (rand() % (gAreaHeight-20)) + 10;
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

	gProperties.checkAndGetPropertyValue("VisibleEnergyPoint", &_visible, true);
	if ( _visible)
	{
		display();	
	}

	gProperties.checkAndGetPropertyValue("energyPointRespawnLagMaxValue", &energyPointRespawnLagMaxValue, true);
	_respawnLag = energyPointRespawnLagMaxValue ;
	_internLagCounter = 0;
	
	_energyPointValueIsLocal = false; // use gEnergyPointValue
	_energyPointValue = MedeaCommSharedData::energyPointValueMax;

	_respawnMethodIsLocal = false; // use gEnergyPointRespawnLagMaxValue
	_respawnLagMaxValue = energyPointRespawnLagMaxValue; // default, not used if _respawnMethodIsLocal is true

	gProperties.checkAndGetPropertyValue("harvestingThreshold", &harvestingThreshold, true);
	gProperties.checkAndGetPropertyValue("harvestingRate", &harvestingRate, true);
	gProperties.checkAndGetPropertyValue("regrowRate", &regrowRate, true);
}

MedeaCommEnergyPoint::~MedeaCommEnergyPoint()
{
	//nothing to do
}

void MedeaCommEnergyPoint::display()
{
	Uint32 color;
	//orange : 234 183 31
	//blue : 100 140 255
	color = 0xeab71fff;

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

void MedeaCommEnergyPoint::hide()
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

void MedeaCommEnergyPoint::step()
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
			_energyPointValue = MedeaCommSharedData::energyPointValueMax;

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
		if ( _energyPointValue < MedeaCommSharedData::energyPointValueMax)
		{
			_energyPointValue += regrowRate;
		}
		if ( _energyPointValue > MedeaCommSharedData::energyPointValueMax)
		{
			_energyPointValue = MedeaCommSharedData::energyPointValueMax;
		}

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

double MedeaCommEnergyPoint::getRadius()
{
	return _radius;
}

double MedeaCommEnergyPoint::getHarvestingThreshold()
{
	return harvestingThreshold;
}

double MedeaCommEnergyPoint::getEnergy()
{	
	double toReturn = 0.0;
	if (_energyPointValue < harvestingRate)
	{
		toReturn = _energyPointValue;
		_active = false;
		hide();
	}
	else
	{
		toReturn = harvestingRate;
		_energyPointValue -= harvestingRate;
	}
	return toReturn;	
}
