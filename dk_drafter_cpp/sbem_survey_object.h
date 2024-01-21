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
	static const std::string CONSTRUCTION;
	static const std::string DOOR;
	static const std::string DHW_GENERATOR;
	static const std::string GLASS;
	static const std::string HVAC_SYSTEM;
	static const std::string WALL;
	static const std::string WINDOW;
	static const std::string ZONE;
	/* Common keywords */
	static const std::string AREA;
	/*=== Instance methods ===*/
	std::string type;
	std::string name;
	
	void setNumericProperty(std::string key, float value);
	void setStringProperty(std::string key, std::string value);
	void setAssociation(std::string key, std::shared_ptr<SbemSurveyObject> value);
	/*=== Instance members ===*/
	std::shared_ptr<SbemSurveyObject> getAssociation(std::string key);
	float getNumericProperty(std::string key);
	std::string getStringProperty(std::string key);
	std::vector<SbemSurveyObject> children;
	std::vector<std::string> stringPropertiesForRemoval;
	std::vector<std::string> numericPropertiesForRemoval;
protected:
	/*=== Instance members===*/
	std::vector<std::string> associationPropertyKeys;
	std::vector<std::string> numericPropertyKeys;
	std::vector<std::string> stringPropertyKeys;
	std::unordered_map<std::string, std::shared_ptr<SbemSurveyObject>> associationProperties;
	std::unordered_map<std::string, float> numericProperties;
	std::unordered_map<std::string, std::string> stringProperties;
	
};