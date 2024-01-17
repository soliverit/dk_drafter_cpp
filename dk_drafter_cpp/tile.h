#pragma once
/*===
	Includes
===*/
// Native 
#include <string>
#include <unordered_map>
#include <memory>
// Project
#include "player.h"
#include "tile_definition.h"
/*

*/
class Tile {
public:
	// Constructors
	Tile();
	Tile(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePalyer, int x, int y);
	/*=== Static methods ===*/
	/*
	//	Parse Tile label: 

	//	Take a label intended to represent a tile value and parse it into a 
	//	tuple:
	//		bool:			Label is valid
	//		TileDefinition:	Definition of the Tile. Dirt for " and invalid labels
	//		int:			Player ID. Default 1.
	//*/
	static std::tuple<bool, std::shared_ptr<TileDefinition>, int> parseLabel(std::string label);// {
	// Static members
	static std::unordered_map < std::string, std::shared_ptr<TileDefinition>> TILE_DEFINITIONS_KEYWORDED;	// Keyword indexed Map of Tile Definitions 
	static std::unordered_map<std::string, std::shared_ptr<TileDefinition>>  TILE_DEFINITIONS_LABELED;	// Label indexd Map of Tile Definitions
	
	static const std::string UNCLAIMED;			// Dug but not claimed 
	static const std::string CLAIMED;			// Dug, claimed but no activity
	static const std::string DIRT;				// Not dug
	static const std::string REINFORCED;		// Reinforced wall
	static const std::string WATER;				// Wet stuff
	static const std::string LAVA;				// Hot wet stuff
	static const std::string IMPENETRABLE;		// Unbreakable dirt
	static const std::string BARRACKS;			// Barracks
	static const std::string BRIDGE;			// Barracks
	static const std::string GRAVEYARD;			// Graveyard
	static const std::string GUARD_POST;		// Guard post
	static const std::string HATCHERY;			// hatchery
	static const std::string LAIR;				// Lair
	static const std::string LIBRARY;			// Library
	static const std::string PRISON;			// Prison
	static const std::string SCAVENGER_ROOM;	// Scavenger room
	static const std::string TEMPLE;			// Place of worship
	static const std::string TORTURE_CHAMBER;	// Tortue chamber
	static const std::string TRAINING_ROOM;		// Trainig room
	static const std::string TREASURE_ROOM;		// Treasure room
	static const std::string WORKSHOP;			// Workshop

	static const std::string UNCLAIMED_KEYWORD;	// Dug but not claimed 
	static const std::string CLAIMED_KEYWORD;	// Dug, claimed but no activity
	static const std::string DIRT_KEYWORD;		// Not dug
	static const std::string REINFORCED_KEYWORD;		// Reinforced wall
	static const std::string WATER_KEYWORD;				// Wet stuff
	static const std::string LAVA_KEYWORD;				// Hot wet stuff
	static const std::string IMPENETRABLE_KEYWORD;		// Unbreakable dirt
	static const std::string BARRACKS_KEYWORD;			// Barracks
	static const std::string BRIDGE_KEYWORD;			// Barracks
	static const std::string GRAVEYARD_KEYWORD;			// Graveyard
	static const std::string GUARD_POST_KEYWORD;		// Guard post
	static const std::string HATCHERY_KEYWORD;			// hatchery
	static const std::string LAIR_KEYWORD;				// Lair
	static const std::string LIBRARY_KEYWORD;			// Library
	static const std::string PRISON_KEYWORD;			// Prison
	static const std::string SCAVENGER_ROOM_KEYWORD;	// Scavenger room
	static const std::string TEMPLE_KEYWORD;			// Place of worship
	static const std::string TORTURE_CHAMBER_KEYWORD;	// Tortue chamber
	static const std::string TRAINING_ROOM_KEYWORD;		// Trainig room
	static const std::string TREASURE_ROOM_KEYWORD;		// Treasure room
	static const std::string WORKSHOP_KEYWORD;			// Workshop

	/*=== Instance methods ===*/
	/* Is this tile owned by a Player? */
	bool isOwned();
	/* Is Owned by this Player */
	bool ownedBy(int playerID);
	/* Redefine the tile: Type, Player and location in tiles[][] */
	void update(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePlayer, int x, int y);
	/* Redefine the Tile: Type and owner */
	void update(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePlayer);
	
	/*=== Instance members ===*/
	std::shared_ptr<Player> player;					// The owner or nullptr
	std::shared_ptr<TileDefinition> definition;		// The template properties of the Tile
	int x;											// The cell index in tiles[y][x]
	int y;											// The row index in tiles[y][x]
	std::string path;								// If a file is parsed, this is the path. Either .xlsx or .csv
};