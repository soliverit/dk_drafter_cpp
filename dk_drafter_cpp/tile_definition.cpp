#include "tile_definition.h"

TileDefinition::TileDefinition(){}
TileDefinition::TileDefinition(std::string keyword, std::string label, std::tuple<int, int, int> colour) : keyword(keyword), label(label), colour(colour), ownable(true){}
TileDefinition::TileDefinition(std::string keyword, std::string label, bool canBeOwned,  std::tuple<int, int, int> colour) : keyword(keyword), label(label), colour(colour), ownable(canBeOwned){}
