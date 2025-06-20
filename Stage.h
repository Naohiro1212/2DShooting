#pragma once
#include "GameObject.h"
#include <vector>

class Player; // �O���錾
class Enemy; // �O���錾
class EnemyBeam; // �O���錾

class Stage :
    public GameObject
{
private:
	Player* player_; // �v���C���[�I�u�W�F�N�g
	std::vector<Enemy *> enemy_; // �G�I�u�W�F�N�g
	std::vector<EnemyBeam*> ebs_; // �G�̒e�I�u�W�F�N�g
	std::vector<Enemy *> aliveenemys; // �������Ă���G�I�u�W�F�N�g
	int hBackground;
	float pX_, pY_; // �v���C���[�̈ʒu���擾�i�G�̒e�ɓn�����߁j
	bool isClear_; // �G��S���|������
	int aliveEnemyNum_;

public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	bool IsClear() { return isClear_; }
};

