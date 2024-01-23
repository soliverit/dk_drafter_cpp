#include "sbem_survey.h"
/*=== Constructors ===*/
SbemSurvey::SbemSurvey(){
	/* Add minimal objects, excluding DHW and HVAC. They should be added during survey */
	general			= SbemSurveyObject(SbemSurveyObject::GENERAL, "DK-PROJECT");
	recProject		= SbemSurveyObject(SbemSurveyObject::REC_PROJECT, "REC-PROJECT");
	compliance		= SbemSurveyObject(SbemSurveyObject::COMPLIANCE, "DK-SBEM");
}
/*=== Instance methods ===*/
std::string SbemSurvey::toInp() {
	std::string output = general.toInpObject();
	output += "\n" + recProject.toInpObject();
	output += "\n" + compliance.toInpObject();
	for (size_t constructionID = 0; constructionID < constructions.size(); constructionID++)
		output += "\n" + constructions[constructionID].toInpObject();
	for (size_t glassID = 0; glassID < glasses.size(); glassID++)
		output += "\n" + glasses[glassID].toInpObject();
	for (size_t dhwID = 0; dhwID < dhws.size(); dhwID++)
		output += "\n" + dhws[dhwID].toInpObject();
	for (size_t hvacID = 0; hvacID < hvacs.size(); hvacID++)
		output += "\n" + hvacs[hvacID].toInpObject();
	return output;
}