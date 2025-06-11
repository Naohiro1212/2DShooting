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
	float dx, dy, length; // �G�̒e�̃x�N�g��
	Player* pl;
	
protected:

public:
	EnemyBeam();
	EnemyBeam(float x, float y, Player* player);
	EnemyBeam(Point pos_, Player* player);
	~EnemyBeam();
	void Update() override;
	void Draw() override;

	void SetPos(float x, float y) { pos_.x = x; pos_.y = y;	}
	void SetPos(const Point& pos) { pos_ = pos; }
	void SetFired(bool fired) { isFired_ = fired; } // ���ˏ�Ԃ�ݒ�
	bool IsFired() const { return isFired_; } // ���ˏ�Ԃ��擾
	Rect GetRect() const { return { pos_.x, pos_.y, imageSize_.x, imageSize_.y }; } // �e�̃T�C�Y���擾
};