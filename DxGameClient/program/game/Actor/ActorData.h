/*Actorの基本データを管理するクラス
	ステータスや画像なども含む
	個別の特別なステータス等がある場合は継承先で実装する方針で
*/
#pragma once


class ActorData
{
public:
	ActorData();
	~ActorData();

	//レンジのgetter,setter
	inline double GetAttackRange() {
		return attackRange;
	}
	inline void SetAttackRange(double setRange) {
		if (setRange < 0.0)return;
		attackRange = setRange;
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

	void SetAllStatus(double AttackRange, float Attack, float Defence, float MoveSpeed);

	void SetHP(float Hp);

private:

	//通常攻撃の当たる距離(レンジ)基本値
	double attackRange = 0.0f;

	//攻撃力
	float attack = 0.0f;
	//防御力
	float defence = 0.0f;
	//移動スピード
	float moveSpeed = 0.0f;

	float hp = 0.0f;


};

