#pragma once

class GameManager;

class JobLevelConverter {
public:
	// �C���X�^���X�̎擾
	static JobLevelConverter * GetInstance();

private:
	JobLevelConverter();
	~JobLevelConverter();

private:
	static JobLevelConverter* instance;
	GameManager* gManager = nullptr;

};