#pragma once
#include "GameObject.h"
#include "globals.h"
#include "Player.h"

class EnemyBeam : public GameObject
{
private:
	int hImage_; // �e�̉摜�n���h��
	Point pos_; // �e�̈ʒu
	float speed_; // �e�̈ړ����x
	Point imageSize_; // �e�̕\���T�C�Y
	bool isFired_; // ���˂���Ă��邩�ǂ���
	float pX_, pY_;
	float vX_, vY_;
	float dX_, dY_;
	float length_;
	float angle_;
	Player* player_; // ���@�i�ʒu���擾���邽�߂̂��́j
	
	// ����ς�e���ǂ����s��

protected:

public:
	EnemyBeam();
	EnemyBeam(float x, float y, float pX, float pY);
	EnemyBeam(Point pos_, float pX, float pY);
	~EnemyBeam();
	void Update() override;
	void Draw() override;

	bool IsOutOfScreen();
	void SetTarget(float pX, float pY);
	void SetPos(float x, float y) { pos_.x = x; pos_.y = y;	}
	void SetPos(const Point& pos) { pos_ = pos; }
	void SetFired(bool fired) { isFired_ = fired; } // ���ˏ�Ԃ�ݒ�
	bool IsFired() const { return isFired_; } // ���ˏ�Ԃ��擾
	Rect GetRect() const { return { pos_.x, pos_.y, imageSize_.x - 10, imageSize_.y - 10 }; } // �e�̃T�C�Y���擾
};