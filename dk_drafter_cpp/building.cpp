#include "building.h"

/*=== Constructors ===*/
Building::Building() {}
Building::Building(Map* map) : map(map){
	extractRooms();
}
void Building::extractRooms() {
	std::vector<std::string> activityTypes = map->getActivityTypes();
	std::cout << "\n\nActivity MAP\n\n";
	map->drawPlayersToConsole();
	for (size_t activityTypeID = 0; activityTypeID < activityTypes.size(); activityTypeID++) {
		std::shared_ptr<TileDefinition> tileDefinition = Tile::TILE_DEFINITIONS_KEYWORDED[activityTypes[activityTypeID]];
		Map* activityMap = map->clone();
		std::cout << "\n--- Activity " << tileDefinition->label << " ---\n";
		activityMap->removeOwnableBlocksExcept(tileDefinition->label, Tile::TILE_DEFINITIONS_KEYWORDED[Tile::DIRT], 1);
		activityMap->drawPlayersToConsole();
		std::cout << "\n===";
		activityMap = activityMap->extractPlayerMap(1);
		activityMap->drawToConsole();
		Room room = Room(activityMap, tileDefinition);
		rooms.push_back(room);
		return;
	}
}