#include "tile.h"

/*=== Static methods ===*/
/*
		Parse Tile label:

		Take a label intended to represent a tile value and parse it into a
		tuple:
			bool:			Label is valid
			TileDefinition:	Definition of the Tile. Dirt for " and invalid labels
			int:			Player ID. Default 1.
	*/
#include <iostream>
std::tuple<bool, std::shared_ptr<TileDefinition>, int> Tile::parseLabel(std::string label) {
	// Empty lables are DIRT
	if (label.length() == 0) {
		return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(true, Tile::TILE_DEFINITIONS_LABELED[DIRT_KEYWORD], 1);
	}
	// Labels should be lower case
	for (size_t charID = 0; charID < label.length(); charID++)
		label[charID] = std::tolower(label[charID]);
	
	// Single character codes are unclaimed/unclaimable, like Lava, water, impenetrable
	if (label.length() == 1) {
		// If the label isn't found, it's invalid
		if (TILE_DEFINITIONS_LABELED.find(label) == TILE_DEFINITIONS_LABELED.end())
			return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(false, TILE_DEFINITIONS_LABELED[DIRT_KEYWORD], 1);
		// Otherwise, it's a valid, unclaimed Tile
		return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(true, TILE_DEFINITIONS_LABELED[label], 1);
	}
	// All other labels have two-character labels
	std::string subLabel = label.substr(0, 2);
	// Two character codes have definitions regardless of whether a Player ID is given
	if (TILE_DEFINITIONS_LABELED.find(subLabel) == TILE_DEFINITIONS_LABELED.end())
		return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(false, TILE_DEFINITIONS_LABELED[DIRT_KEYWORD], 1);
	// There might be a Player ID in there somewhere after the first two characters
	for (size_t charID = 2; charID < label.length(); charID++)
		if (isdigit(label[charID]))
			return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(true, TILE_DEFINITIONS_LABELED[subLabel], int(label[charID]));
	// Oh well, at least we found something. Assign it to Player 1
	return std::tuple<bool, std::shared_ptr<TileDefinition>, int>(true, TILE_DEFINITIONS_LABELED[subLabel], 1);
}
/*
	Block type alias constants
*/
// Labels
const std::string Tile::UNCLAIMED				= "UNCLAIMED";
const std::string Tile::CLAIMED					= "CLAIMED";
const std::string Tile::DIRT					= "DIRT";
const std::string Tile::GOLD					= "GOLD";
const std::string Tile::RUBY					= "RUBY";
const std::string Tile::REINFORCED				= "REINFORCED";
const std::string Tile::WATER					= "WATER";
const std::string Tile::LAVA					= "LAVA";
const std::string Tile::IMPENETRABLE			= "IMPENETRABLE";
const std::string Tile::BARRACKS				= "BARRACKS";
const std::string Tile::BRIDGE					= "BRIDGE";
const std::string Tile::GRAVEYARD				= "GRAVEYARD";
const std::string Tile::GUARD_POST				= "GUARD_POST";
const std::string Tile::HATCHERY				= "HATCHERY";
const std::string Tile::LAIR					= "LAIR";
const std::string Tile::LIBRARY					= "LIBRARY";
const std::string Tile::PRISON					= "PRISON";
const std::string Tile::SCAVENGER_ROOM			= "SCAVENGER_ROOM";
const std::string Tile::TEMPLE					= "TEMPLE";
const std::string Tile::TORTURE_CHAMBER			= "TORTURE_CHAMBER";
const std::string Tile::TRAINING_ROOM			= "TRAINING_ROOM";
const std::string Tile::TREASURE_ROOM			= "TREASURE_ROOM";
const std::string Tile::WORKSHOP				= "WORKSHOP";
// Keywords
const std::string Tile::UNCLAIMED_KEYWORD		= "u";
const std::string Tile::CLAIMED_KEYWORD			= "ca";
const std::string Tile::DIRT_KEYWORD			= "d";
const std::string Tile::GOLD_KEYWORD			= "g";
const std::string Tile::RUBY_KEYWORD			= "y";
const std::string Tile::REINFORCED_KEYWORD		= "r";
const std::string Tile::WATER_KEYWORD			= "w";
const std::string Tile::LAVA_KEYWORD			= "l";
const std::string Tile::IMPENETRABLE_KEYWORD	= "i";
const std::string Tile::BARRACKS_KEYWORD		= "ba";
const std::string Tile::BRIDGE_KEYWORD			= "br";
const std::string Tile::GRAVEYARD_KEYWORD		= "gr";
const std::string Tile::GUARD_POST_KEYWORD		= "gu";
const std::string Tile::HATCHERY_KEYWORD		= "ha";
const std::string Tile::LAIR_KEYWORD			= "la";
const std::string Tile::LIBRARY_KEYWORD			= "li";
const std::string Tile::PRISON_KEYWORD			= "pr";
const std::string Tile::SCAVENGER_ROOM_KEYWORD	= "sc";
const std::string Tile::TEMPLE_KEYWORD			= "te";
const std::string Tile::TORTURE_CHAMBER_KEYWORD = "to";
const std::string Tile::TRAINING_ROOM_KEYWORD	= "tr";
const std::string Tile::TREASURE_ROOM_KEYWORD	= "ta";
const std::string Tile::WORKSHOP_KEYWORD		= "wo";


