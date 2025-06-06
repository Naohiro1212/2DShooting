#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>

class Effect : public GameObject
{
public:
	Effect(Point _pos);
	~Effect();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y);

private:
	// 敵と弾がぶつかった場所に発生していて３秒で消える
	float animTimer_;
	// 9枚のアニメーションが更新される
	float frameTimer_;
	// フレーム番号
	int frame_;
	float x_, y_;
	std::vector<int> hImage_;
};