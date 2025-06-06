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
	const int ENEMY_X_OFFSET = 100; // �G�̍��W�̒����p
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
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // ��
		int row = i / ENEMY_COL_SIZE; // �s
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // �G�̎��
		enemy_[i] = new Enemy(i, enemyType[row]); // �G�I�u�W�F�N�g�̐���

		enemy_[i]->SetPos(col * 55.0f + ENEMY_X_OFFSET, row * 50.0f); // �G�̏����ʒu��ݒ�

	}
	hBackground = LoadGraph("Assets/sbg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	// �����ɓ����蔻��
	std::vector<Bullet*>bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for(auto& b : bullets)
		{
			// ���˂���Ă��Ȃ���Ԃ������甲������
			if (b->IsFired() && e->IsAlive())
			{
				// �����蔻��
				if (IntersectRect(e->GetRect(), b->GetRect()))
				{
					// �e�����˂���Ă�����`�悳��邽��
					// ���˂���Ă��Ȃ���Ԃɂ���
					// �G�����l�œG�������Ă��Ȃ���Ԃɂ��邱�Ƃŕ`�悳��Ȃ�
					b->SetFired(false);
					e->SetAlive(false);
				}
			}
		}
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
