#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>

class GameManager;

class ResourceManager
{
public:
	// �C���X�^���X�̎擾
	static ResourceManager* GetInstance();

	void LoadResouce(int type);

	std::vector< std::vector<int>>& GetAnimVector(int type);
	std::vector<int>& GetGraphicVector(int type);

public:
	enum class RESOUCETYPE :uint32_t {
		PLAYER,
		ENEMY,
		EFFECT,
		ITEM,
		JOB,
		TALENT,
		MAX
	};

private:
	ResourceManager();
	~ResourceManager();

	void SetLoadCsvPass();


	void LoadGraphicCsv(std::string pass, std::vector<int>& putInVector);
	void LoadAnimGraphicCsv(std::string pass, std::vector< std::vector<int>>& putInVector);

private:
	static ResourceManager* instance;

	GameManager* gManager = nullptr;

	//�e�摜��URL���L�q���ꂽCSV�̃p�X���i�[����z��
	std::vector <std::string>loadCsvPasses;

	std::vector< std::vector<int>>playerGhs;
	std::vector< std::vector<int>>enemyGhs;
	std::vector< std::vector<int>>effectGhs;
	std::vector<int>itemGhs;
	std::vector<int>jobGhs;
	std::vector<int>talentGhs;

};

