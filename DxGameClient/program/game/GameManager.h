#pragma once
#include "../dxlib_ext/dxlib_ext.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>


class SceneManager;
class GameManager {
private :
	GameManager();
	~GameManager();
	static GameManager* instance;

	SceneManager* sManager = nullptr;

public :

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Update(float delta_time);

	void Destroy();

public :

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��

	//�T�[�o�[�Ƃ̃n���h�V�F�C�N
	void ConnectServer();
	


};




