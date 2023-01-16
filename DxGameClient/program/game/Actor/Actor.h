#pragma once

#include<functional>
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"

class GameManager;
class Camera;
class ActorData;

class Actor :public std::enable_shared_from_this<Actor>
{
	//getterなどはここに書く
public:
	Actor();
	virtual~Actor() {}

	//生死状態の獲得
	inline bool& GetIsLive() {
		return isLive;
	}
	//死亡判定セット関数
	inline void	SetIsLive(bool IsLive) {
		isLive = IsLive;
	}

	//描画座標の取得
	inline tnl::Vector3& GetPos() {
		return drawPos;
	}
	//描画座標のセット
	inline void	SetPos(tnl::Vector3 Pos) {
		drawPos = Pos;
	}
	//ローカル座標の取得
	inline tnl::Vector3& GetLocalPos() {
		return localPos;
	}
	//ローカル座標のセット
	inline void	SetLocalPos(tnl::Vector3 Pos) {
		localPos = Pos;
	}
	//actorDataの取得
	inline std::shared_ptr<ActorData>GetActorData() {
		return myData;
	}
	void SetActorData(double attackRange, float attack, float defence, float moveSpeed);

	//向いている向きの取得
	inline int GetDir() {
		return static_cast<int>(myExDir);
	}


	//*******純粋仮想関数 継承先で実装************//
	virtual void Update() = 0;

	virtual void Draw(Camera* camera) = 0;

	virtual void Init() = 0;

	//継承先で使うかつprivateな変数はここに書く
protected:
	//描画座標
	tnl::Vector3 drawPos;

	//ローカル座標
	tnl::Vector3 localPos;

	//キャラクター画像の幅 初期値はプレイヤーの基本の大きさ
	//横幅
	float width = 32.0f;
	//縦幅
	float height = 32.0f;

	//画像ハンドル
	int gh = 0;

	//アニメーション関係
	//アニメーション切替速度
	const int actSpeed = 20;
	//実際に今描画中のグラフィックハンドル
	int drawGh = 0;
	//現在の切り替えタイマー
	int actWait = actSpeed;
	//描画するアニメーション配列のインデックス番号
	int actIndex = 0;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//方向
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	//方向 8方向バージョン 回転を前提
	enum class EXDIR :uint32_t {
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

	//攻撃タイプ
	enum class ATTACKTYPE {
		MELEE,
		RANGE,
		MAX
	};
	//自分の向いている方向
	DIR myDir = DIR::DOWN;

	//自分の向いている方向(8方向Ver) こっちで今後動かしたい
	EXDIR myExDir = EXDIR::TOP;

	//攻撃タイプ->持っている武器の種別 初期値は近接
	ATTACKTYPE myType = ATTACKTYPE::MELEE;

	//各種Actorのデータ
	std::shared_ptr<ActorData> myData = nullptr;

	//向いている方向の距離のオフセット 上,右,下,左
	const tnl::Vector3 VECOFFSET[4] = { tnl::Vector3(1,-1,0),tnl::Vector3(1,1,0),tnl::Vector3(1,1,0),tnl::Vector3(-1,1,0) };

	//このクラス内でしか使わない関数はここに書く
private:
	//移動関数 上下左右

	void MoveUp();

	void MoveRight();

	void MoveDown();

	void MoveLeft();

	void MoveDummy() {};

	//向いている方向の任意座標を取得する関数
	tnl::Vector3 GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance);

	//継承先で使う関数かつprivateなものはここに書く
protected:
	//移動関数のポインタ配列
	const std::function< void(Actor*) > MOVEFUNC[4] = { &Actor::MoveUp,&Actor::MoveRight,&Actor::MoveDown,&Actor::MoveLeft };

	//XとYから方向を返す関数
	uint32_t GetExDir(float x, float y);

	void SetExDirFromInt(int dir);

	//XとYから自分の向いている方向を変更する関数
	void SetExDir(float x, float y);

	//引数から向いている方向を変更する関数
	void SetExDir(int dir);

	//基本攻撃関数	
	void DefaultAttack();

	//アニメーション更新関数
	void Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed = 20);


};

