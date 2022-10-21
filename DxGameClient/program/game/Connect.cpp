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


	Json obj = Json::object({
		{ "sendMessage", text },
		});

	// Send the message
	//ws.write(net::buffer(text));

	ws.write(obj);

}

void Connect::GetServerMessage(std::vector<std::string>& Save)
{
	// This buffer will hold the incoming message
	beast::flat_buffer buffer;


	// Read a message into our buffer
	ws.read(buffer);

	ws.text(true);

	const std::string result = boost::asio::buffer_cast<const char*>(buffer.data());
	
	std::string getMessage = beast::buffers_to_string(buffer.data());

	//���������������b�Z�[�W�������ꍇ�͓o�^���Ȃ�
	if (getMessage == myLastMessage)return;
	//������vector�ɓo�^
	Save.emplace_back(getMessage);

}
