
/*===
	Includes
===*/
// Native

// Project
#include "sbem_survey_object.h"
/*
	SBEM survey - the intermediary between DK and SBEM.
*/
struct SbemSurvey {
	/*=== Constructors ===*/
	SbemSurvey();
	std::vector<SbemSurveyObject> constructions;
	std::vector<SbemSurveyObject> glasses;
	std::vector<SbemSurveyObject> dhws;
	std::vector<SbemSurveyObject> hvacs;;
};