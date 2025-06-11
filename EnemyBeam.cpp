#include "EnemyBeam.h"
#include "DxLib.h"
#include "string"

namespace
{
	const int ENEMYBEAM_IMAGE_WIDTH = 16; // �e�̉摜�̕�;
	const int ENEMYBEAM_IMAGE_HEIGHT = 48; // �e�̉摜�̍���;
	const float BULLET_INIT_SPEED = 200.0f; // �e�̏����ړ����x;
	const std::string BULLET_IMAGE_PATH = "Assets\\ebeams.png";
}

EnemyBeam::EnemyBeam()
	:GameObject(), hImage_(-1),
	pos_({ -10,-10 }), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }),pl(NULL)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
	dx = pl->GetX() - pos_.x;
	dy = pl->GetY() - pos_.y;
	length = sqrtf(dx * dx + dy * dy);
}

EnemyBeam::EnemyBeam(float x, float y, Player* player)
	:GameObject(), hImage_(-1),
	pos_({x, y}), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }), pl(player)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
	dx = pl->GetX() - pos_.x;
	dy = pl->GetY() - pos_.y;
	length = sqrtf(dx * dx + dy * dy);
}

EnemyBeam::EnemyBeam(Point pos_, Player* player)
	:GameObject(), hImage_(-1),
	pos_(pos_), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }), pl(player)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
	dx = pl->GetX() - pos_.x;
	dy = pl->GetY() - pos_.y;
	length = sqrtf(dx * dx + dy * dy);
}

EnemyBeam::~EnemyBeam()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // �摜�̊J��
	}
	hImage_ = -1; // �摜�n���h���𖳌���
}

void EnemyBeam::Update()
{
	float dt = GetDeltaTime();

	float vx = dx / length * speed_ * dt;
	float vy = dy / length * speed_ * dt;

	pos_.x = pos_.x + vx; // �e�̈ړ�
	pos_.y = pos_.y + vy; // �e�̈ړ�
	if (pos_.y >= WIN_HEIGHT)
	{
		isFired_ = false;
		SetAlive(false); // �Q�[���I�u�W�F�N�g���A�N�e�B�u�ɂ���
	}
}

void EnemyBeam::Draw()
{
	// ���˂���Ă�����`��
	if (isFired_)
	{
		DrawExtendGraph(pos_.x, pos_.y, 
			pos_.x + imageSize_.x, pos_.y + imageSize_.y, 
			hImage_, TRUE); // �`�� 
	}
}
