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
		LoadAnimGraphicCsv(loadCsvPasses[type], GetAnimVector(type), type);
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
	case static_cast<uint32_t>(RESOUCETYPE::SKILL):
		return skillGhs;
		break;
	default:
		break;
	}
}

std::vector<tnl::Vector3>& ResourceManager::GetGraphicSize(int type)
{
	return graphicSizes[type];
}

ResourceManager::ResourceManager()
{
	gManager = GameManager::GetInstance();

	graphicSizes.resize(static_cast<int>(RESOUCETYPE::MAX));
	SetLoadCsvPass();
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::SetLoadCsvPass()
{

	loadCsvPasses.emplace_back("csv/playerGraphics.csv");//�G�t�F�N�g����
	loadCsvPasses.emplace_back("csv/enemyGraphics.csv"); //�G�t�F�N�g����
	loadCsvPasses.emplace_back("csv/effectGraphics.csv");//�G�t�F�N�g����
	loadCsvPasses.emplace_back("csv/itemIconGraphics.csv");
	loadCsvPasses.emplace_back("csv/jobIconGraphics.csv");
	loadCsvPasses.emplace_back("csv/talentIconGraphics.csv");

}
//�P��摜�̃O���t�B�b�N�n���h���̃��[�h
void ResourceManager::LoadGraphicCsv(std::string pass, std::vector<int>& putInVector)
{
	//������URL�Ŏw�肳�ꂽCSV�t�@�C���̒��g�𕶎���Ƃ��Ď擾����
	auto loadCsv = tnl::LoadCsv(pass);
	for (int i = 1; i < loadCsv.size(); ++i) {
		//�擾����������̉摜�p�X�ŉ摜�f�[�^�𐶐�����
		int gh = gManager->LoadGraphEx(loadCsv[i][1]);
		//�����Ŏw�肵��vector�ɐ��������摜�f�[�^�n���h�����i�[����
		putInVector.emplace_back(gh);
	}
}

void ResourceManager::LoadAnimGraphicCsv(std::string pass, std::vector<std::vector<int>>& putInVector, int type)
{
	//������URL�Ŏw�肳�ꂽCSV�t�@�C���̒��g�𕶎���Ƃ��Ď擾����
	auto loadCsv = tnl::LoadCsv(pass);
	for (int i = 1; i < loadCsv.size(); ++i) {

		int allNum = std::stoi(loadCsv[i][2]);
		int widthNum = std::stoi(loadCsv[i][3]);
		int heightNum = std::stoi(loadCsv[i][4]);
		int widthSize = std::stoi(loadCsv[i][5]);
		int heightSize = std::stoi(loadCsv[i][6]);

		SetGraphicSize(type, widthSize, heightSize);

		//�擾����������̉摜�p�X�ŉ摜�f�[�^�𐶐�����
		gManager->LoadDivGraphEx(loadCsv[i][1], allNum, widthNum, heightNum, widthSize, heightSize, putInVector[i - 1]);
	}
}

void ResourceManager::SetGraphicSize(int type, int width, int height)
{
	graphicSizes[type].emplace_back(tnl::Vector3(width, height, 0));

}
