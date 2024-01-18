#pragma once
/*===
	Includes
===*/
// Native
#include <vector>
// Project
#include "map.h"
#include "room.h"
#include "tile.h"
class Building {
public:
	Building();
	Building(Map* map);
	Map* map;
	std::vector<Room> rooms;
	void extractRooms();
};