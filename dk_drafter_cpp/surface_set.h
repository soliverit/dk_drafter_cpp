#pragma once
/*===
	Includes
===*/
// Native 
#include <unordered_map>
// Project
#include "tile.h"
/*
	
*/
class SurfaceSet {
public:
	/*=== Constructors ===*/
	SurfaceSet();
	/*=== Static members ===*/
	enum ORIENTATION {	// No need for diagonals (souths-west etc)
		North,
		East,
		South,
		West
	};
	static const std::string NORTH;
	static const std::string EAST;
	static const std::string SOUTH;
	static const std::string WEST;
	static const std::string HORIZONTAL;
	/*=== Instance methods ===*/
	/* Add a Tile to the set */
	void addTile(ORIENTATION orientation, Tile tile);
	/* Return Tiles associated with a compass direction and TileDefintion (yeah, should've done enums at the start) */
	std::vector<Tile> getTiles(ORIENTATION orientation, std::string tileDefinitionLabel);
	/*=== Instance members ===*/
protected:
	/* The Tile map. Keep it protected to enforce read/write */
	std::unordered_map<ORIENTATION, std::unordered_map<std::string, std::vector<Tile>>> tiles;
};