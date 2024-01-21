#include  "surface_set.h"

/*=== Constructors ===*/
SurfaceSet::SurfaceSet(){}
/*=== Instance methods ===*/
void SurfaceSet::addTile(ORIENTATION orientation,	Tile tile) {
	tiles[orientation][tile.definition->label].push_back(tile);
}
std::vector<Tile> SurfaceSet::getTiles(ORIENTATION orientation, std::string tileDefinitionType) {
	return tiles[orientation][tileDefinitionType];
}