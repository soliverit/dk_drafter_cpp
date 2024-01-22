#pragma once
/*===
	Includes
===*/
// Native 
#include <string>
#include <tuple>
// Project
#include "player.h"
/*

*/
class TileDefinition {
public:
	/*=== Constructor ===*/
	/* Default constructor */
	TileDefinition();
	/* Construct with common properties. Asume the TileDefinition is ownable*/
	TileDefinition(std::string keyword, std::string label, std::tuple<int, int, int>	colour );
	/* Construct with comoon properties. Explicitly define if it is ownable */
	TileDefinition(std::string keyword, std::string label,bool canBeOwned, std::tuple<int, int, int>	colour );
	/* Term for the Tile. E.g LAIR, HATCHERY */
	std::string keyword;
	/* Character code for the Tile. E.g l = LAVA, ha = HATCHERTY */
	std::string label;
	/* Colour: TODO: REMOVE ME. Isn't used, won't be used. */
	std::tuple<unsigned int, unsigned int, unsigned int> colour;
	/* Can a Player own this Tile type? */
	bool ownable;
};