#include <iostream>
//#include <boost/version.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iomanip>
//#include<boost/serialization/serialization.hpp>

#include"json11.hpp"

//クライアントはdxlibとboostで組む
//クライアントの情報を、変更が起こるたびにサーバーに差分だけ送る
//新しいオブジェクトが生成されたときはオブジェクトの情報をシリアライズして送り、共有する

//サーバーはnode.jsで作る
//定期的にサーバーからタイマーイベントで接続中の全てのクライアントにすべての情報を同期する

//クライアントのboost関数を非同期にするかどうかは勉強する



/*
#pragma comment(lib,"Ws2_32.lib")
#include<winsock.h>

WSADATA WinSockDataStorage = { 0 };
SOCKET ConnectSocket;//相手に接続要求を出し、そのままパケット通信をするソケット

SOCKADDR_IN ServerInfo = { 0 };//鯖情報を格納する構造体
*/
using namespace std;
using namespace json11;
namespace asio = boost::asio;
namespace ip = asio::ip;
using asio::ip::tcp;

//テスト用の数字
int num1 = 10;
int num2 = 3;

/*
int main(void) {
	
	//リクエストに対するレスポンス
	string allRes = "";

	try
	{
		//宣言
		asio::io_service io_service;
		//tcpソケットの作成
		ip::tcp::socket socket(io_service);
		boost::system::error_code error;

		//名前解決(ホスト名からIPアドレスに変換)
		ip::tcp::resolver resolver(io_service);
		ip::tcp::resolver::query query("127.0.0.1", "HTTP");

		//ホスト情報の設定
		ip::tcp::endpoint endpoint(*resolver.resolve(query));

		//接続
		socket.connect(endpoint, error);

		if (error) {
			std::cout << "cannot connect: " << error.message() << std::endl;
		}
		else {
			std::cout << "connected\n " << std::endl;
		}


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

		//メッセージを受信
		asio::streambuf response;

		while (asio::read(socket, response, asio::transfer_at_least(4), error)) {
			//streambufからstringに変換
			string tmp = asio::buffer_cast<const char*>(response.data());
			allRes += tmp.substr(0, response.size());
		}
	}
	catch (exception& e) {
		cout << e.what() << '\n';
		return 1;
	}

	//二重改行で区切る(レスポンスボディを取得するため)
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