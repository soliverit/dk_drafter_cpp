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
	// Instance methods
	SurfaceSet extractGeometry();
	/* Global positioning forwarding methods (points to Map->wcsX/wcsY) */
	size_t wcsX();
	size_t wcsY();
	// Instance members
	Map* floorPlan;
	std::shared_ptr<TileDefinition> activity;
	std::vector<Tile> floorTiles;
	std::unordered_map<std::string, std::vector<Tile>> wallTiles;
	float height;
	unsigned int sbemID;
};