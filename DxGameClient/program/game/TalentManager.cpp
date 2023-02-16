#include "TalentManager.h"
#include "Talent.h"
#include"GameManager.h"




TalentManager* TalentManager::instance = nullptr;


TalentManager* TalentManager::GetInstance()
{
	if (!instance) {
		instance = new TalentManager();
	}
	return instance;
}

TalentManager::TalentManager()
{
	gManager = GameManager::GetInstance();

	LoadCsv();
}

TalentManager::~TalentManager()
{
}

void TalentManager::LoadCsv()
{
	auto loadCsv = tnl::LoadCsv("csv/TalentMaster.csv");

	for (int i = 1; i < loadCsv.size(); ++i) {

		auto id = std::stoi(loadCsv[i][0]);//id
		auto name = gManager->UTF8toSjis(loadCsv[i][1]);//name
		auto rare = std::stoi(loadCsv[i][2]);//rare
		auto lowestRank = std::stoi(loadCsv[i][3]);//lowestRank
		auto STR = std::stoi(loadCsv[i][4]);//str
		auto VIT = std::stoi(loadCsv[i][5]);//vit
		auto INT = std::stoi(loadCsv[i][6]);//int
		auto MIN = std::stoi(loadCsv[i][7]);//min
		auto SPD = std::stoi(loadCsv[i][8]);//spd
		auto DEX = std::stoi(loadCsv[i][9]);//dex

		auto weight = std::stoi(loadCsv[i][10]);//dex
		talentWaight.emplace_back(weight);


		//int talentId, std::string talentName, int talentRare, int lowestRank,
		//int addSTR, int addVIT, int addINT, int addMIN, int addSPD, int addDEX
		auto talent = std::make_shared<Talent>(id, name, rare, lowestRank, STR, VIT, INT, MIN, SPD, DEX);
		talentMaster.emplace_back(talent);
	}
}

std::shared_ptr<Talent> TalentManager::GetNewTalent(int remainRank, std::vector<int>& haveTalentList)
{
	int randId = -1;
	while (true) {
		//マスターシートのタレント一覧からランダムにidを決定する
		//randId = gManager->GetRandBetweenNum(0, talentMaster.size() - 1);

		randId = gManager->GerRandomNumInWeight(talentWaight);

		bool alreadyHave = false;
		if (!haveTalentList.empty()) {
			for (auto haveTalent : haveTalentList) {
				if (haveTalent == randId) {
					alreadyHave = true;
					break;
				}
			}
		}
		if (alreadyHave)continue;

		if (talentMaster[randId]->GetLowestTalentRank() <= remainRank)break;
	}


	return CreateNewTalent(randId, remainRank);
}

std::shared_ptr<Talent> TalentManager::CreateNewTalent(int id, int remainRank)
{
	// 才能取得上限の 20 を超えないように
	if (remainRank <= 0)return nullptr;


	auto& name = talentMaster[id]->GetName();
	auto rare = talentMaster[id]->GetRare();
	auto lowestRank = talentMaster[id]->GetLowestTalentRank();
	auto str = talentMaster[id]->GetStr();
	auto vit = talentMaster[id]->GetVit();
	auto inteli = talentMaster[id]->GetInt();
	auto min = talentMaster[id]->GetMin();
	auto spd = talentMaster[id]->GetSpd();
	auto dex = talentMaster[id]->GetDex();

	int rank = 0;

	if (remainRank < 10) {
		rank = gManager->GetRandBetweenNum(lowestRank, remainRank);
	}
	else {
		rank = gManager->GetRandBetweenNum(lowestRank, 10);
	}


	return std::make_shared<Talent>(id, name, rare, lowestRank, str, vit, inteli, min, spd, dex, rank);
}