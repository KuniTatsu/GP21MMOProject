#pragma once
#include<list>
#include<vector>
#include<memory>
#include"../dxlib_ext/dxlib_ext.h"

class Effect;
class Camera;
class EffectManager
{
public:
	// �C���X�^���X�̎擾
	static EffectManager* GetInstance();

	void CreateEffect(int type,tnl::Vector3& pos);

	void Update(const float deltatime);

	void Draw(Camera* camera);

	enum class EFFECTTYPE:uint32_t {
		NORMAL,
		WATER,
		DEATH,
		MAX
	};
	
private:
	EffectManager();
	~EffectManager();

	void LoadEffectCsv();

private:
	static EffectManager* instance;

	//���ݍĐ����̃G�t�F�N�g
	std::list<std::shared_ptr<Effect>>liveEffect;

	std::vector<std::shared_ptr<Effect>>effectMaster;


};

