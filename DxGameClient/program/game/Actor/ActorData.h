/*Actorの基本データを管理するクラス
	ステータスや画像なども含む
	個別の特別なステータス等がある場合は継承先で実装する方針で
*/
#pragma once
#include<vector>

class ActorData
{
public:
	ActorData();
	~ActorData();

	//レンジのgetter,setter
	inline float GetAttackRange() {
		return attackRange;
	}
	inline void SetAttackRange(float setRange) {
		if (setRange < 0.0)return;
		attackRange = setRange;
	}
	//横幅のgetter,setter
	inline double GetAttackWidth() {
		return attackWidth;
	}
	inline void SetAttackRange(double setWidth) {
		if (setWidth < 0.0)return;
		attackWidth = static_cast<float>(setWidth);
	}

	inline float GetAttack() {
		return attack;
	}

	inline float GetDefence() {
		return defence;
	}

	inline float GetMoveSpeed() {
		return moveSpeed;
	}

	void SetAllStatus(float Attack, float Defence, float MoveSpeed);

	void SetAttribute(int STR, int VIT, int INT, int MID, int SPD, int DEX);

	inline std::vector<int>& GetAttribute() {
		return attribute;
	}
	inline int GetLevel() {
		return level;
	}

	inline void  UpdateHp(double moveHp) {
		HP += static_cast<float>(moveHp);
	}

	inline void SetHP(float startHP) {
		HP = startHP;
	}

	inline const float GetHP() {
		return HP;
	}
	//攻撃力などの基本ステータスの計算と代入
	void CalcMainStatus();

	//HP以外のステータスを計算して代入
	void CalcDefaultStatus();

public:
	enum class ATTRIBUTE :uint32_t {
		STR,
		VIT,
		INT,
		MID,
		SPD,
		DEX,
		MAX
	};


private:

private:

	//通常攻撃の当たる距離(レンジ)基本値
	float attackRange = 100.0f;

	//攻撃力
	float attack = 0.0f;
	//魔法攻撃力
	float mgAttack = 0.0f;
	//防御力
	float defence = 0.0f;
	//魔法防御力
	float mgDefence = 0.0f;
	//移動スピード
	float moveSpeed = 0.0f;

	float hp = 0.0f;
	//通常攻撃の当たる横幅  デフォルトはキャラ画像と同じ幅
	float attackWidth = 32.0f;
	//暫定でHP
	float HP = 0.0f;

	//attribute
	std::vector<int>attribute;

	int str = 0;
	int vit = 0;
	int intelligence = 0;
	int mid = 0;
	int spd = 0;
	int dex = 0;

	int level = 1;

};

