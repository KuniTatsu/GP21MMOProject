#include "Job.h"

Job::Job(int jobId, std::string jobName, int jobStr, int jobVit, int jobInt, int jobMin, int jobSpd, int jobDex)
{
	//‘ã“ü
	id = jobId;
	name = jobName;
	str = jobStr;
	vit = jobVit;
	inteli = jobInt;
	min = jobMin;
	spd = jobSpd;
	dex = jobDex;
}

Job::Job(int jobId, std::string jobName, int jobStr, int jobVit, int jobInt, int jobMin, int jobSpd, int jobDex, int startLevel)
{
	//‘ã“ü
	id = jobId;
	name = jobName;
	str = jobStr;
	vit = jobVit;
	inteli = jobInt;
	min = jobMin;
	spd = jobSpd;
	dex = jobDex;

	level = startLevel;
}

Job::~Job()
{
}

