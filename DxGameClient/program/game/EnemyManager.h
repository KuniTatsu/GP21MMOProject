#pragma once

#include<vector>
#include<memory>
#include<unordered_map>
#include "../dxlib_ext/dxlib_ext.h"

class Camera;
class GameManager;
class EnemySpawnManager;
class Enemy;
class ActorData;

class EnemyManager {
private:
	EnemyManager();
	~EnemyManager();

	static EnemyManager* instance;

	GameManager* gManager = nullptr;
	std::shared_ptr<EnemySpawnManager> eSpawnManager = nullptr;
	bool hoge = false;

	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	/*SpawnEnemy�֐�*/
//������
	int createCount = 0;
	//��������
	const int SPAWNLIMIT = 5;

	//�C���^�[�o���̃J�E���g�J�nFlag
	bool spawntiming = false;
	//��������܂ł̃C���^�[�o�����J�E���g
	int intervalCount = 0;
	//�C���^�[�o���̐�������
	const int intervalLimit = 5;

	std::vector<std::shared_ptr<Enemy>> enemyMaster;

	std::vector<bool>isUseEnemyIdentNum;

	//enemy�̎���Id
	std::unordered_map<int, int>matchDeadBodyId;

	//private�֐��Q
private:
	void LoadEnemyMaster();

public:
	//�C���X�^���X�̎擾
	static EnemyManager* GetInstance();
	void Destory();

	/*�G�l�~�[���*/
	enum class EnemyType : uint32_t {
		KOBOLD,
		SLIME,
		SKULL,
		MAX
	};

	/*�G�l�~�[���X�g*/
	std::list<std::shared_ptr<Enemy>> EnemyList;

	const int MAXRECENTDEAD = 10;

	//���߂Ŏ��񂾃G�l�~�[�̃��X�g(�h�菈���̂��߈ꎟ�ۑ�) �ő�10��
	std::list<std::shared_ptr<Enemy>> recentDeadEnemyList;

	//�G�l�~�[�X�|�[���E�F�C�g
	std::vector<int>EnemySpawnWeight;

	//Enemy�f�[�^�擾
	std::shared_ptr<ActorData> GetEnemyData(int type);

	//enemyId�擾
	int GetEnemyIdFromType(int type);

	//enemy���Ƃ̎���Id�̎擾
	int GetDeadBodyId(int enemyId);

	//

	//Enemy�X�|�[���͈͌���
	void SpawnEnemy(tnl::Vector3& PlayerPos);

	//�G�l�~�[���X�g�̎擾
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return EnemyList;
	}
	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		EnemyList.emplace_back(enemy);
	}
	//�G�̎��ʔԍ��ŊJ���Ă���ԍ��𒲂ׁA�Ԃ��֐�
	int SearchBlankEnemyNum();

	//�G�̎��ʔԍ������ɖ߂��֐�
	void ResetEnemyNum(int enemyNum);

	//�G�̎��ʔԍ��𖄂߂�֐�


	//Enemy�̈ʒu���W�̓���
	void ShareEnemyPosFromServer(int identId, float x, float y, int dir, int type);

	//Enemy�̃X�e�[�^�X�ύX�̓���
	void ShareEnemyStatusFromServer(int identId, float moveHP);

	//Enemy�̎��S�󋵂̓��� args1:���ʔԍ� args2:0->�����Ă�,1->����ł�
	//��{�I�ɂ͓G�����񂾂Ƃ��ɋ��L���邽�߂Ɏg��
	//�G�������Ԃ�n�̎��������邩������Ȃ��̂�0�Ő����Ԃ�悤�Ɏ�������]�n���c��
	void ShareEnemyDead(int identId, int isDead = 1);

	void SortEnemyList(tnl::Vector3& playerPos);

	/*�G�l�~�[�����֐�*/
	void CreateEnemy(int type, tnl::Vector3& posEnemy);
	//�T�[�o�[����̏��ł̃G�l�~�[�����֐�
	void CreateEnemyFromServer(int type, int identId, tnl::Vector3& spawnPos, int IsBig = 0);

	//Enemy�̐���������擾����֐�
	inline const int GetLimitEnemySpawn() {
		return SPAWNLIMIT;
	}

	void Update(float deltatime);
	void Draw(Camera* camera);
};