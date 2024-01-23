
/*===
	Includes
===*/
// Native

// Project
#include "sbem_survey_object.h"
/*
	SBEM survey - the intermediary between DK and SBEM.

	Top-level object SbemSurveyObjects.

	Zones, walls, windows, and doors are nested within their respective parent.
*/
struct SbemSurvey {
	/*=== Constructors ===*/
	SbemSurvey();
	/*=== Instance methods ===*/
	std::string toInp();
	/*=== Instance members ===*/
	/* SbemGeneral */
	SbemSurveyObject general;
	/* SbemRecProject (pointless object but needs to be there */
	SbemSurveyObject recProject;
	/* SbemCompliance */
	SbemSurveyObject compliance;
	/* SbemConstruction details */
	std::vector<SbemSurveyObject> constructions;
	/* SbemGlass details */
	std::vector<SbemSurveyObject> glasses;
	/* SbemDhwGenerator details */
	std::vector<SbemSurveyObject> dhws;
	/* SbemHvacSystem details */
	std::vector<SbemSurveyObject> hvacs;;
};