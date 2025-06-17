#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "DxLib.h"

namespace
{
	const int ENEMY_NUM = 10 * 7; // 敵の数
	const int ENEMY_COL_SIZE = 10; // 敵の列数
	const int ENEMY_ROW_SIZE = 7; // 敵の行数
	const int ENEMY_X_OFFSET = 270; // 敵の座標の調整用
	const int ENEMY_BULLET_NUM = 4;
	bool IntersectRect(const Rect& a, const Rect& b)
	{
		bool overlapX = (a.x + a.width > b.x) && (b.x + b.width > a.x);
		bool overlapY = (a.y + a.height > b.y) && (b.y + b.height > a.y);
		return overlapX && overlapY;
	}
}

Stage::Stage()
	:GameObject(), player_(nullptr),hBackground(-1), isClear_(false)
{
	AddGameObject(this); // ステージオブジェクトをゲームオブジェクトのベクターに追加
	player_ = new Player(); // プレイヤーオブジェクトの生成
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // 敵オブジェクトの生成
	ebs_ = std::vector<EnemyBeam*>(ENEMY_BULLET_NUM); // 敵の弾オブジェクトの生成
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // 列
		int row = i / ENEMY_COL_SIZE; // 行
		int oddeven = i % 2; // moveID_が0か1か
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // 敵の種類
		enemy_[i] = new Enemy(i, enemyType[row],oddeven); // 敵オブジェクトの生成

		enemy_[i]->SetPos(col * 55.0f + ENEMY_X_OFFSET, row * 50.0f); // 敵の初期位置を設定

	}
	hBackground = LoadGraph("Assets/sbg.png");

	player_->playerPosition(pX_, pY_);

	for (int i = 0; i < ENEMY_BULLET_NUM; i++)
	{
		ebs_[i] = new EnemyBeam(enemy_[i]->GetX(), enemy_[i]->GetY(), pX_, pY_);
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	aliveenemys.clear();

	//ここに当たり判定
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

	for (auto& ebs : ebs_)
	{
		if (ebs->IsFired() && player_->IsAlive())
		{
			if (IntersectRect(ebs->GetRect(), player_->GetRect()))
			{
				if (ebs->IsFired())
				{
					ebs->SetAlive(false);
				}
				if (player_->IsAlive())
				{
					player_->SetAlive(false);
				}
			}
		}
	}

	for (auto& e : enemy_)
	{
		if (e->IsAlive())
		{
			aliveenemys.push_back(e);
		}
	}

	// 常にプレイヤーの座標を取得しておき、画面外に出たときに敵弾のターゲットを更新する
	player_->playerPosition(pX_, pY_);

	static size_t targetEnemyIndex = 0;
	static size_t aliveCount_ = aliveenemys.size();
	if (aliveCount_ > 0)
	{
		for (auto& ebs : ebs_)
		{
			if (ebs->IsOutOfScreen() && !aliveenemys.empty())
			{
				// 現在のインデックスの敵座標を取得
				size_t index = targetEnemyIndex % aliveCount_;
				ebs->SetPos(aliveenemys[index]->GetX(),
					aliveenemys[index]->GetY());
				ebs->SetTarget(pX_, pY_);
				ebs->SetFired(true);
				targetEnemyIndex++;
			}
		}
	}

	if (aliveenemys.size() == 0)
	{
		isClear_ = true;
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}