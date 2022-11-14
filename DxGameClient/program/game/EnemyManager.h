#pragma once

#include<vector>
#include<memory>

class Camera;
class GameManager;
class Enemy;

class EnemyManager {
private:
	EnemyManager();
	~EnemyManager();

	static EnemyManager* instance;

	GameManager* gManager = nullptr;

	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	enum class EnemyType {
		GHOST,
		SLIME,
		GOBLIN,
		MAX
	};

	/*�����_���ϐ�*/
	int random = 0;
	/*�͈͎w��̃����_���֐�*/
	int randomRange(int minRange, int maxRange);

	//const int FIXDIS[4] = { -512,512,512,-512 };
	const int FIXDIS[4] = { -100,100,100,-100 };

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	///*Enemy�X�|�[��*/
	//void SpawnEnemy(tnl::Vector3& PlayerPos);

	//private�֐��Q
private:
	void LoadEnemyMaster();


public:
	//�C���X�^���X�̎擾
	static EnemyManager* GetInstance();

	void Destory();

	void CreateEnemy(tnl::Vector3 posEnemy);

	/*Enemy�X�|�[��*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);


	std::shared_ptr<Enemy>& GetEnemyData(int type);

	void Update(float deltatime);
	void Draw(Camera* camera);
};