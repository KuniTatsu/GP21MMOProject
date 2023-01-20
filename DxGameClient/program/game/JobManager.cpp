#include "JobManager.h"
#include "Job.h"
#include "GameManager.h"

JobManager* JobManager::instance = nullptr;

JobManager::JobManager()
{
    gManager = GameManager::GetInstance();
}

JobManager::~JobManager()
{
}

JobManager* JobManager::GetInstance()
{
    if (!instance) {
        instance = new JobManager();
    }
    return instance;
}

void JobManager::LoadCsv()
{
    auto loadCsv = tnl::LoadCsv("csv/JobMaster.csv");

    for (int i = 1; i < loadCsv.size(); ++i) {
        auto id = std::stoi(loadCsv[i][0]);
        auto name = loadCsv[i][1];
        auto str = std::stoi(loadCsv[i][2]);
        auto vit = std::stoi(loadCsv[i][3]);
        auto inteli = std::stoi(loadCsv[i][4]);
        auto min = std::stoi(loadCsv[i][5]);
        auto spd = std::stoi(loadCsv[i][6]);
        auto dex = std::stoi(loadCsv[i][7]);

        auto job = std::make_shared<Job>(id, name, str, vit, inteli, min, spd, dex);
        jobMaster.emplace_back(job);
    }
}
