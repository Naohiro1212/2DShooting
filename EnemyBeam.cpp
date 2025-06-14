#include "EnemyBeam.h"
#include "DxLib.h"
#include "string"

namespace
{
	const int ENEMYBEAM_IMAGE_WIDTH = 16; // ’e‚Ì‰æ‘œ‚Ì•;
	const int ENEMYBEAM_IMAGE_HEIGHT = 48; // ’e‚Ì‰æ‘œ‚Ì‚‚³;
	const float BULLET_INIT_SPEED = 200.0f; // ’e‚Ì‰ŠúˆÚ“®‘¬“x;
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
	pos_({ x, y }), speed_(0), isFired_(true),
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
		DeleteGraph(hImage_); // ‰æ‘œ‚ÌŠJ•ú
	}
	hImage_ = -1; // ‰æ‘œƒnƒ“ƒhƒ‹‚ð–³Œø‰»
}

void EnemyBeam::Update()
{
	float dt = GetDeltaTime();

	pos_.y += speed_ * dt;
	if (pos_.y >= WIN_HEIGHT)
	{
		isFired_ = false;
	}
}

void EnemyBeam::Draw()
{
	// ”­ŽË‚³‚ê‚Ä‚¢‚½‚ç•`‰æ
	if (isFired_)
	{
		DrawExtendGraph(pos_.x, pos_.y, 
			pos_.x + imageSize_.x, pos_.y + imageSize_.y, 
			hImage_, TRUE); // •`‰æ 
	}
}

bool EnemyBeam::IsOutOfScreen()
{
	if (pos_.y >= WIN_HEIGHT)
	{
		return true;
	}
	return false;
}
