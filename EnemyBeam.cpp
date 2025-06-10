#include "EnemyBeam.h"
#include "DxLib.h"
#include "string"

namespace
{
	const int ENEMYBEAM_IMAGE_WIDTH = 16; // �e�̉摜�̕�;
	const int ENEMYBEAM_IMAGE_HEIGHT = 16; // �e�̉摜�̍���;
	const float BULLET_INIT_SPEED = 200.0f; // �e�̏����ړ����x;
	const std::string BULLET_IMAGE_PATH = "Assets\\ebeams.png";
}

EnemyBeam::EnemyBeam()
	:GameObject(), hImage_(-1),
	pos_({ -10,-10 }), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
}

EnemyBeam::EnemyBeam(float x, float y)
	:GameObject(), hImage_(-1),
	pos_({x, y}), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
}

EnemyBeam::EnemyBeam(Point pos_)
	:GameObject(), hImage_(-1),
	pos_(pos_), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
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
	pos_.y = pos_.y + speed_ * dt; // �e�̈ړ�
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
