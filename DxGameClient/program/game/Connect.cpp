
#include"Connect.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include"GameManager.h"
#include"EnemyManager.h"
#include <cstdlib>
#include <iostream>

#include"../json11.hpp"

#include<boost/version.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

using namespace json11;

// The io_context is required for all I/O
net::io_context ioc;

//// These objects perform our I/O
tcp::resolver resolver{ ioc };
websocket::stream<tcp::socket> ws{ ioc };


Connect::Connect()
{
	//std::cout << BOOST_VERSION << std::endl;
	/*int major = BOOST_VERSION / 100000;
	int minor = BOOST_VERSION / 100 % 1000;
	int patch = BOOST_VERSION % 100;

	auto hoge = "boost.version" + std::to_string(major) + "." + std::to_string(minor);
	std::cout << "boost version " << major << "." << minor << "." << patch
		<< " or " << BOOST_LIB_VERSION << std::endl;*/

	gManager = GameManager::GetInstance();
}

Connect::~Connect()
{
}

int Connect::ConnectServer()
{

	try
	{
		// Look up the domain name

		auto const results = resolver.resolve(host, port);

		// Make the connection on the IP address we get from a lookup
		auto ep = net::connect(ws.next_layer(), results);

		// Update the host_ string. This will provide the value of the
		// Host HTTP header during the WebSocket handshake.
		// See https://tools.ietf.org/html/rfc7230#section-5.4
		host += ':' + std::to_string(ep.port());

		// Set a decorator to change the User-Agent of the handshake
		ws.set_option(websocket::stream_base::decorator(
			[](websocket::request_type& req)
			{
				req.set(http::field::user_agent,
					std::string(BOOST_BEAST_VERSION_STRING) +
					" websocket-client-coro");
			}));

		// Perform the websocket handshake
		ws.handshake(host, "/");
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;

}
//�`���b�g���M
void Connect::SendClientMessage(std::string sendMessage)
{
	const std::string  text = sendMessage;

	Json obj = Json::object({
		{ "chat", text },
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);

	ws.write(net::buffer(fix));

}

const std::string Connect::GetServerMessage()

{
	// This buffer will hold the incoming message
	beast::flat_buffer buffer;
	// Read a message into our buffer
	ws.read(buffer);

	ws.text(true);

	const std::string getMessage = beast::buffers_to_string(buffer.data());

	tnl::DebugTrace("�ǂݎ�萬��");
	tnl::DebugTrace(getMessage.c_str());
	tnl::DebugTrace("\n");

	std::string err;
	auto hoge = json11::Json::parse(getMessage, err);

	//�v���C���[�̃T�[�o�[�ޏo�n�̏�񏈗�
	if (hoge["ExitPlayerUUID"].string_value() != "") {
		std::string message = "";
		message = gManager->UTF8toSjis(hoge["ExitPlayerUUID"].string_value());

		gManager->PopOtherPlayerInUUID(message);
		return "";
	}

	//enemy�̈ʒu���n�̏���(���N���C�A���g�Ő������ꂽ�G�̐������܂�)
	//if (hoge["EPosX"].string_value() != "") {
	int aaa = hoge["EPosX"].int_value();

	bool isnull = hoge["EPosX"].is_null();
	if (hoge["EPosX"].is_null()!=true) {

		auto enemyManager = EnemyManager::GetInstance();

		int id = hoge["id"].int_value();
		float x = static_cast<float>(hoge["EPosX"].number_value());
		float y = static_cast<float>(hoge["EPosY"].number_value());
		int dir = hoge["dir"].int_value();
		int type = hoge["type"].int_value();
		enemyManager->ShareEnemyPosFromServer(id, x, y, dir, type);
		return "";
	}

	//enemy�̃X�e�[�^�X�ϓ��n�̏���
	if (hoge["EMoveHP"].string_value() != "") {
		auto enemyManager = EnemyManager::GetInstance();

		int id = hoge["id"].int_value();
		float moveHP = static_cast<float>(hoge["EMoveHP"].number_value());

		enemyManager->ShareEnemyStatusFromServer(id, moveHP);
		return "";
	}

	//enemy�̎��S�󋵂̏���
	if (hoge["isDead"].string_value() != "") {
		auto enemyManager = EnemyManager::GetInstance();
		int id = hoge["id"].int_value();

	}

	//UUID���܂ރ��b�Z�[�W���ǂ������� �܂܂Ȃ��Ȃ�`���b�g���b�Z�[�W�Ȃ̂ł��̂܂܋A��
	if (hoge["UUID"].string_value() == "")return getMessage;

	//UUID���܂ނȂ�v���C���[�̈ʒu���W���Ȃ̂ł������̏����ɐi��
	//����isCreated��1�Ȃ�_�~�[�͍쐬�ς݂Ȃ̂ňʒu���W�X�V�֐����Ă�
	if (hoge["isCreated"].int_value() == 1) {

		auto x = static_cast<float>(hoge["posX"].number_value());
		auto y = static_cast<float>(hoge["posY"].number_value());
		auto dir = hoge["dir"].int_value();

		auto UUID = gManager->UTF8toSjis(hoge["UUID"].string_value());

		gManager->MoveDummyInUUID(x, y, dir, UUID);
	}
	else {
		gManager->CreateDummyPlayer(getMessage);
	}

	return "";
}


void Connect::EntryServer(std::string playerName)
{
	const std::string  text = playerName;
	Json obj = Json::object({
		{ "playerName", text },
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));
}
//UUID���擾����ini�t�@�C���ŏo��
void Connect::GetEntryUserId()
{
	// This buffer will hold the incoming message
	beast::flat_buffer buffer;
	// Read a message into our buffer
	ws.read(buffer);

	ws.text(true);

	const std::string getMessage = beast::buffers_to_string(buffer.data());

	std::string err;
	auto hoge = json11::Json::parse(getMessage, err);
	//Json::parse()
	std::string message = "";

	message = gManager->UTF8toSjis(hoge["UUID"].string_value());

	if (message == "") {
		return;
	}
	//UUID�̓o�^
	gManager->SetClientUUID(message);

	bool check = WritePrivateProfileString("UUID", "data", message.data(), "clientUUID.ini");
	if (!check) {
		tnl::DebugTrace("�������ݎ��s");
		tnl::DebugTrace("\n");
	}
}

void Connect::SendClientPlayerInfo(float x, float y, int dir, int isCreated, int ghNum, int isDebug)
{
	//const std::string  text = playerName;
	std::string UUID = "";
	if (isDebug == 0) {
		UUID = gManager->GetClientUUID();
	}
	else {
		UUID = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
	}

	Json obj = Json::object({
		{ "PlayerposX", x },
		{ "PlayerposY", y },
		{ "PlayerUUID", UUID },
		{"Dir",dir},
		{"IsCreated",isCreated},
		{ "Playergh", ghNum },
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));

}

void Connect::SendClientEnemyInfo(float x, float y, int dir, int identificationNum, int type)
{
	Json obj = Json::object({
		{ "EnemyPosX", x },
		{ "EnemyPosY", y },
		{ "Dir",dir},
		{ "identId",identificationNum},
		{ "type",type},
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));
}

void Connect::SendClientEnemyStatus(int identificationNum, float moveHP)
{
	Json obj = Json::object({
		{ "EnemyMoveHP", moveHP },
		{ "identId",identificationNum},
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));
}

void Connect::SendClientEnemyIsDead(int identificationNum, int isDead)
{
	Json obj = Json::object({
		{ "isDead", isDead },
		{ "identId",identificationNum},
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));
}

void Connect::SendExitServer()
{
	std::string UUID = gManager->GetClientUUID();
	Json obj = Json::object({
		{ "ExitPlayerUUID", UUID },
		});

	std::string send = obj.dump();

	auto fix = gManager->SjistoUTF8(send);
	ws.write(net::buffer(fix));


}

