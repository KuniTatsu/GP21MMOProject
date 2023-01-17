#pragma once
#include"Actor.h"

class Camera;
class GameManager;


//fukushi_develop
//gManager->GetVectorToPlayer�������ăv���C���[�ւ̕����x�N�g�����擾���A�����̎���moveSpeed���|�����l��1�t���[�����Ɉړ�����ړ���
//Move�֐���V�������A���̒��ɂ��̒l���擾����R�[�h���������A�ړ�������
//move�֐���update�̒��ŌĂ�orgameManager��update�Ń��X�g����Ă�
//Enemy�̃R���X�g���N�^�ɃO���t�B�b�N�X�n���h��int�^�ň����Ɏ����Ă���
//std::vector<int>�̎Q�Ƃ������Ɏ���

class Enemy : public Actor {
public:

	Enemy(tnl::Vector3 SpawnPos, std::shared_ptr<ActorData>& data, std::vector<int>& ghs, int type);

	~Enemy();

	int createEnemy = 0;

	void Update()override;

	void Draw(Camera* camera)override;

	void Init()override;

	void SetCircleSize(tnl::Vector3& size);

	inline float GetCircleSize() {
		return circleSize;
	}

private:
	int img_Ghost = 0;
	bool onFollowToPlayer = false;

	std::vector<int>myAnimationGh;

	/*�ړ��X�s�[�h*/
	float SPEED = 0;

	unsigned int ChangedColor();

	GameManager* gManager = nullptr;

	//�����蔻��p�̔��a
	float circleSize = 0.0f;

private:
	void SearchBox(tnl::Vector3 SpawnPos, double atackRange);
	void EnemyMove();

};