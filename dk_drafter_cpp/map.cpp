/*==
	Includes
===*/
// Native
// Project
#include "map.h"
#include "tile.h"
Map::Map() : width(TILE_MAP_SIZE), height(TILE_MAP_SIZE){}
Map::Map(size_t width, size_t height) : width(width), height(height) {
	// Fill the full map (TILE_MAP_SIZE, not x*y) with Tile::DIRT.
	clear();
}
Map::Map(size_t width, size_t height, std::vector<Player> players) : width(width), height(height), players(players) {
	// Fill the full map (TILE_MAP_SIZE, not x*y) with Tile::DIRT.
	clear();
}
void Map::clear() {
	/*
		Define the Tile array

		Note: The Tile array and effective Map size are independent. Tile array size is
		the maximum level size (CHECK THAT), whereas the Map width/height are the chunk
		of Map that's covered in the model.

		For example, the full map is 128*128, but a small map might be 64*64.
	*/
	for (size_t rowID = 0; rowID < TILE_MAP_SIZE; rowID++)
		for (size_t cellID = 0; cellID < TILE_MAP_SIZE; cellID++) {
				tiles[rowID][cellID]	= Tile(Tile::TILE_DEFINITIONS_KEYWORDED[Tile::DIRT], nullptr, cellID, rowID);
		}
}
std::shared_ptr<Player> Map::findPlayer(int id) {
	for (size_t playerID = 0; playerID < players.size(); playerID++)
		if (players[playerID].getID() == id)
			return std::make_shared<Player>(players[playerID]);	// make_shared necessary?
	return nullptr;
}
void Map::addPlayer(Player player) {
	for (size_t playerID = 0; playerID < players.size(); playerID++)
		if (player.getID() == players[playerID].getID())
			return;
	players.push_back(player);
}

/*=== Parseing ===*/
bool Map::parseCSV(const std::string& csvPath) {
	/*
		Open the CSV and make sure it's readable
	*/
	std::fstream csv(csvPath);
	// Make sure it is readable (it exists and isn't open with something else)
	if (!csv.good())
		return false;	// Maybe throw something here. Need to log it somehow
	/*
		Read the CSV rows

		Read lines from the CSV until either the end is reached or rowID == Map.height.
	*/
	std::string row;
	int rowID = 0;
	// Read the lines
	while (std::getline(csv, row)) {
		/*
			Sanitation time!

			Some csvs start with "´╗┐" or other stupid stuff. So we want to remove it 
			by retaining only relevant characters. We don't need spaces since the 
			Tile::parseLabel method ignores them, so we can remove them as well.
		*/
		
		std::vector<std::string> rowData;
		row.erase(std::remove_if(row.begin(), row.end(), [](unsigned char c) {
			return !std::isalnum(c) && !std::isalpha(c) && c != ',';
			}), row.end());
		std::stringstream rowStream(row);
		std::string cell;
		int cellID = 0;
		while (std::getline(rowStream, cell, ',')) {
			std::tuple<bool, std::shared_ptr<TileDefinition>, int> tileInfo = Tile::parseLabel(cell);
			if (!std::get<0>(tileInfo))
				std::cout << "\nSomething's wrong with label: " << cell;
			
			int playerID					= std::get<2>(tileInfo);
			std::shared_ptr<Player> player	= findPlayer(playerID);
			if (player == nullptr) {
				player  = std::make_shared<Player>(Player("Player " + std::to_string(playerID), playerID));
				addPlayer(*player);
			}
				
			tiles[rowID][cellID].update(std::get<1>(tileInfo), player);
			// We only care about the Map defined boundaries (maybe just do it anyway?)
			cellID++;
			if (cellID == width)
				break;

		}
		rowID++;
		// We only care about the Map defined boundaries (maybe just do it anyway?)
		if (rowID == height)
			break;
	}

	
	return true;
}
/*=== Getters ===*/
std::vector<std::string> Map::getActivityTypes() {
	/* Create map of all Tile types with flag for is present in Map */
	std::unordered_map<std::string, bool> activityTypes;
	for (size_t activityTypeID = 0; activityTypeID < Tile::NO_OWNABLE_TYPES; activityTypeID++)
		activityTypes[Tile::OWNABLE_TYPES[activityTypeID]] = false;
	/* Flag Tile types present in the Map as present */
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			activityTypes[tiles[rowID][cellID].definition->label] = true;
	/* Extract the list of present Tile types from the Tile type is present map */
	std::vector<std::string> activities;
	for (size_t activityTypeID = 0; activityTypeID < Tile::NO_OWNABLE_TYPES; activityTypeID++)
		if (activityTypes[Tile::OWNABLE_TYPES[activityTypeID]])
			activities.push_back(Tile::OWNABLE_TYPES[activityTypeID]);
	return activities;
}
/* Get Tiles by their type */
std::vector<Tile> Map::getTilesByType(std::string type) {
	std::vector<Tile> matchedTiles;
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			if (tiles[rowID][cellID].definition->keyword == type)
				matchedTiles.push_back(tiles[rowID][cellID]);
	return matchedTiles;
}
/*=== Extract, filter, merge, clone ===*/
Map* Map::extractPlayerMap(int id) {
	/*
		Get the dimensions of the Player's Map

		The Player's Map isn't like the normal Map. It's min/max indexed such that its
		zero-index tiles[0][0] is the lowest row number and the lowest cell(column) number. For
		example, if tiles[10][50] is the lowest row and tiles[50][10] is the lowest column, the
		zero-index relative to the base Map is tiles[10][10].

		Additionally, the Player Map dimensions are min/max adjusted also. For example,
		if tiles [60][20] was the max row and tiles[20][60] was the highest column, then
		the relative Map is defined from the base Map as follows:

			min x:	10	min y:	10
			max x:	60	max y:	60
			width:	50	height:	50
	*/
	size_t minX = std::numeric_limits<size_t>::max();
	size_t minY = std::numeric_limits<size_t>::max();
	size_t maxX = std::numeric_limits<size_t>::min();
	size_t maxY = std::numeric_limits<size_t>::min();
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++) {
			if (tiles[rowID][cellID].definition->ownable && tiles[rowID][cellID].ownedBy(id)) {
				if (cellID < minX) minX = cellID;
				if (cellID > maxX) maxX = cellID;
				if (rowID < minY) minY = rowID;
				if (rowID > maxY) maxY = rowID;
			}
		}
	minX--;
	maxX++;
	minY--;
	maxY++;
	size_t playerMapWidth = maxX - minX  + 1;
	size_t playerMapHeight = maxY - minY + 1;

	/*
		Build the Player Map
	*/
	Map* playerMap = new Map(playerMapWidth, playerMapHeight, players);
	for (size_t rowID = minY; rowID <= maxY; rowID++)
		for (size_t cellID = minX; cellID <= maxX; cellID++) {
			Tile tile = tiles[rowID][cellID];
			if (tile.ownedBy(id) || ! tile.definition->ownable) 
				playerMap->tiles[rowID - minY][cellID - minX].update(tiles[rowID][cellID].definition, findPlayer(id), cellID - minX, rowID - minY);
		}
	return playerMap;
}

