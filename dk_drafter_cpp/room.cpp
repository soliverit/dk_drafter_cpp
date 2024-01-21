#include "room.h"

/*=== Constructors ===*/
Room::Room(){}
Room::Room(Map* floorPlan, std::shared_ptr<TileDefinition> activity) : floorPlan(floorPlan), activity(activity), height(3){
	extractGeometry();
}
SurfaceSet Room::extractGeometry() {
	// Get activity tiles
	std::vector<Tile> tiles = floorPlan->getTilesByType(activity->keyword);
	// Get envelope Tiles
	SurfaceSet adjacencies;
	for (size_t tileID = 0; tileID < tiles.size(); tileID++) {
		size_t x	= tiles[tileID].x;
		size_t y	= tiles[tileID].y;
		if(x - 1 >= 0) adjacencies.addTile(SurfaceSet::West, floorPlan->tiles[y][x - 1]);
		if(x + 1 < floorPlan->width) adjacencies.addTile(SurfaceSet::East, floorPlan->tiles[y][x + 1]);
		if(y - 1 >= 0) adjacencies.addTile(SurfaceSet::North, floorPlan->tiles[y - 1][x]);
		if(y + 1 < floorPlan->height) adjacencies.addTile(SurfaceSet::South, floorPlan->tiles[y + 1][x]);
	}
	return adjacencies;
}
/*=== Getters ===*/
size_t Room::wcsX() { return floorPlan->wcsX; }
size_t Room::wcsY() { return floorPlan->wcsY; }