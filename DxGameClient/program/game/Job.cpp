#include "Job.h"

Job::Job(int jobId, std::string jobName, int jobStr, int jobVit, int jobInt, int jobMin, int jobSpd, int jobDex)
{
	//���
	id = jobId;
	name = jobName;
	str = jobStr;
	vit = jobVit;
	inteli = jobInt;
	min = jobMin;
	spd = jobSpd;
	dex = jobDex;
}

Job::~Job()
{
}

