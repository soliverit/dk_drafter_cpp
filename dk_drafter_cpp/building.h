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
#include "sbem_survey.h"
class Building {
public:
	/*=== Constructors ===*/
	/* Default constructor */
	Building();
	/* Basice Building with floor plan */
	Building(Map* map);
	/*=== Static members ===*/
	/* 
		A template for the most basic SBEM model.

		All models have comon objects, GENERAL, COMPLIANCE, CONSTRUCTION, HVAC-SYSTEM, ZONE etc. but 
		most need some knowledge of the buildng. CONSTRUCTION and WALL can't exist without knowing of
		one another, for example.

		This block has the two object that need no reference and are most cruical. It is used to generate
		the barest possible model for converting a Building to SbemModel.
	*/
	static const std::string SBEM_MIN_MODEL;
	/*=== Instance members ===*/
	/* Basically a floor plan */
	Map* map;
	/* The activity spaces within the Building. Sub Maps*/
	std::vector<Room> rooms;
	/* Extract the Rooms into to the associated member */
	void extractRooms();
	/*
		Convert to SBEM model

		Convert the Building into a model for the SBEM (Simplified Building Energy Model) 
		calculator.
	*/
	SbemSurvey toSbemSurvey();
};