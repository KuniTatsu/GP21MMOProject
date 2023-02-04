#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include<unordered_map>
#include<memory>
#include<list>
#include<thread>

class SceneBase;
class SceneManager;
class ChatBase;
class Map;
class Enemy;
class Player;
class Connect;
class DummyPlayer;
class UIEditor;

class GameManager {
private:
	GameManager();
	~GameManager();
	static GameManager* instance;

	bool init = false;

	SceneManager* sManager = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::shared_ptr<Connect> connect = nullptr;

	std::thread acceptThread;

	//マルチスレッドで動かす受信用関数
	void Accept();

	//マルチスレッドで動かす送信用関数
	void Send(const std::string sendMessage);


	ChatBase* chat = nullptr;
	//UIEditor* editor = nullptr;
	std::shared_ptr<UIEditor> uiEditor = nullptr;

	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;
	//各チャンクのマップポインタを持つ配列
	std::list<std::shared_ptr<Map>>Maps;

	//playerがいるマップのポインタ
	std::shared_ptr<Map>lastStayMap = nullptr;

	std::list<std::shared_ptr<Enemy>> Enemys;
	std::list<std::shared_ptr<DummyPlayer>>otherPlayers;

	std::string clientUUID = "";

	std::string playerName = "";


	// ゲーム全体で参照したい変数はここで用意
public:
	static constexpr int SCREEN_WIDTH = 1024;
	static constexpr int SCREEN_HEIGHT = 768;

	//一チャンクの一辺のチップ数
	const int MAPSIZE = 35;
	//一チップの大きさ
	const int CHIPWIDTH = 32;
	const int CHIPHEIGHT = 32;

	float deltaTime = 0.0f;

	const tnl::Vector3 MAPPOSOFFSET[8] = {
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//左上
		tnl::Vector3(0,-MAPSIZE * CHIPHEIGHT,0),//上
		tnl::Vector3(MAPSIZE * CHIPWIDTH,-MAPSIZE * CHIPHEIGHT,0),//右上
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,0,0),//左
		tnl::Vector3(MAPSIZE * CHIPWIDTH,0,0),//右
		tnl::Vector3(-MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0),//左下
		tnl::Vector3(0,MAPSIZE * CHIPHEIGHT,0),//下
		tnl::Vector3(MAPSIZE * CHIPWIDTH,MAPSIZE * CHIPHEIGHT,0)//右下 

	};
	//回転角の方向
	enum class ROTATEDIR :uint32_t {
		LEFTTOP,
		LEFT,
		LEFTBOTTOM,
		BOTTOM,
		RIGHTBOTTOM,
		RIGHT,
		RIGHTTOP,
		TOP,
		MAX
	};

	//座標回転時に使用する回転角の配列(角度) 上方向を0度とする。(左は+90度とする)
	const float ROTATEDEGREE[static_cast<uint32_t>(ROTATEDIR::MAX)] = {
		-45.0f,//左上
		-90.0f,//左
		-135.0f,//左下
		-180.0f,//下
		-225.0f,//右下
		-270.0f,//右
		-315.0f,//右上
		-360.0f//上
	};
	//マウス座標
	int mousePosX = 0;
	int mousePosY = 0;

	//UIを並べる方向
	enum class DIR {
		HORIZONTAL,
		VERTICAL,
		MAX
	};


