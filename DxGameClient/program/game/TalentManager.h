#pragma once

#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>
#include<memory>

class Talent;
class GameManager;

class TalentManager
{
public:
	// インスタンスの取得
	static TalentManager* GetInstance();

	//新しく作るタレントのidを決定する関数
	std::shared_ptr<Talent>GetNewTalent(int remainRank,std::vector<int>& haveTalentList);


private:
	TalentManager();
	~TalentManager();

	void LoadCsv();
	
	
	//新しくタレントを生成する関数
	std::shared_ptr<Talent>CreateNewTalent(int id, int remainRank);


private:
	static TalentManager* instance;
	GameManager* gManager = nullptr;


	std::vector<std::shared_ptr<Talent>>talentMaster;

	std::vector<int> talentWaight;


};

