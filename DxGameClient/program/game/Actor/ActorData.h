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
		attackWidth = setWidth;
	}


private:

	//通常攻撃の当たる距離(レンジ)基本値
	float attackRange = 100.0f;

	//通常攻撃の当たる横幅  デフォルトはキャラ画像と同じ幅
	float attackWidth = 32.0f;


};

