#pragma once
/*===
	Includes
===*/
// Native 

// Project
#include "map.h"
#include "tile.h"
#include "tile_definition.h"

class Room {
public:
	Room();
	Room(Map* floorPlan, std::shared_ptr<TileDefinition> activity);
	// Instance methods
	void extractGeometry();
	// Instance members
	Map* floorPlan;
	std::shared_ptr<TileDefinition> activity;
	std::vector<Tile> floorTiles;
	std::unordered_map<std::string, std::vector<Tile>> wallTiles;
	float height;
	unsigned int sbemID;
};