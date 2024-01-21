#include "sbem_survey_object.h"
/*=== Constructors ===*/
SbemSurveyObject::SbemSurveyObject(){}
SbemSurveyObject::SbemSurveyObject(std::string name, std::string type) : name(name), type(type){}
/*=== Static members ===*/
const std::string SbemSurveyObject::CONSTRUCTION	= "CONSTRUCTION";
const std::string SbemSurveyObject::DOOR			= "DOOR";
const std::string SbemSurveyObject::DHW_GENERATOR	= "DHW-GENERATOR";
const std::string SbemSurveyObject::GLASS			= "GLASS";
const std::string SbemSurveyObject::HVAC_SYSTEM		= "HVAC-SYSTEM";
const std::string SbemSurveyObject::WALL			= "WALL";
const std::string SbemSurveyObject::WINDOW			= "WINDOW";
const std::string SbemSurveyObject::ZONE			= "ZONE";
/* Common keywords */
const std::string SbemSurveyObject::AREA			= "AREA";
/*=== Instance methods ===*/
// Getters
std::shared_ptr<SbemSurveyObject> SbemSurveyObject::getAssociation(std::string key) { return associationProperties[key]; }
float SbemSurveyObject::getNumericProperty(std::string key) { return numericProperties[key];}
std::string SbemSurveyObject::getStringProperty(std::string key) { return stringProperties[key];}
// Setters
void SbemSurveyObject::setAssociation(std::string key, std::shared_ptr<SbemSurveyObject> value) {
	associationProperties[key] = value;
	for (size_t propertyKeyID = 0; propertyKeyID < associationPropertyKeys.size(); propertyKeyID++)
		if (associationPropertyKeys[propertyKeyID] == key)
			return;
	associationPropertyKeys.push_back(key);
}
void SbemSurveyObject::setNumericProperty(std::string key, float value) {
	numericProperties[key] = value;
	for (size_t propertyKeyID = 0; propertyKeyID < numericPropertyKeys.size(); propertyKeyID++)
		if (numericPropertyKeys[propertyKeyID] == key)
			return;
	numericPropertyKeys.push_back(key);
}
void SbemSurveyObject::setStringProperty(std::string key, std::string value) {
	stringProperties[key] = value;
	for (size_t propertyKeyID = 0; propertyKeyID < stringPropertyKeys.size(); propertyKeyID++)
		if (stringPropertyKeys[propertyKeyID] == key)
			return;
	stringPropertyKeys.push_back(key);
}