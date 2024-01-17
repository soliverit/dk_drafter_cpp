#pragma once
/*===
	Includes
===*/
// Native 
#include <string>
// Project
/*
	Player: The thing that owns tiles
*/
class Player {
public:
	/*=== Constructors ===*/
	/* Default*/
	Player();
	/* With alias and identifier*/
	Player(std::string playerName, unsigned int playerID);
	/*=== Instance methods ===*/
	unsigned int getID();
	/*=== Instance members ===*/
	std::string name;		// Player name. Arbitrary
protected:
	/*=== Player ID. Protected because it has purpose. Access with map.getID() */
	unsigned int id;
};