public:
	// インスタンスの取得
	static GameManager* GetInstance();

	void Update(float delta_time);
	// 破棄
	void Destroy();

	inline void SetPlayerName(std::string name) {
		playerName = name;
	}
	inline std::string GetPlayerName() {
		return playerName;
	}

	//単位ベクトル取得関数
	inline tnl::Vector3 GetFixVector(float X, float Y) {
		float vecLength = std::sqrt(X * X + Y * Y);

		return tnl::Vector3(X / vecLength, Y / vecLength, 0);
	}


	//外積を取得する関数
	float GetCross(tnl::Vector3& vec1, tnl::Vector3& vec2) {
		return vec1.x * vec2.y - vec2.x * vec1.y;
	}

	//2つの座標間の距離を求める関数
	inline float GetLengthFromTwoPoint(tnl::Vector3& pos1, tnl::Vector3& pos2) {
		tnl::Vector3 vec = pos2 - pos1;
		return vec.length();
	}

	//4点の中央の座標を求める関数
	inline tnl::Vector3 GetCenterPosRect(std::vector<tnl::Vector3>& rectPos) {

		auto x = rectPos[1].x - rectPos[0].x;
		auto y = rectPos[3].y - rectPos[0].y;
		return tnl::Vector3(x, y, 0);
	}

	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string Gh);

	//複数枚の連なった画像をvectorに格納する関数
	void LoadDivGraphEx(const std::string pass, const int allNum, const int widthNum, const int heightNum,
		int xSize, int ySize, std::vector<int>& ghVector);

	//string型の文字コード変換
	std::string SjistoUTF8(std::string srcSjis);
	std::string UTF8toSjis(std::string srcUTF8);

	//当たり判定 短形同士
	bool isHitBox(tnl::Vector3& leftTop1, tnl::Vector3& rightBottom1, tnl::Vector3& leftTop2, tnl::Vector3& rightBottom2);
	//座標の回転	args:回転させたい座標,向いている方向(ROTATEDIRに準ずる),中心座標(デフォルトでは原点)
	tnl::Vector3 RotatePoint(tnl::Vector3& rotatePos, int dir, tnl::Vector3 centerPos = { 0,0,0 });
	tnl::Vector3 RotatePoint(tnl::Vector3& rotatePos, float degree, tnl::Vector3 centerPos = { 0,0,0 });

	//当たり判定 回転体と点座標 args1:当たり判定範囲の頂点座標4つ 左上,右上,左下,右下の順で入れること,args2:判定する点座標
	bool isHitRotateBox(std::vector<tnl::Vector3>& hitBoxPoint, tnl::Vector3& hitPoint);


	//2つの座標から中心座標を求める関数 args1:座標1,args2:座標2
	tnl::Vector3 GetCenterVector(tnl::Vector3& firstPos, tnl::Vector3& secondPos);

	//点から線分中の最近点を求める関数
	tnl::Vector3 GetNearestPointLine(const tnl::Vector3& point, const tnl::Vector3& linePointA, const tnl::Vector3& linePointB);

	//Player(このクライアントの)生成
	std::shared_ptr<Player> CreatePlayer();

	//再ログイン時のプレイヤー生成
	std::shared_ptr<Player>CreatePlayerFromServer(int posX, int posY, double HP, int ghNum);

	inline std::shared_ptr<Player>& GetPlayer() {
		return player;
	}

	//Map新規生成
	bool CreateMap();

	//そのマップにこのクライアントのPlayerがいるかどうか
	bool IsOnMap();

	//Playerのいるマップの登録
	void SetStayMap();
	//Player(このクライアントの)がいるマップポインタを取得する関数
	std::shared_ptr<Map>GetPlayerOnMap();

	//指定座標からマップを取得する関数
	std::shared_ptr<Map>GetMapOnPoint(tnl::Vector3& Point);

	//Playerが越境したかどうか確かめる関数
	bool IsOverChunk();

	//Mapポインタの中心座標からPlayerの中心座標への距離を求める関数
	float GetMapToPlayerDistance(std::shared_ptr<Map> map);

	//チャンク中心からチャンク中心への距離を求める関数
	inline float GetChunkDistance() {
		return static_cast<float>(MAPSIZE * CHIPHEIGHT);
	}

	//二つのPos同士の距離を取得する関数
	inline float GetLength(tnl::Vector3& PosA, tnl::Vector3& PosB) {
		return std::sqrt(((PosA.x - PosB.x) * (PosA.x - PosB.x)) + ((PosA.y - PosB.y) * (PosA.y - PosB.y)));
	}

	//マップリストの取得
	std::list<std::shared_ptr<Map>> GetMapList();

	//エネミーリストの取得
	inline std::list<std::shared_ptr<Enemy>>& GetEnemyList() {
		return Enemys;
	}

	//送信用スレッドを作成する関数
	void CreateSendThread(const std::string sendMessage);

	inline void SetEnemyList(std::shared_ptr<Enemy>& enemy) {
		Enemys.emplace_back(enemy);
	}
	tnl::Vector3 GetVectorToPlayer(tnl::Vector3& enemyPos);

	//メルセンヌ・ツイスターを採用した正規分布ランダム関数(ウェイトを考慮)
	int GerRandomNumInWeight(const std::vector<int>& WeightList);
	//メルセンヌ・ツイスターを採用した正規分布ランダム関数(1~100)
	bool CheckRandomNumberInOdds(const float maxOdds);


	//tnl::Vector3 GetVectorToPlayer(tnl::Vector3& enemyPos);

	//二つの整数の間のランダムな数を返す関数
	int GetRandBetweenNum(int num1, int num2);

	//このクライアントのUUIDを登録する関数
	inline void SetClientUUID(std::string UUID) {
		clientUUID = UUID;
	}
	//このクライアントのUUIDを取得する関数
	inline std::string GetClientUUID() {
		return clientUUID;
	}
	//connect取得
	inline std::shared_ptr<Connect>GetConnection() {
		if (connect)return connect;
		return nullptr;
	}

	//サーバーに接続する関数
	void ConnectServer();

	//チャット作成
	void CreateChat();

	//スレッド作成
	void CreateThread();

	//エネミーの情報を取得する関数
	void GetServerEnemyInfo();

	//サーバーから送られてきた他のプレイヤーの情報からDummyPlayerを生成し登録する関数
	bool CreateDummyPlayer(std::string json);

	bool CreateDummyPlayer(float posX, float posY, std::string UUID, int dir, float HP, int ghNum);

	//プレイヤーの情報をサーバーに送る関数
	void SendPlayerInfoToServer();

	//enemyが生成された時にサーバーに登録する関数
	void SendInitEnemyInfoToServer(float x, float y, int dir, int identNum, int type = -1);

	//enemyの情報をサーバーに送る関数 args1:x座標 args2:y座標HP args3:方角(8方向) args4:識別番号 args5:敵のタイプ
	void SendEnemyInfoToServer(float x, float y, int dir, int identNum, int type = -1);
	//enemyのHP変動をサーバーに送る関数 args1:識別番号 args2:変動HP args3:増加かどうか
	void SendEnemyMoveHPInfoToServer(int identNum, float moveHP, bool isPlus = true);

	//他のプレイヤーのリストを取得する関数
	const inline std::list<std::shared_ptr<DummyPlayer>>& GetOtherPlayersList() {
		return otherPlayers;
	}
	//UUIDと合致するDummyPlayerをリストから消去する関数
	void PopOtherPlayerInUUID(std::string UUID);

	//UUIDと合致するDummyPlayerがいるかどうか確かめる関数
	bool CheckIsThereInUUID(std::string UUID);

	//UUIDと合致するDummyPlayerを動かす関数
	void MoveDummyInUUID(float x, float y, int dir, std::string UUID);

	//UUIDと合致するDummyPlayerのHPを変動させる関数
	void UpdateDummyHP(std::string UUID, float moveHP);

	//サーバーにAttributeのデータを送信する関数
	void SendPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);
	//サーバーから来たAttributeのデータをセットする関数
	void SetPlayerAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	//サーバーにattributeを要求する関数
	void GetPlayerAttribute();
	//サーバーにPlayerデータを要求する関数
	void GetPlayerInfo(std::string UUID);

	//サーバーに名前を送る関数
	void EntryServer();
	//サーバーからUUIDを取得する関数
	void GetMyUUID();



	//四角形のマウスクリック感知
	bool isClickedRect(int RectLeft, int RectTop, int RectRight, int RectBottom);
	bool isClickedRect(tnl::Vector3& CenterPos, int halfSize = 16);

	//四角形のマウス範囲内感知
	bool OnMouseRect(int RectLeft, int RectTop, int RectRight, int RectBottom);

	//マウス座標の取得
	tnl::Vector3 GetMousePos();


};