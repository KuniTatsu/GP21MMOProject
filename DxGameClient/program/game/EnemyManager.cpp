#include "EnemyManager.h"
#include"EnemySpawnManager.h"
#include"Actor/Camera.h"
#include"Actor/Enemy.h"
#include"Actor/ActorData.h"
#include"GameManager.h"
#include<time.h>
#include<random>

EnemyManager* EnemyManager::instance = nullptr;

//-----------------------------------------------------------------------------------------
// コンストラクタ
EnemyManager::EnemyManager()
{
	gManager = GameManager::GetInstance();
	eSpawnManager = std::make_shared<EnemySpawnManager>();
	createCount = 0;
	LoadEnemyMaster();

	for (int i = 0; i < SPAWNLIMIT; ++i) {
		isUseEnemyIdentNum.emplace_back(false);
	}
}

//-----------------------------------------------------------------------------------------
// デストラクタ
EnemyManager::~EnemyManager()
{

}

void EnemyManager::LoadEnemyMaster()
{
	//enemyCsvを読み込む処理を書く //必要なカラム attackRange,attack,defence,moveSpeed


	//debug用 -本来はcsvから読み取って入れる値
	auto newEnemy = std::make_shared<Enemy>(tnl::Vector3{ 0,0,0 }, 3.0, 5.0f, 3.0f, 2.0f);
	enemyMaster.emplace_back(newEnemy);

}

//-----------------------------------------------------------------------------------------
/*シングルトン*/
EnemyManager* EnemyManager::GetInstance()
{
	if (!instance) {
		instance = new EnemyManager();
	}
	return instance;
}

//-----------------------------------------------------------------------------------------
// 破棄
void EnemyManager::Destory()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}
//敵の識別番号で開いている番号を調べ、返す関数
int EnemyManager::SearchBlankEnemyNum() {
	for (int i = 0; i < isUseEnemyIdentNum.size(); ++i) {
		//false:開いているならその番号を返す
		if (isUseEnemyIdentNum[i] != true) {
			isUseEnemyIdentNum[i] = true;
			return i;
		}
	}
	//開いている場所がないならエラーナンバーを返す
	return -1;
}
//Enemyの位置座標の同期
void EnemyManager::ShareEnemyPosFromServer(int identId, float x, float y, int dir, int type)
{
	bool canSpawn = true;

	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {

		int clientEnemyId = (*itr)->GetIdentId();
		//サーバーから通知されたIDとこのクライアント上の敵のIDが一致したら動かす
		if (clientEnemyId == identId)
		{
			(*itr)->MoveEnemyFromServerInfo(x, y, dir);
			canSpawn = false;
			break;
		}
	}
	//既に存在している敵を動かしたなら新規スポーンさせない
	if (!canSpawn)return;

	//一致しなかったらこのクライアント上にまだ存在していない敵なので、生成する
	tnl::Vector3 spawnPos(x, y, 0);
	CreateEnemyFromServer(type, identId, spawnPos);
}

void EnemyManager::ShareEnemyStatusFromServer(int identId, float moveHP)
{
	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {

		int clientEnemyId = (*itr)->GetIdentId();
		//サーバーから通知されたIDとこのクライアント上の敵のIDが一致したら動かす
		if (clientEnemyId == identId)
		{
			(*itr)->ChangeStatusFromServerInfo(moveHP);
			break;
		}
	}
}

void EnemyManager::ShareEnemyDead(int identId, int isDead)
{
	//送られてきたのが死亡通知だったら
	if (isDead == 1) {
		for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ++itr) {
			int clientEnemyId = (*itr)->GetIdentId();
			//サーバーから通知されたIDとこのクライアント上の敵のIDが一致したら殺す
			if (clientEnemyId == identId)
			{
				(*itr)->SetIsLive(false);
				break;
			}
		}
	}
}

/*エネミースポーン*/
void EnemyManager::SpawnEnemy(tnl::Vector3& PlayerPos)
{
	if (!spawntiming) {
		intervalCount++;
	}
	if (intervalCount % (60 * intervalLimit) == 0) {
		spawntiming = true;
	}
	if (createCount < SPAWNLIMIT && spawntiming) {
		eSpawnManager->SpawnEnemy(PlayerPos);
	}
}


std::shared_ptr<ActorData> EnemyManager::GetEnemyData(int type)
{
	auto data = enemyMaster[type]->GetActorData();

	return data;
}

/*エネミー生成*/
void EnemyManager::CreateEnemy(int type, tnl::Vector3& posEnemy)
{
	auto data = GetEnemyData(type);
	//auto newEnemy = std::make_shared<Enemy>(posEnemy, data->GetAttackRange(), data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());

	//個体識別番号を取得
	int identId = SearchBlankEnemyNum();
	//個体識別番号がエラー番号なら敵の生成を行わない
	if (identId == -1)return;

	//auto newEnemy = std::make_shared<Enemy>(posEnemy, 3, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed());
	auto newEnemy = std::make_shared<Enemy>(posEnemy, 3, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed(), identId);

	//サーバーに生成した敵の情報を送る
	gManager->SendEnemyInfoToServer(posEnemy.x, posEnemy.y, 1, identId, type);

	SetEnemyList(newEnemy);
	spawntiming = false;
	intervalCount = 0;
	createCount++;
	tnl::DebugTrace("エネミー生成された：%d\n", createCount);
}

void EnemyManager::CreateEnemyFromServer(int type, int identId, tnl::Vector3& spawnPos)
{
	auto data = GetEnemyData(type);
	auto newEnemy = std::make_shared<Enemy>(spawnPos, 3.0, data->GetAttack(), data->GetDefence(), data->GetMoveSpeed(), identId);
	SetEnemyList(newEnemy);
	createCount++;
	tnl::DebugTrace("エネミー生成された：%d\n", createCount);
}

void EnemyManager::Update(float deltatime)
{
	auto& list = GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Update();
	}


	//死んだ敵の処理
	for (auto itr = EnemyList.begin(); itr != EnemyList.end(); ) {
		bool& isLive = (*itr)->GetIsLive();
		if (!isLive) {
			//最近死んだ敵リストに登録
			recentDeadEnemyList.emplace_back((*itr));
			//生きている敵リストから削除
			itr = EnemyList.erase(itr);
			createCount--;
		}
		else {
			++itr;
		}
	}

	//最近死んだ敵リストの上限判定と処理
	if (recentDeadEnemyList.size() > MAXRECENTDEAD) {
		recentDeadEnemyList.pop_front();
	}

}

void EnemyManager::Draw(Camera* camera)
{

	auto& list = GetEnemyList();
	if (list.empty())return;

	for (auto&& enemy : list) {
		enemy->Draw(camera);
	}
}