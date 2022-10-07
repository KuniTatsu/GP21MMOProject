#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>

class SceneBase;
class SceneManager;
class GameManager {
private :
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;

	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

public :

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();



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

};




