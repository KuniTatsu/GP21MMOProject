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
	// �C���X�^���X�̎擾
	static TalentManager* GetInstance();

	//�V�������^�����g��id�����肷��֐�
	std::shared_ptr<Talent>GetNewTalent(int remainRank,std::vector<int>& haveTalentList);


private:
	TalentManager();
	~TalentManager();

	void LoadCsv();
	
	
	//�V�����^�����g�𐶐�����֐�
	std::shared_ptr<Talent>CreateNewTalent(int id, int remainRank);


private:
	static TalentManager* instance;
	GameManager* gManager = nullptr;


	std::vector<std::shared_ptr<Talent>>talentMaster;

	std::vector<int> talentWaight;


};

