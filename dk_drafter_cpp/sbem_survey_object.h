#pragma once
/*===
	Includes
===*/
// Native
#include <string>
#include <unordered_map>>
#include <vector>
#include <memory>
// Project
/*
	SBEM survey object: Struct for SBEM surveys
*/
class SbemSurveyObject {
public:
	/*=== Constructors ===*/
	SbemSurveyObject();
	SbemSurveyObject(std::string name, std::string type);
	/*=== Static members ===*/
	
	static const std::string CONSTRUCTION;	// Literally just CONSTRUCTION
	static const std::string DOOR;			// Literally just DOOR
	static const std::string DHW_GENERATOR; // DHW-GENERATOR
	static const std::string GLASS;			// Literally just GLASS
	static const std::string HVAC_SYSTEM;	// HVAC-SYSTEM	
	static const std::string WALL;			// Literally just WALL
	static const std::string WINDOW;		// Literally just WINDOW
	static const std::string ZONE;			// Literally just ZONE
	/* Common keywords */
	static const std::string AREA;			// Literally just AREA
	/*=== Instance methods ===*/
	/* Convert survy to JSON - TODO: Serialise someway or another s*/
	std::string toJSON();
	/*=== Instance members ===*/
	/* SBEM object type */
	std::string type;
	/* Object name */
	std::string name;
	/*=== Setters === */
	/* Set numbers. Floats or ints, doesn't matter. The SBEM service figures it out. */
	void setNumericProperty(std::string key, float value);
	/* Set strings */
	void setStringProperty(std::string key, std::string value);
	/* Set associations. Glorified name reference */
	void setAssociation(std::string key, std::shared_ptr<SbemSurveyObject> value);
	/*=== Instance members ===*/
	/* Get an association by object key name. E.g CONSTRUCTION */
	std::shared_ptr<SbemSurveyObject> getAssociation(std::string key);
	/* Get a numeric property */
	float getNumericProperty(std::string key);
	/* Get a string property */
	std::string getStringProperty(std::string key);
	/*=== Instance memebers ===*/
	/* Child objects. Zones of HVACs, for example */
	std::vector<SbemSurveyObject> children;
	/* Array of properties to be dropped if the Sbem Service adds them to the base object, E.g PATH-FILE-EXT from GENERAL*/
	std::vector<std::string> stringPropertiesForRemoval;
	/* Array of properties to be dropped if the Sbem Service adds them to the base object, E.g SBEM-ID from HVAC-SYSTEM */
	std::vector<std::string> numericPropertiesForRemoval;
protected:
	/*=== Instance members===*/
	/*
		Ok, because using auto& feels dirty and is inconvenient for listing keys, we've
		separated proeprties into keys and key-value pairs and types.

		If it ends in *Properties, it's the key-value pairs. If it ends in *Keys, it's the keys
	*/
	std::vector<std::string> associationPropertyKeys;
	std::vector<std::string> numericPropertyKeys;
	std::vector<std::string> stringPropertyKeys;
	std::unordered_map<std::string, std::shared_ptr<SbemSurveyObject>> associationProperties;
	std::unordered_map<std::string, float> numericProperties;
	std::unordered_map<std::string, std::string> stringProperties;
};