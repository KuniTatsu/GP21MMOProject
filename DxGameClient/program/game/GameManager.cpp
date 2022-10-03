#include "GameManager.h"
#include "scene/scene_base.h"
#include "scene/scene_title.h"
#include"SceneManager.h"

#include <cstdlib>
#include <iostream>


GameManager* GameManager::instance = nullptr;

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ip = boost::asio::ip;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//-----------------------------------------------------------------------------------------
// コンストラクタ
GameManager::GameManager() {
	SetBackgroundColor(32, 32, 32);
	sManager = SceneManager::GetInstance();
}

//-----------------------------------------------------------------------------------------
// デストラクタ
GameManager::~GameManager() {

}


//-----------------------------------------------------------------------------------------
// シングルトンのインスタンス取得
GameManager* GameManager::GetInstance() {
	if (!instance) {
		instance = new GameManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// 破棄
void GameManager::Destroy() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void GameManager::ConnectServer()
{
    std::string host = "127.0.0.1";
    const auto  port = "9001";
    auto const  text ="";

    // The io_context is required for all I/O
    net::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver{ ioc };
    websocket::stream<tcp::socket> ws{ ioc };

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

//-----------------------------------------------------------------------------------------
void GameManager::Update(float delta_time) {
	sManager->Update(delta_time);
	sManager->Draw();
}










