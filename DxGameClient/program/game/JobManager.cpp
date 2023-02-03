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

void JobManager::JobTargetTable()
{
    auto loadCsv = tnl::LoadCsv("csv/JobTargetTable.csv");

    for (int i = 1; i < loadCsv.size(); ++i) {}

}

// ‚±‚ê‚©‚ç‚â‚é‚±‚Æ
void JobManager::JobLevelStatus() {
    auto loadCsv = tnl::LoadCsv("csv/JobLevelUp.csv");

    for (int i = 1; i < loadCsv.size(); ++i)
    {
        auto id = std::stoi(loadCsv[i][0]);
        auto name = loadCsv[i][1];
        auto weapon = std::stoi(loadCsv[i][2]);
        auto levelup = std::stoi(loadCsv[i][3]);
        auto exp = std::stoi(loadCsv[i][4]);
    };
}

std::shared_ptr<Job> JobManager::CreateNewJob(int id)
{
    auto name = jobMaster[id]->GetName();
    auto str = jobMaster[id]->GetStr();
    auto vit = jobMaster[id]->GetVit();
    auto inteli = jobMaster[id]->GetInt();
    auto min = jobMaster[id]->GetMin();
    auto spd = jobMaster[id]->GetSpd();
    auto dex = jobMaster[id]->GetDex();

    int rank = 0;
    return std::make_shared<Job>(id, name, str, vit, inteli, min, spd, dex, rank);
}

std::shared_ptr<Job> JobManager::LevelUpJob(int id)
{
    return std::shared_ptr<Job>();
}
