#include "Player.h"
#include"../GameManager.h"
#include"Camera.h"

Player::Player(int startX, int startY)
{
	drawPos.x = startX;
	drawPos.y = startY;
	gh=gManager->LoadGraphEx("graphics/Player.png");
}

Player::~Player()
{

}

void Player::Update()
{
	Move();
}

void Player::Draw(Camera* camera)
{
	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH / 2);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT / 2);
	DrawRotaGraph(x, y, 1, 0, gh, false);
}

void Player::Init()
{
}

void Player::Move()
{
	//�ړ��ʃ��Z�b�g
	moveX = 0;
	moveY = 0;

	//�ǂ��ɂ����Ă܂Ƃ߂����@�֐��������������܂��v�����Ȃ�
	//�㉺�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::UP)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::UP)];
		DrawStringEx(200, 300, -1, "UP");
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
	}

	//���E�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
		DrawStringEx(200, 400, -1, "LEFT");
	}

	//�ړ��ʂ�0�łȂ���΃x�N�g���𐳋K�����Ĉړ�������
	if (moveX != 0 || moveY != 0) {
		
		tnl::Vector3 fixVec = gManager->GetFixVector(moveX, moveY);

		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		drawPos.x += fixMoveX;
		drawPos.y += fixMoveY;

	}
}