/* Clone the map */
Map* Map::clone() {
	Map* map = new Map(width, height);
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			map->tiles[rowID][cellID].update(tiles[rowID][cellID].definition, tiles[rowID][cellID].player);
	return map;
}
void Map::merge(Map* map) {
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			if(tiles[rowID][cellID].definition->label == Tile::DIRT)
				tiles[rowID][cellID].update(map->tiles[rowID][cellID].definition, map->tiles[rowID][cellID].player);
}
/*=== Map filtering / modding ===*/
void Map::replaceBlocks(std::string find, std::shared_ptr<TileDefinition> replaceWith, int playerID) {
	for(size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++) 
			if (tiles[rowID][cellID].definition->label == find)
				tiles[rowID][cellID].update(replaceWith, findPlayer(playerID));
}
void Map::removeBlocksExcept(std::string keep, std::shared_ptr<TileDefinition> replaceWith, int playerID) {
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			if (tiles[rowID][cellID].definition->label != keep)
				tiles[rowID][cellID].update(replaceWith, findPlayer(playerID));
}
void Map::removeOwnableBlocksExcept(std::string keep, std::shared_ptr<TileDefinition> replaceWith, int playerID) {
	for (size_t rowID = 0; rowID < height; rowID++)
		for (size_t cellID = 0; cellID < width; cellID++)
			if (tiles[rowID][cellID].definition->ownable && tiles[rowID][cellID].definition->label != keep)
				tiles[rowID][cellID].update(replaceWith, findPlayer(playerID));
}
/*=== Drawing and what not ===*/

void Map::drawToConsole() {

	for (size_t rowID = 0; rowID < height; rowID++) {
		std::string row;
		for (size_t cellID = 0; cellID < width; cellID++) {
			Tile tile = tiles[rowID][cellID];
			if (tile.definition->label == Tile::DIRT)
				row += "o";
			else if (tile.definition->label == Tile::LAVA)
				row += "l";
			else if (tile.definition->label == Tile::WATER)
				row += "w";
			else if (tile.definition->label == Tile::REINFORCED)
				row += "r";
			else if (tile.definition->label == Tile::IMPENETRABLE)
				row += "i";
			else
				row += ":";
		}
		std::cout << "\n" << row;
	}

}
void Map::drawPlayersToConsole() {

	for (size_t rowID = 0; rowID < height; rowID++) {
		std::string row;
		for (size_t cellID = 0; cellID < width; cellID++) {
			Tile tile = tiles[rowID][cellID];
			if (tile.definition->ownable)
				row += std::to_string(tile.player->getID());
			else
				row += "-";
		}
		std::cout << "\n" << row;
	}

}