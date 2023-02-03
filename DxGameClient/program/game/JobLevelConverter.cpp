#include "GameManager.h"
#include "JobLevelConverter.h"

JobLevelConverter* JobLevelConverter::GetInstance()
{
	if (!instance) {
		instance = new JobLevelConverter();
	}
	return instance;
}

JobLevelConverter::JobLevelConverter() {
	gManager = GameManager::GetInstance();
}


