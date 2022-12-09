#include "Player.h"
#include"../GameManager.h"
#include"Camera.h"

Player::Player(int startX, int startY)
{
	drawPos.x = startX;
	drawPos.y = startY;
	gh = gManager->LoadGraphEx("graphics/Player.png");
	testGh = gManager->LoadGraphEx("graphics/test.png");
}

Player::~Player()
{

}

void Player::Update()
{
	Move();

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		DefaultAttack();
	}

}

void Player::Draw(Camera* camera)
{


	float x = drawPos.x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float y = drawPos.y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);
	DrawRotaGraph(x, y, 1, 0, gh, false);


	if (bufPos.empty())return;
	//test �����蔻��͈̔͂��摜�ŕ`��
	float boxX1 = bufPos[0].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY1 = bufPos[0].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX2 = bufPos[1].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY2 = bufPos[1].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX3 = bufPos[2].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY3 = bufPos[2].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	float boxX4 = bufPos[3].x - camera->pos.x + (GameManager::SCREEN_WIDTH >> 1);
	float boxY4 = bufPos[3].y - camera->pos.y + (GameManager::SCREEN_HEIGHT >> 1);

	//DrawBox(boxX1, boxY1, boxX2, boxY2, -1, true);

	/*DrawExtendGraph(boxX1, boxY1, boxX2, boxY2, testGh, true);*/
	//����A�E��A�E���A�����̒��_�̍��W 
	DrawModiGraphF(boxX1, boxY1, boxX2, boxY2, boxX4, boxY4, boxX3, boxY3, testGh, true);
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
		//myDir = DIR::UP;
		DrawStringEx(200, 300, -1, "UP");
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::DOWN)])) {
		moveY += MOVEAMOUNT[static_cast<int>(DIR::DOWN)];
		//myDir = DIR::DOWN;
	}

	//���E�L�[���m
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::RIGHT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::RIGHT)];
		//myDir = DIR::RIGHT;
	}
	if (tnl::Input::IsKeyDown(arrowKeys[static_cast<int>(DIR::LEFT)])) {
		moveX += MOVEAMOUNT[static_cast<int>(DIR::LEFT)];
		//myDir = DIR::LEFT;
		DrawStringEx(200, 400, -1, "LEFT");
	}
	if (moveX == 0 && moveY == 0)return;

	//�ړ��ʂ�0�łȂ���΃x�N�g���𐳋K�����Ĉړ�������
	if (moveX != 0 || moveY != 0) {
		//�P�ʃx�N�g���擾
		tnl::Vector3 fixVec = gManager->GetFixVector(moveX, moveY);

		//���x�{
		float fixMoveX = fixVec.x * SPEED;
		float fixMoveY = fixVec.y * SPEED;

		//���W�ړ�
		drawPos.x += fixMoveX;
		drawPos.y += fixMoveY;

		//�����ύX
		SetExDir(fixMoveX, fixMoveY);

	}

	//gManager->SetStayMap();
	if (gManager->IsOverChunk()) {
		gManager->CreateMap();
		gManager->SetStayMap();
	}
}
