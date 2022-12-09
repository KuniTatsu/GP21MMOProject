/*
特殊な動作を行うスキルの処理を実装するクラス
Skillクラスにポインタ変数として持たせる
SkillManagerから登録する
インスタンス生成時に使用する関数を選択する
*/

//ちょっと作りが微妙なので多分違う方法で実装すると思う

#pragma once
#include<functional>
#include<unordered_map>
#include<vector>
#include<string>
#include "../dxlib_ext/dxlib_ext.h"
#include<memory>

class SpecialSkillEffect
{
public:
	SpecialSkillEffect(int skillID);
	~SpecialSkillEffect();

	inline void SetSkillName(std::string name) {
		skillName = name;
	}

	//keyで引数返り値なしの関数を検索し、実行する関数
	std::function<void()> DoEvent(std::string key);
	//keyで引数,返り値tnl::Vector3の関数を検索し、実行する関数
	std::function<tnl::Vector3(tnl::Vector3)> DoPosEvent(std::string key);

private:
	//----------実行系----------//

	//各種特殊処理の効果を実行する関数を入れたmap(引数返り値なし)
	std::unordered_map<std::string, std::function<void()>> exEffects;

	//各種特殊処理の効果を実行する関数を入れたmap(引数,返り値 tnl::vector3)
	std::unordered_map<std::string, std::function<tnl::Vector3(tnl::Vector3)>> exPosEffect;

	//登録
	void SetMap(std::string key, void func());
	void SetPosMap(std::string key, tnl::Vector3 func(tnl::Vector3));


	//----------各種スキルの処理関数----------//
	tnl::Vector3 MoveForward(tnl::Vector3 pos);



private:
	//実際に発動するスキルの名前 検索用のキーになるため要注意
	std::string skillName = "";
};