const size_t Tile::NO_TYPES							= 23;	// Arrays suck. can't get size directly
const size_t Tile::NO_OWNABLE_TYPES					= 15;
const size_t Tile::NO_ENVIRONMENT_TYPES				= 8;
const std::string Tile::TYPES[]					= {
	CLAIMED, 
	UNCLAIMED, DIRT, GOLD, RUBY, REINFORCED, LAVA, WATER, IMPENETRABLE, BARRACKS,
	BRIDGE, GRAVEYARD, GUARD_POST, HATCHERY, LAIR, LIBRARY, PRISON, SCAVENGER_ROOM, TEMPLE, 
	TORTURE_CHAMBER, TRAINING_ROOM, TREASURE_ROOM, WORKSHOP
};
const std::string Tile::OWNABLE_TYPES[]			= {
	//CLAIMED,	TODO: Something's wrong with circulation areas. Not necessary for prototype
	BARRACKS, BRIDGE, GRAVEYARD, GUARD_POST, HATCHERY, LAIR, LIBRARY, PRISON,
	SCAVENGER_ROOM, TEMPLE, TORTURE_CHAMBER, TRAINING_ROOM, TREASURE_ROOM, WORKSHOP
};
const std::string Tile::ENVIRONMENT_TYPES[]		= {
	UNCLAIMED, DIRT, GOLD, RUBY, REINFORCED, LAVA, WATER, IMPENETRABLE
};

