#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include "Effect.h"
#include "EnemyBeam.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; // �G�̉摜�̕�;
	const int ENEMY_IMAGE_HEIGHT = 48; // �G�̉摜�̍���;

	const float ENEMY_INIT_X = 100; // �G�̏���X���W;
	const float ENEMY_INIT_Y = 100; // �G�̏���Y���W;
	const float ENEMY_INIT_SPEED = 1.5f; // �G�̏����ړ����x;

	const float ENEMY_CENTER_X = WIN_WIDTH / 2 - 120; // �G�̒�����
	const float ENEMY_MOVE_X = 200; // �G�̍��E�̃u��
	const float ENEMY_TIMER = 3.0f;
}


Enemy::Enemy()
	:GameObject(),
	hImage_(-1),
	x_(0), y_(0),
	oddspeed_(0), evenspeed_(0), cenx_(0), moveID_(0), Timer_(0), ID_(0), type_(MAX_ETYPE)
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png"); // �G�̉摜��ǂݍ���
	if (hImage_ == -1) {
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X; // �������W
	y_ = ENEMY_INIT_Y; // �������W
	oddspeed_ = ENEMY_INIT_SPEED; // �ړ����x
}

Enemy::Enemy(int id, ETYPE type, int moveID)
	:GameObject(),
	hImage_(-1),
	x_(ENEMY_INIT_X), y_(ENEMY_INIT_Y),
	oddspeed_(ENEMY_INIT_SPEED), evenspeed_(-ENEMY_INIT_SPEED),
	ID_(id), type_(type), cenx_(ENEMY_CENTER_X), moveID_(moveID), Timer_(ENEMY_TIMER)
{	

	// �摜�̓ǂݍ���
	std::string imagePath[MAX_ETYPE] = {
		"Assets\\tiny_ship10.png", // ZAKO
		"Assets\\tiny_ship18.png", // MID
		"Assets\\tiny_ship16.png", // KNIGHT
		"Assets\\tiny_ship9.png"   // BOSS
	};

	hImage_ = LoadGraph( imagePath[type_].c_str() ); // �G�̉摜��ǂݍ���
	if (hImage_ == -1) {
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
	x_ = ENEMY_INIT_X; // �������W
	y_ = ENEMY_INIT_Y; // �������W
	AddGameObject(this); // �G�I�u�W�F�N�g���Q�[���I�u�W�F�N�g�̃x�N�^�[�ɒǉ�
}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // �摜�̃n���h�������
	}
}

void Enemy::Update()
{
	if (moveID_ == 0)
	{
		x_ += oddspeed_;
	}
	if (moveID_ == 1)
	{
		x_ += evenspeed_;
	}

	Timer_ -= GetDeltaTime();
	if(Timer_ <= 0)
	{
		if (moveID_ == 0)
		{
			oddspeed_ = -oddspeed_;
		}
		if (moveID_ == 1)
		{
			evenspeed_ = -evenspeed_;
		}
		Timer_ = ENEMY_TIMER;
		y_ += 5.0f;
	}
}

void Enemy::Draw()
{
	//��ʂ̍���ɓG�摜��\��
	if (isAlive_)
	{
		DrawExtendGraphF(x_, y_, x_ + ENEMY_IMAGE_WIDTH,
			y_ + ENEMY_IMAGE_HEIGHT,
			hImage_, TRUE);
	}
}

Rect Enemy::GetRect() const
{
	return { x_, y_, ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT };
}
