#pragma once
class Spawn {
private:

	Spawn();
	~Spawn();

	static Spawn* instance;

	Spawn* spawn = nullptr;

public:
	
	static Spawn* GetInstance();



	void CreateEnemy(int SpawnMax);
};