#include <iostream>
//#include <boost/version.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>
//#include<boost/serialization/serialization.hpp>

#include"json11.hpp"

//�N���C�A���g��dxlib��boost�őg��
//�N���C�A���g�̏����A�ύX���N���邽�тɃT�[�o�[�ɍ�����������
//�V�����I�u�W�F�N�g���������ꂽ�Ƃ��̓I�u�W�F�N�g�̏����V���A���C�Y���đ���A���L����

//�T�[�o�[��node.js�ō��
//����I�ɃT�[�o�[����^�C�}�[�C�x���g�Őڑ����̑S�ẴN���C�A���g�ɂ��ׂĂ̏��𓯊�����

//�N���C�A���g��boost�֐���񓯊��ɂ��邩�ǂ����͕׋�����



/*
#pragma comment(lib,"Ws2_32.lib")
#include<winsock.h>

WSADATA WinSockDataStorage = { 0 };
SOCKET ConnectSocket;//����ɐڑ��v�����o���A���̂܂܃p�P�b�g�ʐM������\�P�b�g

SOCKADDR_IN ServerInfo = { 0 };//�I�����i�[����\����
*/
using namespace std;
using namespace json11;
namespace asio = boost::asio;
namespace ip = asio::ip;
using asio::ip::tcp;

//�e�X�g�p�̐���
int num1 = 10;
int num2 = 3;

/*
int main(void) {
	
	//���N�G�X�g�ɑ΂��郌�X�|���X
	string allRes = "";

	try
	{
		//�錾
		asio::io_service io_service;
		//tcp�\�P�b�g�̍쐬
		ip::tcp::socket socket(io_service);
		boost::system::error_code error;

		//���O����(�z�X�g������IP�A�h���X�ɕϊ�)
		ip::tcp::resolver resolver(io_service);
		ip::tcp::resolver::query query("127.0.0.1", "HTTP");

		//�z�X�g���̐ݒ�
		ip::tcp::endpoint endpoint(*resolver.resolve(query));

		//�ڑ�
		socket.connect(endpoint, error);

		if (error) {
			std::cout << "cannot connect: " << error.message() << std::endl;
		}
		else {
			std::cout << "connected\n " << std::endl;
		}


		//���b�Z�[�W�𑗐M
	asio::streambuf request;
	boost::system::error_code writeError;
	ostream request_ostream(&request);

	string getRequest = "GET /server.php?value1=" + to_string(10)
		+ "&value2=" + to_string(20) + " HTTP/1.1\r\n"+" Host: 127.0.0.1\r\n\r\n";
	request_ostream << getRequest;

	asio::write(socket, request, writeError);


	if (writeError) {
		cout << "send failed:" << error.message() << endl;
	}
	else {
		cout << "send correct!\n" << endl;
	}

		//���b�Z�[�W����M
		asio::streambuf response;

		while (asio::read(socket, response, asio::transfer_at_least(4), error)) {
			//streambuf����string�ɕϊ�
			string tmp = asio::buffer_cast<const char*>(response.data());
			allRes += tmp.substr(0, response.size());
		}
	}
	catch (exception& e) {
		cout << e.what() << '\n';
		return 1;
	}

	//��d���s�ŋ�؂�(���X�|���X�{�f�B���擾���邽��)
	vector<string> res;
	res = boost::split(res, allRes, boost::is_any_of("\r\n\r\n"));

	string err;
	const Json jsonData = Json::parse(res[res.size() - 1], err);

	cout << jsonData.dump() << "\n\n";

	auto jsonArray = jsonData.array_items();
	cout << "   id value1 value2     ans" << endl;

	for (auto& item : jsonArray) {
		cout << setw(6) << right << item["id"].string_value() << " ";
		cout << setw(6) << right << item["value1"].string_value() << " ";
		cout << setw(6) << right << item["value2"].string_value() << " ";
		cout << setw(6) << right << item["ans"].string_value() << '\n';
	}

	return 0;
}

*/