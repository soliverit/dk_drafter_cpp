#pragma once
#define TILE_MAP_SIZE 128
/*===
	Includes
===*/
// Native
#include <map>
// Project
#include "tile.h""
/*
	Tile Map: A map of Tiles
*/
class TileMap {
public:
	TileMap();
	Tile tiles[TILE_MAP_SIZE][TILE_MAP_SIZE];
};