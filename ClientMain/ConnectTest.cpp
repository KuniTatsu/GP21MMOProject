#include <iostream>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;
namespace asio = boost::asio;
namespace ip = asio::ip;
using asio::ip::tcp;

/*
int main(void) {

	asio::io_service io_service;
	tcp::socket socket(io_service);

	boost::system::error_code error;

	//-----接続-----

	socket.connect(tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 80), error);

	if (error) {
		cout << "connect failed:" << error.message() << endl;
	}
	else {
		cout << "connected" << endl;
	}


	//-----メッセージ送信-----

	//asio::streambuf message;
	//boost::system::error_code writeError;

	//ostream request_ostream(&message);

	//string aaa = "HelloServer";
	//string hoge = "GET /server.php?message=" + aaa;
	//hoge += " HTTP/1.1\r\n";
	//hoge += "Host: 127.0.0.1\r\n\r\n";

	//cout << hoge+"\n" << endl;

	//request_ostream << hoge;

	//asio::write(socket, message, writeError);


	//if (writeError) {
	//	cout << "send failed:" << error.message() << endl;
	//}
	//else {
	//	cout << "send correct!\n" << endl;
	//}
	

//メッセージを送信
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
	

	//-----メッセージ受信-----
	asio::streambuf receive_buffer;
	boost::system::error_code receiveError;

	asio::read(socket, receive_buffer, asio::transfer_all(), receiveError);

	if (error && error != asio::error::eof) {
		cout << "receive failed:" << error.message() << endl;
	}
	else {
		const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
		cout << data << endl;
	}


}
*/