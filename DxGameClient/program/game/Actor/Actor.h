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
	inline const std::shared_ptr<ActorData>GetActorData() {
		return myData;
	}
	void SetActorData(float attack, float defence, float moveSpeed);

	void SetActorAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	//typeの取得
	inline int GetActorType() {
		return actorType;
	}
	inline void SetActorType(int type) {
		if (type > 1)return;
		if (type == actorType)return;
		actorType = type;
	}

	//キャラ画像の四点の座標を求める関数 左上,右上,左下,右下
	std::vector<tnl::Vector3> GetCharaEdgePos();

	//向いている向きの取得
	inline int GetDir() {
		return static_cast<int>(myExDir);
	}

	void SetCircleSize(tnl::Vector3& size);

	//半径取得
	inline float GetCircleSize() {
		return circleSize;
	}

	//通常攻撃間隔の変更関数
	inline void SetCanAttackTime(float time) {
		if (time <= 0.0f)return;
		canAttackTime = time;
	}
	//通常攻撃間隔の取得関数
	inline float GetCanAttackTime(float time) {
		return canAttackTime;
	}

	inline void SetName(std::string Name) {
		name = Name;
	}

	inline std::string GetName() {
		return name;
	}

	inline const std::vector<int>& GetGhs() {
		return ghs;
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

	//test
	std::vector<tnl::Vector3> bufPos;

	//名前
	std::string name = "";

	//プレイヤーか敵か
	int actorType = 0;//デフォルトはプレイヤー


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
	float actWait = actSpeed;
	//描画するアニメーション配列のインデックス番号
	int actIndex = 0;

	////アニメーションが減るスピード 標準は1
	//float decreaseAnimSpeed = 1;

	//アニメーションの再生モード
	enum class ANIMMODE {
		NORMAL,
		FAST2X,
		FAST3X,
		HALF,
		STOP,
		MAX
	};

	//今のアニメーションの再生モード
	int nowAnimMode = static_cast<int>(ANIMMODE::NORMAL);

	//モードごとのスピード
	const float ANIMSPEED[static_cast<int>(ANIMMODE::MAX)] = { 1.0,2.0,3.0,0.5,0 };

	//通常攻撃の検知間隔
	float canAttackTime = 1.0f;
	//通常攻撃の現在のインターバル
	float attackInterval = 0.0f;

	GameManager* gManager = nullptr;

	bool isLive = true;

	//当たり判定用の半径
	float circleSize = 0.0f;

	//方向
	enum class DIR {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};


	//方向 8方向バージョン 回転を前提　こっちを使うこと
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

	//通常攻撃エフェクト用距離オフセット
	tnl::Vector3 EFFECTOFFSET[8] = {};

	//アニメーションするgh 本来はこっちを使う
	std::vector<int>ghs;


	//このクラス内でしか使わない関数はここに書く
private:


	//向いている方向の任意座標を取得する関数
	tnl::Vector3 GetPositionToVector(tnl::Vector3& myPos, tnl::Vector3& distance);

	//ある座標と、線分との最近点との一番近い点を求める関数
	tnl::Vector3 GetNearestPoint(tnl::Vector3& Pos, std::vector<tnl::Vector3>& boxPos);

	//通常攻撃用エフェクト用のオフセットを求める関数
	void SetDefaultAttackOffset();

	//継承先で使う関数かつprivateなものはここに書く
protected:

	//XとYから方向を返す関数
	uint32_t GetExDir(float x, float y);

	void SetExDirFromInt(int dir);

	//XとYから自分の向いている方向を変更する関数
	void SetExDir(float x, float y);

	//引数から向いている方向を変更する関数
	void SetExDir(int dir);

	//アニメーションモードを変更する関数
	void ChangeAnimMode(int changeMode);

	//基本攻撃関数	
	void DefaultAttack();

	//通常攻撃のインターバル更新
	void UpdateAttackInterval(const float deltatime);

	//基本攻撃の近接タイプの範囲を計算する関数 左上,右上,左下,右下の順
	std::vector<tnl::Vector3>GetMeleeAttackBox();
	//アニメーション更新関数
	void Anim(std::vector<int> DrawGhs, int MaxIndex, int Speed = 20);

	/*マップとキャラクターの当たり判定*/
	bool HitMaptoCharacter(tnl::Vector3& pos);

};

