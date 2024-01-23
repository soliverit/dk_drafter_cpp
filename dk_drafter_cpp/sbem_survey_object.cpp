#include "sbem_survey_object.h"
/*=== Constructors ===*/
SbemSurveyObject::SbemSurveyObject(){}
SbemSurveyObject::SbemSurveyObject(std::string name, std::string type) : name(name), type(type){}
/*=== Static members ===*/
const std::string SbemSurveyObject::COMPLIANCE			= "COMPLAINCE";
const std::string SbemSurveyObject::CONSTRUCTION		= "CONSTRUCTION";
const std::string SbemSurveyObject::DOOR				= "DOOR";
const std::string SbemSurveyObject::DHW_GENERATOR		= "DHW-GENERATOR";
const std::string SbemSurveyObject::GLASS				= "GLASS";
const std::string SbemSurveyObject::GENERAL				= "GENERAL";
const std::string SbemSurveyObject::HVAC_SYSTEM			= "HVAC-SYSTEM";
const std::string SbemSurveyObject::REC_PROJECT			= "REC-PROJECT";
const std::string SbemSurveyObject::WALL				= "WALL";
const std::string SbemSurveyObject::WINDOW				= "WINDOW";
const std::string SbemSurveyObject::ZONE				= "ZONE";
/* Common keywords */
const std::string SbemSurveyObject::AREA				= "AREA";
const std::string SbemSurveyObject::HEIGHT				= "HEIGHT";
const std::string SbemSurveyObject::PITCH				= "PITCH";
const std::string SbemSurveyObject::ORIENTATION			= "ORIENTATION";
const std::string SbemSurveyObject::TYPE				= "TYPE";
const std::string SbemSurveyObject::TYPE_ENV			= "TYPE-ENV";
const std::string SbemSurveyObject::EXTERIOR			= "Exterior";
const std::string SbemSurveyObject::ROOF				= "Roof";
const std::string SbemSurveyObject::FLORR_OR_CEILING	= "Floor or Ceiling";
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
#include "iostream"
std::string SbemSurveyObject::toInpObject() {
	std::string output = "\"" + name + "\"\t=\t" + type;
	/* Update associations */
	for (size_t associationID = 0; associationID < associationPropertyKeys.size(); associationID++) {
		std::string key			= associationPropertyKeys[associationID];
		setStringProperty(key, "\"" + associationProperties[key]->name + "\"");
	}
	
	/* Write string properties */
	for (size_t propertyID = 0; propertyID < stringPropertyKeys.size(); propertyID++)
		output += "\n" + stringPropertyKeys[propertyID] + "\t=\t" + stringProperties[stringPropertyKeys[propertyID]];
	/* Write numeric properties */
	for (size_t propertyID = 0; propertyID < numericPropertyKeys.size(); propertyID++)
		if(numericProperties[numericPropertyKeys[propertyID]] == int(numericProperties[numericPropertyKeys[propertyID]]))
			output += "\n" + numericPropertyKeys[propertyID] + "\t=\t" + std::to_string(int(numericProperties[numericPropertyKeys[propertyID]]));
		else
			output += "\n" + numericPropertyKeys[propertyID] + "\t=\t" + std::to_string(numericProperties[numericPropertyKeys[propertyID]]);
	/* Close object */
	output += "\n ..";
	/* Write children */
	for (size_t childID = 0; childID < children.size(); childID++)
		output += "\n" + children[childID].toInpObject();
	/* We're done! */
	return output;
}