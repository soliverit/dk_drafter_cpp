#include "building.h"

/*=== Constructors ===*/
/* Keeping c++ happy. Don't use */
Building::Building() {}
/* Create with a Player Map. Ideally, a single Player but go nuts */
Building::Building(Map* map) : map(map){}

/*=== Instance methods ===*/
void Building::extractRooms() {
	// Empty the Room store
	rooms.clear();
	// Get all the activities in the Building
	std::vector<std::string> activityTypes = map->getActivityTypes();
	// With every activity, extract a Map containing only Tile of that kind + non-ownable boundary surfaces;
	for (size_t activityTypeID = 0; activityTypeID < activityTypes.size(); activityTypeID++) {
		std::shared_ptr<TileDefinition> tileDefinition = Tile::TILE_DEFINITIONS_LABELED[activityTypes[activityTypeID]];
		/* Clone the floor Plan */
		Map* activityMap			= map->clone();
		/* Reduce the Map to only the target activity */
		activityMap->removeOwnableBlocksExcept(tileDefinition->label, Tile::TILE_DEFINITIONS_LABELED[Tile::DIRT], 1);
		/* Extract the activty Map. Rescaled on boundaries */
		activityMap					= activityMap->extractPlayerMap(1);
		std::cout << "\n\n" << tileDefinition->label << "\n";
		activityMap->drawToConsole();
		Room room					= Room(activityMap, tileDefinition);
		rooms.push_back(room);;
	}
}
/* 
	Create SBEM survey for SBEM service

	Note: The SBEM service creates basic instances of each SbemSurveyObject.type. Anything that's to be
	overwritten or removed should be added in this method.

	E.g: CONSTRUCTION and GLASS U-VALUEs
*/
SbemSurvey Building::toSbemSurvey() {
	SbemSurvey survey;
	/*=== Define constructions ===
		Create constructions that define the thermal properties of surfaces.

		TODO: Values will eventually come from Level-specific templates

		V1: All surfaces assumed be exterior.
		V2: TODO: Reference the World Map to check for adjacencies

		TODO: Take these values from a hash in the Building object. E.g myBuilding.constructionMap
	*/
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

	SbemSurveyObject floor			= SbemSurveyObject(Tile::IMPENETRABLE, SbemSurveyObject::CONSTRUCTION);
	floor.setStringProperty("METAL-CLADDING", "NO");
	floor.setNumericProperty("U-VALUE", 0.5);
	survey.constructions.push_back(floor);

	SbemSurveyObject roof			= SbemSurveyObject(Tile::IMPENETRABLE, SbemSurveyObject::CONSTRUCTION);
	roof.setStringProperty("METAL-CLADDING", "NO");
	roof.setNumericProperty("U-VALUE", 0.3);
	survey.constructions.push_back(roof);
	

	std::unordered_map<std::string, std::shared_ptr<SbemSurveyObject>> constructionMap = {
		{Tile::DIRT,			std::make_shared<SbemSurveyObject>(dirt)}, 
		{Tile::REINFORCED,		std::make_shared<SbemSurveyObject>(reinforced)},
		{Tile::LAVA,			std::make_shared<SbemSurveyObject>(lava)},
		{Tile::WATER,			std::make_shared<SbemSurveyObject>(water)},
		{Tile::CLAIMED,			std::make_shared<SbemSurveyObject>(claimed)},
		{Tile::UNCLAIMED,		std::make_shared<SbemSurveyObject>(unclaimed)},
		{Tile::IMPENETRABLE,	std::make_shared<SbemSurveyObject>(impenetrable)},
		{"FLOOR",				std::make_shared<SbemSurveyObject>(floor)},
		{"ROOF",				std::make_shared<SbemSurveyObject>(roof)}
	};
	/*=== Define glasses ===
		Ok, hear me out. Lava, water and unclaimed don't exist in SBEM, but they need to
		here. To account for them, they are being modelled as external surfaces with glazing. U-VALUES 
		are generously assumed to accommodate differences in temperature.

		Highly-ventilated spaces were considered but they aren't intended for this purpose. In any case,
			  it'd be a major pain to sense-check results and models would be too volatile. 

		Tl;dr: Trust me, I'm a doctor!
	*/
	SbemSurveyObject lavaGlass		= SbemSurveyObject("LAVA", SbemSurveyObject::GLASS);
	lavaGlass.setNumericProperty("U-VALUE", 1.4);
	lavaGlass.setNumericProperty("TOT-SOL-TRANS", 0.9);
	lavaGlass.setNumericProperty("LIG-SOL-TRANS", 0.9);
	lavaGlass.setNumericProperty("LIG-SOL-TRANS", 0.9);
	survey.glasses.push_back(lavaGlass);

	SbemSurveyObject waterGlass		= SbemSurveyObject("WATER", SbemSurveyObject::GLASS);
	waterGlass.setNumericProperty("U-VALUE", 3);
	waterGlass.setNumericProperty("TOT-SOL-TRANS", 0.6);
	waterGlass.setNumericProperty("LIG-SOL-TRANS", 0.6);
	survey.glasses.push_back(waterGlass);

	SbemSurveyObject unclaimedGlass = SbemSurveyObject("WATER", SbemSurveyObject::GLASS);
	unclaimedGlass.setNumericProperty("U-VALUE", 5);
	survey.glasses.push_back(unclaimedGlass);

	std::unordered_map <std::string, std::shared_ptr<SbemSurveyObject>> glassMap = {
		{Tile::LAVA,		std::make_shared<SbemSurveyObject>(lavaGlass)}, 
		{Tile::WATER,		std::make_shared<SbemSurveyObject>(waterGlass)},
		{Tile::UNCLAIMED,	std::make_shared<SbemSurveyObject>(unclaimedGlass)}
	};

	/*=== Shared objects === */
	SbemSurveyObject dhw			= SbemSurveyObject("DHW", SbemSurveyObject::DHW_GENERATOR);
	survey.dhws.push_back(dhw);

	SbemSurveyObject hvac			= SbemSurveyObject("HVAC", SbemSurveyObject::HVAC_SYSTEM);
	

	/* Do Rooms*/
	extractRooms();
	for (size_t roomID = 0; roomID < rooms.size(); roomID++) {
		Room room				= rooms[roomID];
		/* Zone info */
		SbemSurveyObject zone	= SbemSurveyObject(room.activity->label, SbemSurveyObject::ZONE);
		zone.setNumericProperty("ACTIVITY", std::stof(Tile::TILE_SBEM_ACTIVITIES[room.activity->label]["ID"]));
		zone.setStringProperty("ACTIVITY-NAME", Tile::TILE_SBEM_ACTIVITIES[room.activity->label]["NAME"]);
		zone.setNumericProperty(SbemSurveyObject::HEIGHT, 3);
		zone.setNumericProperty(SbemSurveyObject::AREA, room.area());
		
		/* Walls */
		SurfaceSet surfaces		= room.extractGeometry();
		float height			= zone.getNumericProperty("HEIGHT");
		std::vector<Tile> tiles;
		SbemSurveyObject window;
		/* 
			There are 8 environment TileDefinition and 4 orientations in DK. For each pairing, create
			walls and windows. 			
			
				- IF the type and orientation has surfaces. Add them to the survey
				- IF the surface type is defined as having windows. Add them.
		*/
		for (size_t envKeywordID = 0; envKeywordID < Tile::NO_ENVIRONMENT_TYPES; envKeywordID++) {
			std::string envType			= Tile::ENVIRONMENT_TYPES[envKeywordID];
			/* North-facing surfaces */
			SbemSurveyObject northWall	= SbemSurveyObject("North-Wall - " + envType + " - " + zone.name, SbemSurveyObject::WALL);
			northWall.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::NORTH);
			northWall.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
			northWall.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::WALL);
			northWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::North, envType).size() * height);
			northWall.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap[envType]);
			if (northWall.getNumericProperty(SbemSurveyObject::AREA) > 0) {
				zone.children.push_back(northWall);
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + northWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, northWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, glassMap[envType]);
					northWall.children.push_back(window);
				}
			}
			/* East-facing surfaces */
			SbemSurveyObject eastWall	= SbemSurveyObject("East-Wall - " + envType + " - " + zone.name, SbemSurveyObject::WALL);
			eastWall.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::EAST);
			eastWall.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
			eastWall.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::WALL);
			eastWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::East, envType).size() * height);
			eastWall.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap[envType]);
			if (eastWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + eastWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, eastWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, glassMap[envType]);
					eastWall.children.push_back(window);
				}
				zone.children.push_back(eastWall);
			}
			/* South-facing surfaces */
			SbemSurveyObject southWall	= SbemSurveyObject("South-Wall - " + envType + " - " + zone.name, SbemSurveyObject::WALL);
			southWall.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::SOUTH);
			southWall.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
			southWall.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::WALL);
			southWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::South, envType).size() * height);
			southWall.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap[envType]);
			if (southWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + southWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, southWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, glassMap[envType]);
					southWall.children.push_back(window);
				}
				zone.children.push_back(southWall);
			}
			/* West-facing surfaces */
			SbemSurveyObject westWall	= SbemSurveyObject("East-Wall - " + envType + " - " + zone.name, SbemSurveyObject::WALL);
			westWall.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::WEST);
			westWall.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
			westWall.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::WALL);
			westWall.setNumericProperty(SbemSurveyObject::AREA, surfaces.getTiles(SurfaceSet::ORIENTATION::West, envType).size() * height);
			westWall.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap[envType]);
			if (westWall.getNumericProperty(SbemSurveyObject::AREA) > 0){
				if (envType == Tile::WATER || envType == Tile::LAVA || envType == Tile::UNCLAIMED) {
					window = SbemSurveyObject("WINDOW - " + westWall.name, SbemSurveyObject::WINDOW);
					window.setNumericProperty(SbemSurveyObject::AREA, westWall.getNumericProperty("AREA") * 0.9); // Frame factor adjustment
					window.setAssociation(SbemSurveyObject::GLASS, glassMap[envType]);
					westWall.children.push_back(window);
				}
				zone.children.push_back(westWall);
			}
		}
		/* Roof */
		SbemSurveyObject roof = SbemSurveyObject("Roof - " + zone.name, SbemSurveyObject::WALL);
		roof.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::HORIZONTAL);
		roof.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::ROOF);
		roof.setNumericProperty(SbemSurveyObject::PITCH, 0);
		roof.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
		roof.setNumericProperty(SbemSurveyObject::AREA, zone.getNumericProperty(SbemSurveyObject::AREA));
		roof.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap["ROOF"]);
		zone.children.push_back(roof);
		/* Floor */
		SbemSurveyObject floor = SbemSurveyObject("Floor  - " + zone.name, SbemSurveyObject::WALL);
		floor.setStringProperty(SbemSurveyObject::ORIENTATION, SurfaceSet::HORIZONTAL);
		floor.setStringProperty(SbemSurveyObject::TYPE_ENV, SbemSurveyObject::FLORR_OR_CEILING);
		floor.setStringProperty(SbemSurveyObject::TYPE, SbemSurveyObject::EXTERIOR);
		floor.setNumericProperty(SbemSurveyObject::AREA, zone.getNumericProperty(SbemSurveyObject::AREA));
		floor.setAssociation(SbemSurveyObject::CONSTRUCTION, constructionMap["FLOOR"]);
		zone.children.push_back(floor);
		/* Associations */
		zone.setAssociation(SbemSurveyObject::DHW_GENERATOR, std::make_shared<SbemSurveyObject>(dhw));
		hvac.children.push_back(zone);
	}
	survey.hvacs.push_back(hvac);
	return survey;
}