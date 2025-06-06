#include "Effect.h"
#include "DxLib.h"
#include "globals.h"
#include <assert.h>
#include <string>

namespace
{
	// 爆発のアニメーション数
	const int MAX_FRAME = 9;
	const int DIV_NUM = 3;
	const std::string EIMG_PATH = "Assets\\explosion.png";
	const float ANIME_TIME = {0.5f};
	const int ANIMATION_SIZE = 48;
	const float FRAME_TIME = ANIME_TIME / MAX_FRAME;
}

Effect::Effect(Point _pos) : GameObject(), x_(_pos.x), y_(_pos.y), 
animTimer_(ANIME_TIME), 
hImage_(std::vector<int>(MAX_FRAME, -1)), 
frameTimer_(FRAME_TIME),frame_(0)
{
	LoadDivGraph(EIMG_PATH.c_str(), MAX_FRAME, DIV_NUM, DIV_NUM,
		ANIMATION_SIZE, ANIMATION_SIZE, hImage_.data());
	AddGameObject(this);
}

Effect::~Effect()
{
	for (auto& itr : hImage_)
	{
		DeleteGraph(itr);
	}
	hImage_.clear();
}

void Effect::Update()
{
	float dt = GetDeltaTime();
	animTimer_ = animTimer_ - dt;
	if (animTimer_ < 0)
	{
		this->isAlive_ = false;
	}

	frameTimer_ = frameTimer_ - dt;
	if (frameTimer_ < 0)
	{
		frame_++;
		frameTimer_ = FRAME_TIME - frameTimer_; // リセット
	}
}

void Effect::Draw()
{
	if (isAlive_)
	{
		DrawExtendGraph(x_, y_, x_ + ANIMATION_SIZE, y_ + ANIMATION_SIZE,
			hImage_[frame_], TRUE);
	}
}

void Effect::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
