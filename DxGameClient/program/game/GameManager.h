#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>

class SceneBase;
class SceneManager;

class ChatBase;
class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	ChatBase* chat = nullptr;

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

public :


	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	void Update(float delta_time);

	void Destroy();
	float deltaTime = 0.0f;

public :

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��
	// 
	//�P�ʃx�N�g���擾�֐�
	inline tnl::Vector3 GetFixVector(float X, float Y) {

		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);

	}

	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string Gh);

	//string�^�̕����R�[�h�ϊ�
	std::string SjistoUTF8(std::string srcSjis);
	std::string UTF8toSjis(std::string srcUTF8);

	//�����蔻�� �Z�`���m
	bool isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2);

};




