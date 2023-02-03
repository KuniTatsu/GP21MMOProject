#pragma once

class GameManager;

class JobLevelConverter {
public:
	// インスタンスの取得
	static JobLevelConverter * GetInstance();

private:
	JobLevelConverter();
	~JobLevelConverter();

private:
	static JobLevelConverter* instance;
	GameManager* gManager = nullptr;

};