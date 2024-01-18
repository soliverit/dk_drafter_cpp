#include "room.h"

/*=== Constructors ===*/
Room::Room(){}
Room::Room(Map* floorPlan, std::shared_ptr<TileDefinition> activity) : floorPlan(floorPlan), activity(activity), height(3) {
	extractGeometry();
}
void Room::extractGeometry() {
	// Get activity tiles
	std::vector<Tile> tiles = floorPlan->getTilesByType(activity->keyword);
	// Get envelope Tiles
	std::unordered_map<std::string, int> adjacencies;
	for (size_t tileID = 0; tileID < tiles.size(); tileID++) {
		size_t x = tiles[tileID].x;
		size_t y = tiles[tileID].y;
		adjacencies[floorPlan->tiles[y][x - 1].definition->label] += 1;
		adjacencies[floorPlan->tiles[y][x + 1].definition->label] += 1;
		adjacencies[floorPlan->tiles[y - 1][x].definition->label] += 1;
		adjacencies[floorPlan->tiles[y + 1][x].definition->label] += 1;
	}
	for (size_t envKeywordID = 0; envKeywordID < Tile::NO_ENVIRONMENT_TYPES; envKeywordID++) {
		std::cout << "\nRoom " << activity->label << " has " << adjacencies[Tile::ENVIRONMENT_TYPES[envKeywordID]];
		std::cout << " " <<  Tile::ENVIRONMENT_TYPES[envKeywordID] << " tiles";
	}
}