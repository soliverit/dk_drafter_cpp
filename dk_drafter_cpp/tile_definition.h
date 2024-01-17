#pragma once
/*===
	Includes
===*/
// Native 
#include <string>
#include <tuple>s
// Project
#include "player.h"
/*

*/
class TileDefinition {
public:
	/*=== Constructor ===*/
	TileDefinition();
	TileDefinition(std::string keyword, std::string label, std::tuple<int, int, int>	colour );
	TileDefinition(std::string keyword, std::string label,bool canBeOwned, std::tuple<int, int, int>	colour );
	std::string keyword;
	std::string label;
	std::tuple<unsigned int, unsigned int, unsigned int> colour;
	bool ownable;
};