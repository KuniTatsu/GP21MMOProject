#pragma once
#include<string>
#include<vector>

class Connect
{
public:
	Connect();
	~Connect();


	int ConnectServer();
	void SendClientMessage(std::string sendMessage);

	void GetServerMessage(std::vector<std::string>& Save);

private:

	//�T�[�o�[��IP�A�h���X
	std::string host = "127.0.0.1";
	//std::string host = "192.168.80.129";

	//�|�[�g
	const std::string  port = "9001"; //80


	std::string	myLastMessage = "";

};

