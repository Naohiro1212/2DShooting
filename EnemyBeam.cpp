#include "EnemyBeam.h"
#include "dxLib.h"
#include "string"
#include <assert.h>

namespace
{
	const int ENEMYBEAM_IMAGE_WIDTH = 16; // 弾の画像の幅;
	const int ENEMYBEAM_IMAGE_HEIGHT = 48; // 弾の画像の高さ;
	const float BULLET_INIT_SPEED = 300.0f; // 弾の初期移動速度;
	const std::string BULLET_IMAGE_PATH = "Assets\\ebeams.png";
}

EnemyBeam::EnemyBeam()
	:GameObject(), hImage_(-1),
	pos_({ -10,-10 }), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }), pX_(0), pY_(0),
	angle_(0)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);
}

EnemyBeam::EnemyBeam(float x, float y, float pX, float pY)
	:GameObject(), hImage_(-1),
	pos_({ x, y }), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }),
	pX_(pX), pY_(pY)
{
	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);

	assert(pX != 0);
	assert(pY != 0);
	dX_ = pX_ - pos_.x;
	dY_ = pY_ - pos_.y;
	length_ = sqrt(dX_ * dX_ + dY_ * dY_);
	vX_ = dX_ / length_ * speed_;
	vY_ = dY_ / length_ * speed_;
}

EnemyBeam::EnemyBeam(Point pos_, float pX, float pY)
	:GameObject(), hImage_(-1),
	pos_(pos_), speed_(0), isFired_(true),
	imageSize_({ ENEMYBEAM_IMAGE_WIDTH, ENEMYBEAM_IMAGE_HEIGHT }),
	pX_(pX), pY_(pY)
{

	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;
	AddGameObject(this);

	assert(pX != 0);
	assert(pY != 0);
	dX_ = pX_ - pos_.x;
	dY_ = pY_ - pos_.y;
	length_ = sqrt(dX_ * dX_ + dY_ * dY_);
	vX_ = dX_ / length_ * speed_;
	vY_ = dY_ / length_ * speed_;
}

EnemyBeam::~EnemyBeam()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // 画像の開放
	}
	hImage_ = -1; // 画像ハンドルを無効化
}

void EnemyBeam::Update()
{
	float dt = GetDeltaTime();
	angle_ = atan2(dY_, dX_);

	pos_.x += vX_ * dt;
	pos_.y += vY_ * dt;
	if (pos_.y >= WIN_HEIGHT)
	{
		isFired_ = false;
	}
	
}

void EnemyBeam::Draw()
{
	// 発射されていたら描画
	if (isFired_)
	{
		//DrawExtendGraph(pos_.x, pos_.y, 
		//	pos_.x + imageSize_.x, pos_.y + imageSize_.y, 
		//	hImage_, TRUE); // 描画 
		DrawRotaGraph(pos_.x, pos_.y, 1.0, angle_ - DX_PI / 2, hImage_, TRUE);
	}
}

bool EnemyBeam::IsOutOfScreen()
{
	if (pos_.y >= WIN_HEIGHT || pos_.x <= 0 || pos_.x >= WIN_WIDTH || pos_.y <= 0)
	{
		return true;
	}
	return false;
}

void EnemyBeam::SetTarget(float pX, float pY)
{
	pX_ = pX;
	pY_ = pY;
	dX_ = pX_ - pos_.x;
	dY_ = pY_ - pos_.y;
	length_ = sqrt(dX_ * dX_ + dY_ * dY_);
	vX_ = dX_ / length_ * speed_;
	vY_ = dY_ / length_ * speed_;
}