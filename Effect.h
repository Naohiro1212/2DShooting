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
	// �G�ƒe���Ԃ������ꏊ�ɔ������Ă��ĂR�b�ŏ�����
	float animTimer_;
	// 9���̃A�j���[�V�������X�V�����
	float frameTimer_;
	// �t���[���ԍ�
	int frame_;
	float x_, y_;
	std::vector<int> hImage_;
};