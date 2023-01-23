#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<vector>
#include<string>

class GameManager;

class ResourceManager
{
public:
	// インスタンスの取得
	static ResourceManager* GetInstance();

	void LoadResouce(int type);

	std::vector< std::vector<int>>& GetAnimVector(int type);
	std::vector<int>& GetGraphicVector(int type);

	std::vector<tnl::Vector3>& GetGraphicSize(int type);

	std::vector<int>& GetCharaVectorAtGhNum(int graphicNum);

public:
	enum class RESOUCETYPE :uint32_t {
		PLAYER,
		ENEMY,
		EFFECT,
		ITEM,
		JOB,
		TALENT,
		SKILL,
		MAX
	};

private:
	ResourceManager();
	~ResourceManager();

	void SetLoadCsvPass();


	void LoadGraphicCsv(std::string pass, std::vector<int>& putInVector);
	void LoadAnimGraphicCsv(std::string pass, std::vector< std::vector<int>>& putInVector,int type);

	void SetGraphicSize(int type, int width, int height);


private:
	static ResourceManager* instance;

	GameManager* gManager = nullptr;

	//各画像のURLが記述されたCSVのパスを格納する配列
	std::vector <std::string>loadCsvPasses;

	std::vector< std::vector<int>>playerGhs;
	std::vector< std::vector<int>>enemyGhs;
	std::vector< std::vector<int>>effectGhs;
	std::vector<int>itemGhs;
	std::vector<int>jobGhs;
	std::vector<int>talentGhs;
	std::vector<int>skillGhs;

	//画像のx,y方向の大きさ
	std::vector<std::vector<tnl::Vector3>> graphicSizes;

};