/*
	Block properties hash
*/
std::unordered_map<std::string, std::shared_ptr<TileDefinition>> Tile::TILE_DEFINITIONS_KEYWORDED = {
	{"UNCLAIMED", std::make_shared<TileDefinition>("u", "UNCLAIMED", false, std::tuple<int, int, int>(233, 022, 140))},
	{"CLAIMED", std::make_shared<TileDefinition>("ca", "CLAIMED", std::tuple<int, int, int>(0,0,153))},
	{"DIRT", std::make_shared<TileDefinition>("d", "DIRT", false, std::tuple<int, int, int>(0,0,0))},
	{"GOLD", std::make_shared<TileDefinition>("g", "GOLD", false, std::tuple<int, int, int>(0,0,0))},
	{"RUBY", std::make_shared<TileDefinition>("y", "RUBY", false, std::tuple<int, int, int>(0,0,0))},
	{"REINFORCED", std::make_shared<TileDefinition>("r", "REINFORCED", false, std::tuple<int, int, int>(255, 255, 255))},
	{"WATER", std::make_shared<TileDefinition>("w", "WATER", false, std::tuple<int, int, int>(0, 176, 240))},
	{"LAVA", std::make_shared<TileDefinition>("l", "LAVA", false,  std::tuple<int, int, int>(204, 176, 0))},
	{"IMPENETRABLE", std::make_shared<TileDefinition>("i", "IMPENETRABLE", false, std::tuple<int, int, int>(102, 51, 0))},
	{"BARRACKS", std::make_shared<TileDefinition>("ba", "BARRACKS", std::tuple<int, int, int>(160, 43, 147))},
	{"BRIDGE", std::make_shared<TileDefinition>("br", "BRIDGE", std::tuple<int, int, int>(126, 53, 14))},
	{"GRAVEYARD", std::make_shared<TileDefinition>("gr", "GRAVEYEARD", std::tuple<int, int, int>(15, 158, 213))},
	{"GUARD_POST", std::make_shared<TileDefinition>("gu", "GUARD_POST", std::tuple<int, int, int>(116, 116, 116))},
	{"HATCHERY", std::make_shared<TileDefinition>("ha", "HATCHERY", std::tuple<int, int, int>(233, 113, 50))},
	{"LAIR", std::make_shared<TileDefinition>("la", "LAIR", std::tuple<int, int, int>(21, 96, 130))},
	{"LIBRARY", std::make_shared<TileDefinition>("li", "LIBRARY", std::tuple<int, int, int>(112, 48, 160))},
	{"PRISON", std::make_shared<TileDefinition>("pi", "PRISON", std::tuple<int, int, int>(241, 169, 131))},
	{"SCAVENGER_ROOM", std::make_shared<TileDefinition>("sc", "SCAVENGER_ROOM", std::tuple<int, int, int>(173, 173, 173))},
	{"TEMPLE", std::make_shared<TileDefinition>("te", "TEMPLE", std::tuple<int, int, int>(173, 173, 173))},
	{"TORTURE_CHAMBER", std::make_shared<TileDefinition>("to", "TORTURE_CHAMBER", std::tuple<int, int, int>(192, 0, 0))},
	{"TRAINING_ROOM", std::make_shared<TileDefinition>("tr", "TRAINING_ROOM", std::tuple<int, int, int>(60, 125, 34))},
	{"TREASURE_ROOM", std::make_shared<TileDefinition>("ta", "TREASURE_ROOM", std::tuple<int, int, int>(255, 153, 0))},
	{"WORKSHOHP", std::make_shared<TileDefinition>("wo", "WORKSHOP", std::tuple<int, int, int>(255, 192, 0))}
};
std::unordered_map<std::string, std::shared_ptr<TileDefinition>> Tile::TILE_DEFINITIONS_LABELED = {
	{"u", TILE_DEFINITIONS_KEYWORDED[Tile::UNCLAIMED]},
	{"ca",TILE_DEFINITIONS_KEYWORDED[Tile::CLAIMED]},
	{"g", TILE_DEFINITIONS_KEYWORDED[Tile::GOLD]},
	{"d", TILE_DEFINITIONS_KEYWORDED[Tile::DIRT]},
	{"r", TILE_DEFINITIONS_KEYWORDED[Tile::REINFORCED]},
	{"w", TILE_DEFINITIONS_KEYWORDED[Tile::WATER]},
	{"l", TILE_DEFINITIONS_KEYWORDED[Tile::LAVA]},
	{"i", TILE_DEFINITIONS_KEYWORDED[Tile::IMPENETRABLE]},
	{"ba", TILE_DEFINITIONS_KEYWORDED[Tile::BARRACKS]},
	{"br", TILE_DEFINITIONS_KEYWORDED[Tile::BRIDGE]},
	{"gr", TILE_DEFINITIONS_KEYWORDED[Tile::GRAVEYARD]},
	{"gu", TILE_DEFINITIONS_KEYWORDED[Tile::GUARD_POST]},
	{"ha", TILE_DEFINITIONS_KEYWORDED[Tile::HATCHERY]},
	{"la", TILE_DEFINITIONS_KEYWORDED[Tile::LAIR]},
	{"li", TILE_DEFINITIONS_KEYWORDED[Tile::LIBRARY]},
	{"pr", TILE_DEFINITIONS_KEYWORDED[Tile::PRISON]},
	{"sc", TILE_DEFINITIONS_KEYWORDED[Tile::SCAVENGER_ROOM]},
	{"te", TILE_DEFINITIONS_KEYWORDED[Tile::TEMPLE]},
	{"to", TILE_DEFINITIONS_KEYWORDED[Tile::TORTURE_CHAMBER]},
	{"tr", TILE_DEFINITIONS_KEYWORDED[Tile::TRAINING_ROOM]},
	{"ta", TILE_DEFINITIONS_KEYWORDED[Tile::TREASURE_ROOM]},
	{"wo", TILE_DEFINITIONS_KEYWORDED[Tile::WORKSHOP]}
};
Tile::Tile(): definition(Tile::TILE_DEFINITIONS_KEYWORDED[Tile::DIRT]){}
/*
	Main constructor:
*/
Tile::Tile(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePlayer, int x, int y) : definition(def),player(thePlayer), x(x), y(y){}

// Instance methods

bool Tile::isOwned() { return player != nullptr; }
bool Tile::ownedBy(int playerID) { return isOwned() && player->getID() == playerID; }
void Tile::update(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePlayer, int xPos, int yPos) {
	definition	= def;
	player		= thePlayer;
	x			= xPos;
	y			= yPos;
}
void Tile::update(std::shared_ptr<TileDefinition> def, std::shared_ptr<Player> thePlayer) {
	definition = def;
	player = thePlayer;
}