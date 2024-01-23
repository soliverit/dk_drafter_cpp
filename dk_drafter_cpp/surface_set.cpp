#include  "surface_set.h"

/*=== Constructors ===*/
SurfaceSet::SurfaceSet(){}
/*=== Static members ===*/
const std::string SurfaceSet::NORTH			= "North";
const std::string SurfaceSet::EAST			= "East";
const std::string SurfaceSet::SOUTH			= "South";
const std::string SurfaceSet::WEST			= "West";
const std::string SurfaceSet::HORIZONTAL	= "Horizontal";
/*=== Instance methods ===*/
void SurfaceSet::addTile(ORIENTATION orientation,	Tile tile) {
	tiles[orientation][tile.definition->label].push_back(tile);
}
std::vector<Tile> SurfaceSet::getTiles(ORIENTATION orientation, std::string tileDefinitionType) {
	return tiles[orientation][tileDefinitionType];
}
std::string toInp();