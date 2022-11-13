#pragma once
#include"../library/tnl_vector.h"

class Camera;
class GameManager;

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
		SLIME,
		GOBLIN,
		MAX
	};

	/*�����_���ϐ�*/
	int random = 0;
	/*�͈͎w��̃����_���֐�*/
	int randomRange(int minRange, int maxRange);

	const int FIXDIS[4] = { -512,512,512,-512 };

	/*Enemy�X�|�[��*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);

public:
	//�C���X�^���X�̎擾
	static EnemyManager* GetInstance();

	void Destory();

	void CreateEnemy(tnl::Vector3 posEnemy);
	
	void Update();
	void Draw(Camera* camera);
};