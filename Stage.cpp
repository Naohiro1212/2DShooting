#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "DxLib.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // �G�̐�
	const int ENEMY_COL_SIZE = 10; // �G�̗�
	const int ENEMY_ROW_SIZE = 7; // �G�̍s��
	const int ENEMY_X_OFFSET = 270; // �G�̍��W�̒����p
	const int ENEMY_BULLET_NUM = 10;
	bool IntersectRect(const Rect& a, const Rect& b)
	{
		bool overlapX = (a.x + a.width > b.x) && (b.x + b.width > a.x);
		bool overlapY = (a.y + a.height > b.y) && (b.y + b.height > a.y);
		return overlapX && overlapY;
	}
}

Stage::Stage()
	:GameObject(), player_(nullptr),hBackground(-1)
{
	AddGameObject(this); // �X�e�[�W�I�u�W�F�N�g���Q�[���I�u�W�F�N�g�̃x�N�^�[�ɒǉ�
	player_ = new Player(); // �v���C���[�I�u�W�F�N�g�̐���
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // �G�I�u�W�F�N�g�̐���
	ebs_ = std::vector<EnemyBeam*>(ENEMY_BULLET_NUM); // �G�̒e�I�u�W�F�N�g�̐���
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		int oddeven = i % 2; // moveID_��0��1��
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row],oddeven); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetPos(col * 55.0f + ENEMY_X_OFFSET, row * 50.0f); // �G�̏����ʒu��ݒ�

	}
	hBackground = LoadGraph("Assets/sbg.png");

	for (int i = 0; i < ENEMY_BULLET_NUM; i++)
	{
		ebs_[i] = new EnemyBeam(enemy_[i]->GetX(), enemy_[i]->GetY());
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	//�����ɓ����蔻��
	std::vector<Bullet*> bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for (auto& b : bullets)
		{
			if (b->IsFired() && e->IsAlive()) {
				if (IntersectRect(e->GetRect(), b->GetRect()))
				{
					if (b->IsFired())
						b->SetFired(false);
					if (e->IsAlive())
						e->SetAlive(false);
				}
			}
		}
	}

	std::vector<Enemy*> aliveenemys;
	for (auto& e : enemy_)
	{
		if (e->IsAlive())
		{
			aliveenemys.push_back(e);
		}
	}

	for (auto& ebs : ebs_)
	{
		if (ebs->IsOutOfScreen())
		{
			// �Ⴆ�΁A�ŏ��̐����Ă���G�̍��W�ɍĐݒ肷��ꍇ
			if (!aliveenemys.empty())
			{
				ebs->SetPos(aliveenemys[0]->GetX(), aliveenemys[0]->GetY());
				ebs->SetFired(true);
			}
		}
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}