#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class GameManager;
class EnemyManager;

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();

	GameManager* gManager = nullptr;
	EnemyManager* eManager = nullptr;

public:

	/*Enemy��ޑI��*/
	void SelectEnemy(tnl::Vector3 posEnemy);
	/*Enemy�X�|�[���͈͌���*/
	void SpawnEnemy(tnl::Vector3& PlayerPos);

private:

	//�G�l�~�[���m�����Ԃ��Ă��Ȃ����`�F�b�N
	bool CheckCanCreateEnemy(tnl::Vector3& Pos);

	/*�����_���ϐ�*/
	int random = 0;
	/*�͈͎w��̃����_���֐�*/
	int randomRange(int minRange, int maxRange);

};

