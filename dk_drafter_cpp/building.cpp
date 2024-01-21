#include "building.h"

/*=== Constructors ===*/
Building::Building() {}
Building::Building(Map* map) : map(map){
	extractRooms();
}

/*=== Instance methods ===*/
void Building::extractRooms() {
	// Empty the Room store
	rooms.clear();
	// Get all the activities in the Building
	std::vector<std::string> activityTypes = map->getActivityTypes();
	// With every activity, extract a Map containing only Tile of that kind + non-ownable boundary surfaces;
	for (size_t activityTypeID = 0; activityTypeID < activityTypes.size(); activityTypeID++) {
		std::shared_ptr<TileDefinition> tileDefinition = Tile::TILE_DEFINITIONS_LABELED[activityTypes[activityTypeID]];
		Map* activityMap			= map->clone();
		activityMap->removeOwnableBlocksExcept(tileDefinition->label, Tile::TILE_DEFINITIONS_LABELED[Tile::DIRT], 1);
		activityMap					= activityMap->extractPlayerMap(1);
		Room room					= Room(activityMap, tileDefinition);
		rooms.push_back(room);;
	}
}
SbemSurvey Building::toSbemSurvey() {
	SbemSurvey survey;
	std::vector<SbemSurveyObject> constructions;
	std::vector<SbemSurveyObject> glasses;
	std::vector<SbemSurveyObject> dhws;
	std::vector<SbemSurveyObject> hvacs;
	/*=== Define constructions ===*/
	SbemSurveyObject construction;
	// Outside
	SbemSurveyObject reinforced		= SbemSurveyObject(Tile::REINFORCED, SbemSurveyObject::CONSTRUCTION);
	reinforced.setStringProperty("METAL-CLADDING", "YES");
	reinforced.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(reinforced);

	SbemSurveyObject dirt			= SbemSurveyObject(Tile::DIRT, SbemSurveyObject::CONSTRUCTION);
	dirt.setStringProperty("METAL-CLADDING", "NO");
	dirt.setNumericProperty("U-VALUE", 1);
	survey.constructions.push_back(dirt);
	
	SbemSurveyObject lava			= SbemSurveyObject(Tile::LAVA, SbemSurveyObject::CONSTRUCTION);
	lava.setStringProperty("METAL-CLADDING", "NO");
	lava.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(lava);

	SbemSurveyObject water = SbemSurveyObject(Tile::WATER, SbemSurveyObject::CONSTRUCTION);
	water.setStringProperty("METAL-CLADDING", "NO");
	water.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(water);

	SbemSurveyObject claimed		= SbemSurveyObject(Tile::CLAIMED, SbemSurveyObject::CONSTRUCTION);
	claimed.setStringProperty("METAL-CLADDING", "NO");
	claimed.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(claimed);

	SbemSurveyObject unclaimed		= SbemSurveyObject(Tile::UNCLAIMED, SbemSurveyObject::CONSTRUCTION);
	unclaimed.setStringProperty("METAL-CLADDING", "NO");
	unclaimed.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(unclaimed);

	SbemSurveyObject impenetrable	= SbemSurveyObject(Tile::IMPENETRABLE, SbemSurveyObject::CONSTRUCTION);
	impenetrable.setStringProperty("METAL-CLADDING", "NO");
	impenetrable.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(impenetrable);
	std::unordered_map<std::string, SbemSurveyObject> constructionMap = {
		{Tile::DIRT, dirt}, {Tile::REINFORCED, reinforced}, {Tile::LAVA, lava}, {Tile::WATER, water},
		{Tile::CLAIMED, claimed}, {Tile::UNCLAIMED, unclaimed}, {Tile::IMPENETRABLE, impenetrable}
	};
	/*=== Define glasses ===*/
	SbemSurveyObject lavaGlass		= SbemSurveyObject("LAVA", SbemSurveyObject::GLASS);
	lavaGlass.setNumericProperty("U-VALUE", 1.4);
	survey.glasses.push_back(lavaGlass);

	SbemSurveyObject waterGlass		= SbemSurveyObject("WATER", SbemSurveyObject::GLASS);
	waterGlass.setNumericProperty("U-VALUE", 3);
	survey.glasses.push_back(waterGlass);

	SbemSurveyObject unclaimedGlass = SbemSurveyObject("WATER", SbemSurveyObject::GLASS);
	unclaimedGlass.setNumericProperty("U-VALUE", 5);
	survey.glasses.push_back(unclaimedGlass);

	std::unordered_map <std::string, SbemSurveyObject> glassMap = {
		{Tile::LAVA, lavaGlass}, {Tile::WATER, waterGlass}, {Tile::UNCLAIMED, unclaimedGlass}
	};

	/*=== Shared objects === */
	SbemSurveyObject dhw			= SbemSurveyObject("DHW", SbemSurveyObject::DHW_GENERATOR);
	survey.dhws.push_back(dhw);

	SbemSurveyObject hvac			= SbemSurveyObject("DHW", SbemSurveyObject::HVAC_SYSTEM);
	survey.hvacs.push_back(hvac);

	/* Do Rooms*/
	extractRooms();
	for (size_t roomID = 0; roomID < rooms.size(); roomID++) {
		Room room				= rooms[roomID];
		/* Zone info */
		SbemSurveyObject zone	= SbemSurveyObject(room.activity->label, SbemSurveyObject::ZONE);
		zone.setNumericProperty("ACTIVITY", std::stof(Tile::TILE_SBEM_ACTIVITIES[room.activity->label]["ID"]));
		zone.setStringProperty("ACTIVITY-NAME", Tile::TILE_SBEM_ACTIVITIES[room.activity->label]["NAME"]);
		zone.setNumericProperty("HEIGHT", 3);
		
		
		/* Walls */
		SurfaceSet surfaces		= room.extractGeometry();
		float height			= zone.getNumericProperty("HEIGHT");
		std::vector<Tile> tiles;
		SbemSurveyObject window;
		for (size_t envKeywordID = 0; envKeywordID < Tile::NO_ENVIRONMENT_TYPES; envKeywordID++) {
			std::string envType			= Tile::ENVIRONMENT_TYPES[envKeywordID];
			SbemSurveyObject northWall	= SbemSurveyObject("WEST-WALL - " + zone.name, SbemSurveyObject::WALL);
			northWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::North, envType).size() * height);
			if (northWall.getNumericProperty(SbemSurveyObject::AREA) > 0) {
				zone.children.push_back(northWall);
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + northWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, northWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, std::make_shared<SbemSurveyObject>(glassMap[envType]));
				}
			}
			SbemSurveyObject eastWall	= SbemSurveyObject("WEST-WALL - " + zone.name, SbemSurveyObject::WALL);
			eastWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::East, envType).size() * height);
			if (eastWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + eastWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, eastWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, std::make_shared<SbemSurveyObject>(glassMap[envType]));
				}
				zone.children.push_back(eastWall);
			}
			SbemSurveyObject southWall	= SbemSurveyObject("WEST-WALL - " + zone.name, SbemSurveyObject::WALL);
			southWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::South, envType).size() * height);
			if (southWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + southWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, southWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, std::make_shared<SbemSurveyObject>(glassMap[envType]));
				}
				zone.children.push_back(southWall);
			}
			SbemSurveyObject westWall	= SbemSurveyObject("WEST-WALL - " + zone.name, SbemSurveyObject::WALL);
			westWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::West, envType).size() * height);
			if (westWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + westWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, westWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, std::make_shared<SbemSurveyObject>(glassMap[envType]));
				}
				zone.children.push_back(westWall);
			}

		}
		/* Associations */
		hvac.children.push_back(zone);
		zone.setAssociation(SbemSurveyObject::DHW_GENERATOR, std::make_shared<SbemSurveyObject>(dhw));
	}
	return survey;
}