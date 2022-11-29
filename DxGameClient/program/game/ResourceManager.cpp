#include "ResourceManager.h"
#include"GameManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (!instance) {
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::LoadResouce(int type)
{
	if (type == static_cast<uint32_t>(RESOUCETYPE::PLAYER) ||
		type == static_cast<uint32_t>(RESOUCETYPE::ENEMY) ||
		type == static_cast<uint32_t>(RESOUCETYPE::EFFECT)) 
	{
		LoadAnimGraphicCsv(loadCsvPasses[type], GetAnimVector(type));
	}
	else
	{
		LoadGraphicCsv(loadCsvPasses[type], GetGraphicVector(type));
	}

}

std::vector<std::vector<int>>& ResourceManager::GetAnimVector(int type)
{
	switch (type)
	{
	case static_cast<uint32_t>(RESOUCETYPE::PLAYER):
		return playerGhs;
		break;
	case static_cast<uint32_t>(RESOUCETYPE::ENEMY):
		return enemyGhs;
		break;
	case static_cast<uint32_t>(RESOUCETYPE::EFFECT):
		return effectGhs;
		break;
	default:
		break;
	}
}

std::vector<int>& ResourceManager::GetGraphicVector(int type)
{
	switch (type)
	{
	case static_cast<uint32_t>(RESOUCETYPE::ITEM):
		return itemGhs;
		break;
	case static_cast<uint32_t>(RESOUCETYPE::JOB):
		return jobGhs;
		break;
	case static_cast<uint32_t>(RESOUCETYPE::TALENT):
		return talentGhs;
		break;
	default:
		break;
	}
}

ResourceManager::ResourceManager()
{
	gManager = GameManager::GetInstance();
	SetLoadCsvPass();
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::SetLoadCsvPass()
{

	loadCsvPasses.emplace_back("csv/playerGraphics.csv");//エフェクトあり
	loadCsvPasses.emplace_back("csv/enemyGraphics.csv"); //エフェクトあり
	loadCsvPasses.emplace_back("csv/effectGraphics.csv");//エフェクトあり
	loadCsvPasses.emplace_back("csv/itemIconGraphics.csv");
	loadCsvPasses.emplace_back("csv/jobIconGraphics.csv");
	loadCsvPasses.emplace_back("csv/talentIconGraphics.csv");

}
//単一画像のグラフィックハンドルのロード
void ResourceManager::LoadGraphicCsv(std::string pass, std::vector<int>& putInVector)
{
	//引数のURLで指定されたCSVファイルの中身を文字列として取得する
	auto loadCsv = tnl::LoadCsv(pass);
	for (int i = 1; i < loadCsv.size(); ++i) {
		//取得した文字列の画像パスで画像データを生成する
		int gh = gManager->LoadGraphEx(loadCsv[i][1]);
		//引数で指定したvectorに生成した画像データハンドルを格納する
		putInVector.emplace_back(gh);
	}
}

void ResourceManager::LoadAnimGraphicCsv(std::string pass, std::vector<std::vector<int>>& putInVector)
{
	//引数のURLで指定されたCSVファイルの中身を文字列として取得する
	auto loadCsv = tnl::LoadCsv(pass);
	for (int i = 1; i < loadCsv.size(); ++i) {

		int allNum = std::stoi(loadCsv[i][2]);
		int widthNum = std::stoi(loadCsv[i][3]);
		int heightNum = std::stoi(loadCsv[i][4]);
		int widthSize = std::stoi(loadCsv[i][5]);
		int heightSize = std::stoi(loadCsv[i][6]);

		//取得した文字列の画像パスで画像データを生成する
		gManager->LoadDivGraphEx(loadCsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, putInVector[i - 1]);
	}
}
