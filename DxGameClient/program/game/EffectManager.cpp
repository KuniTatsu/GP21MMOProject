#include "EffectManager.h"
#include"ResourceManager.h"
#include"Effect.h"

EffectManager* EffectManager::instance = nullptr;
EffectManager* EffectManager::GetInstance()
{
	if (!instance) {
		instance = new EffectManager();
	}
	return instance;
}

void EffectManager::CreateEffect(int type, tnl::Vector3& pos)
{
	auto& effectList = ResourceManager::GetInstance()->GetAnimVector(static_cast<int>(ResourceManager::RESOUCETYPE::EFFECT));

	int id = effectMaster[type]->GetId();
	int maxMotionIndex = effectMaster[type]->GetMaxIndex();
	float actSpeed = effectMaster[type]->GetActSpeed();

	auto effect = std::make_shared<Effect>(effectList[type], pos, id, maxMotionIndex, actSpeed);

	liveEffect.emplace_back(effect);
}

void EffectManager::Update(const float deltatime)
{
	if (liveEffect.empty())return;
	for (const auto& effect : liveEffect) {
		effect->Update();
	}

	for (auto itr = liveEffect.begin(); itr != liveEffect.end(); ) {
		bool isLive = (*itr)->GetIsLive();
		if (!isLive) {
			//生きているエフェクトリストから削除
			itr = liveEffect.erase(itr);
		}
		else {
			++itr;
		}
	}
}

void EffectManager::Draw(Camera* camera)
{
	if (liveEffect.empty())return;
	for (const auto& effect : liveEffect) {
		effect->Draw(camera);
	}
}

EffectManager::EffectManager()
{
	LoadEffectCsv();
}

EffectManager::~EffectManager()
{
}

void EffectManager::LoadEffectCsv()
{
	auto loadEffect = tnl::LoadCsv("Csv/EffectRef.csv");

	//int id,int MaxIndex, float ActSpeed = 3.0f
	for (int i = 1; i < loadEffect.size(); ++i) {
		int id = stoi(loadEffect[i][0]);
		int maxIndex = stoi(loadEffect[i][1]);
		float actSpeed = std::stof(loadEffect[i][2]);

		std::shared_ptr<Effect> newEffect = std::make_shared<Effect>(id, maxIndex, actSpeed);

		effectMaster.emplace_back(newEffect);
	}
}
