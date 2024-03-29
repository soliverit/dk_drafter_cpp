#pragma once
/*===
	Includes
===*/
// Native 

// Project
#include "map.h"
#include "tile.h"
#include "tile_definition.h"
#include "surface_set.h"
class Room {
public:
	Room();
	Room(Map* floorPlan, std::shared_ptr<TileDefinition> activity);
	/*=== Instance mehtods ===*/
	/* Get a surface set of all the adjacent Tile::ENVIRONMENT_TYPES */
	SurfaceSet extractGeometry();
	/* Get the area (No. of activity floor tiles) */
	float area();
	/* Room's X position on the world coordinate system */
	size_t wcsX();
	/* Room's Y position on the world coordinate system */
	size_t wcsY();
	/*=== Instance members ===*/
	Map* floorPlan;
	/* The TileDefinition that represent the activity. Hatchery, Lair, etc. */
	std::shared_ptr<TileDefinition> activity;
	/* Ceiling height. Used in SbemZone */
	float height;
};