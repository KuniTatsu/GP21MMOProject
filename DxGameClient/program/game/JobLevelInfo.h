#pragma once
#include<unordered_map>


class GameManager;


class JobLevelInfo {
public:

private:


private:
	JobLevelInfo(int JobId1, int BonusValue1, int JobId2, int BonusValue2);
	~JobLevelInfo();

	// �E�ɑ΂���{�[�i�X�l�̊i�[	
	std::unordered_map<int, int> info;
};