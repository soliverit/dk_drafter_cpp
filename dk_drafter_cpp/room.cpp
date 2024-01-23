#include "room.h"

/*=== Constructors ===*/
Room::Room(){}
Room::Room(Map* floorPlan, std::shared_ptr<TileDefinition> activity) : floorPlan(floorPlan), activity(activity), height(3){
	extractGeometry();
}
SurfaceSet Room::extractGeometry() {
	// Get activity tiles
	std::vector<Tile> tiles = floorPlan->getTilesByType(activity->keyword);
	/* Build the SurfaceSet */
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
/* Get the room area in terms No. of activityType Tiles */
float Room::area() {
	float area = 0;
	for (size_t rowID = 0; rowID < floorPlan->height; rowID++)
		for (size_t cellID = 0; cellID < floorPlan->width; cellID++)
			if (floorPlan->tiles[rowID][cellID].definition->label == activity->label)
				area += 1;
	return area;
}
/* Room's X position on the world coordinate system */
size_t Room::wcsX() { return floorPlan->wcsX; }
/* Room's Y position on the world coordinate system */
size_t Room::wcsY() { return floorPlan->wcsY; }