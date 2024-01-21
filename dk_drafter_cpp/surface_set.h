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
	/*=== Instance methods ===*/
	/* Add a Tile to the set */
	void addTile(ORIENTATION orientation, Tile tile);
	std::vector<Tile> getTiles(ORIENTATION orientation, std::string tileDefinitionLabel);
	/*=== Instance members ===*/
protected:
	std::unordered_map<ORIENTATION, std::unordered_map<std::string, std::vector<Tile>>> tiles;
};