#include"Connect.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>

#include"../json11.hpp"

#include<boost/version.hpp>

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

std::string UTF8toSjis(std::string srcUTF8)
{
	//Unicodeへ変換後の文字列長を得る
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	memset(bufUnicode, 0, sizeof(char) * lenghtUnicode);

	//UTF8からUnicodeへ変換
	MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1, bufUnicode, lenghtUnicode);

	//ShiftJISへ変換後の文字列長を得る
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけShiftJIS文字列のバッファを確保
	char* bufShiftJis = new char[lengthSJis];

	memset(bufShiftJis, 0, sizeof(char) * lengthSJis);

	//UnicodeからShiftJISへ変換
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);

	std::string strSJis(bufShiftJis);

	delete[] bufUnicode;
	delete[] bufShiftJis;

	return strSJis;
}




Connect::Connect()
{
	//std::cout << BOOST_VERSION << std::endl;
	/*int major = BOOST_VERSION / 100000;
	int minor = BOOST_VERSION / 100 % 1000;
	int patch = BOOST_VERSION % 100;

	auto hoge = "boost.version" + std::to_string(major) + "." + std::to_string(minor);
	std::cout << "boost version " << major << "." << minor << "." << patch
		<< " or " << BOOST_LIB_VERSION << std::endl;*/

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


void Connect::SendClientMessage(std::string sendMessage)
{
	const std::string  text = sendMessage;

	myLastMessage = sendMessage;


	/*Json obj = Json::object({
		{ "message", text },
		});*/
		//obj.string_value();

		// Send the message
	ws.write(net::buffer(text));

	//ws.write(net::buffer(obj.string_value()));

}

void Connect::GetServerMessage(std::vector<std::string>& Save)
{
	// This buffer will hold the incoming message
	beast::flat_buffer buffer;


	// Read a message into our buffer
	ws.read(buffer);

	ws.text(true);

	const std::string result = boost::asio::buffer_cast<const char*>(buffer.data());

	const std::string getMessage = beast::buffers_to_string(buffer.data());

	std::string err;
	auto hoge = json11::Json::parse(getMessage,err);
	//Json::parse()

	auto message = UTF8toSjis(hoge["info"].string_value());
	auto count = hoge["count"].int_value();

	//自分が送ったメッセージだった場合は登録しない
	if (getMessage == myLastMessage)return;
	//引数のvectorに登録
	Save.emplace_back(message);

}
