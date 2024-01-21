#pragma once
#define TILE_MAP_SIZE 128
/*===
	Includes
===*/
// Native 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// Project
#include "tile.h"
#include "player.h"
/*
	Map: The DK map - Tile array without Player association
*/
class Map {
public:
	static const int MAP_SIZE;
	/*=== Constructors ===*/
	/* Default */
	Map();
	/* Construct with custom size (doesn't change tiles[][] size */
	Map(size_t width, size_t height);
	/* Construct with custom size and world coordinate system position*/
	Map(size_t width, size_t height, size_t wcsX, size_t wcsY);
	/* Construct with custom size and some predefined Players */
	Map(size_t width, size_t height, std::vector<Player> players);
	/* Construct with custom size, world coordinate position and predefined Players */
	Map(size_t width, size_t height, size_t wcsX, size_t wcsY, std::vector<Player> players);
	/*=== Static members ===*/
	/* Compass directions */
	
	// Instance methods
	/* Replace all Tiles in the tiles[][] array with unowned Tile::DIRT Tiles*/
	void clear();
	/* Add a Player to the Map if they're aren't on it already. */
	void addPlayer(Player player);
	/* Get list of space activities */
	std::vector<std::string> getActivityTypes();
	/*
		Parse a CSV file:

		Read a CSV file with text values from the list below to construct a Map() of
		the dungeon represented by the CSV.

		Labels have two components
			1) The Tile type KEYWORD. E.g "La" = Lair
			2)[optional] The ID of the Player that owns it.

		If a Player doesn't exist, they are created and added to the Map().

		{"u", TileDefinition("u", "UNCLAIMED", std::tuple<int, int, int>(233, 022, 140))},
		{"ca", TileDefinition("ca", "CLAIMED", std::tuple<int, int, int>(0,0,153))},
		{"d", TileDefinition("d", "DIRT", std::tuple<int, int, int>(0,0,0))},
		{"r", TileDefinition("r", "REINFORCED", std::tuple<int, int, int>(255, 255, 255))},
		{"w", TileDefinition("w", "WATER", std::tuple<int, int, int>(0, 176, 240))},
		{"l", TileDefinition("l", "LAVA", std::tuple<int, int, int>(204, 176, 0))},
		{"i", TileDefinition("i", "LAVA", std::tuple<int, int, int>(102, 51, 0))},
		{"ba", TileDefinition("ba", "BARRACKS", std::tuple<int, int, int>(160, 43, 147))},
		{"br", TileDefinition("br", "BRIDGE", std::tuple<int, int, int>(126, 53, 14))},
		{"gr", TileDefinition("gr", "GRAVEYEARD", std::tuple<int, int, int>(15, 158, 213))},
		{"gu", TileDefinition("gu", "GUARD_POST", std::tuple<int, int, int>(116, 116, 116))},
		{"ha", TileDefinition("ha", "HATCHERY", std::tuple<int, int, int>(233, 113, 50))},
		{"la", TileDefinition("la", "LAIR", std::tuple<int, int, int>(21, 96, 130))},
		{"li", TileDefinition("li", "LAVA", std::tuple<int, int, int>(112, 48, 160))},
		{"pr", TileDefinition("pi", "PRISON", std::tuple<int, int, int>(241, 169, 131))},
		{"sc", TileDefinition("sc", "SCAVENGER_ROOM", std::tuple<int, int, int>(173, 173, 173))},
		{"te", TileDefinition("te", "TEMPLE", std::tuple<int, int, int>(173, 173, 173))},
		{"to", TileDefinition("to", "TORTURE_CHAMBER", std::tuple<int, int, int>(192, 0, 0))},
		{"tr", TileDefinition("tr", "TRAINING_ROOM", std::tuple<int, int, int>(60, 125, 34))},
		{"ta", TileDefinition("ta", "TREASURE_ROOM", std::tuple<int, int, int>(255, 153, 0))},
		{"wo", TileDefinition("wo", "WORKSHOP", std::tuple<int, int, int>(255, 192, 0))}
	*/
	bool parseCSV(const std::string& csvPath);
	/* Find a Player by their ID */
	std::shared_ptr<Player> findPlayer(int id);
	/* Draw the Map to console: Just a dirty drawer for debugging or whatever */
	void drawToConsole();
	void drawPlayersToConsole();
	/* Reconstruct the map with only Player(playerID)'s Tiles. Everything else is dirt */
	Map* extractPlayerMap(int playerID);
	/* Get all the tiles from a Map of a specific kind */
	std::vector<Tile> getTilesByType(std::string type);
	/* Create a clone */
	Map* clone();
	/* Merge another Map by replacing the original Map tiles with any non-DIRT tiles from the passed Map */
	void merge(Map* map);
	/*=== Map filtering / modding ===*/
	/* Find blocks by label and replace them with another. Assign to a player, 0 for null player */
	void replaceBlocks(std::string find, std::shared_ptr<TileDefinition> replaceWith, int playerID);
	/* Replace all blocks except one kind. Replace everything else with a given block. Assign to player, 0 for null player */
	void removeBlocksExcept(std::string find, std::shared_ptr<TileDefinition> replaceWith, int playerID);
	void removeOwnableBlocksExcept(std::string find, std::shared_ptr<TileDefinition> replaceWith, int playerID);
	// Instance members
	size_t width;									// Width of the Map independent of the Tile column count
	size_t height;									// Height of the Map independent of the Tile row count
	size_t wcsX;									// World coordinate system X (for derived Maps)
	size_t wcsY;									// World coordinate system Y (for derived Maps)
	Tile	tiles[TILE_MAP_SIZE][TILE_MAP_SIZE];	// Full size array of Tiles independent of the Map width and height
	std::vector<Player> players;					// Players...
};