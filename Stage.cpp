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
	const int ENEMY_X_OFFSET = 100; // 敵の座標の調整用
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
	AddGameObject(this); // ステージオブジェクトをゲームオブジェクトのベクターに追加
	player_ = new Player(); // プレイヤーオブジェクトの生成
	enemy_ = std::vector<Enemy*>(ENEMY_NUM); // 敵オブジェクトの生成
	for (int i = 0; i < ENEMY_NUM; i++) {
		int col = i % ENEMY_COL_SIZE; // 列
		int row = i / ENEMY_COL_SIZE; // 行
		ETYPE enemyType[ENEMY_ROW_SIZE] = { BOSS, KNIGHT, MID, ZAKO, ZAKO, ZAKO, ZAKO }; // 敵の種類
		enemy_[i] = new Enemy(i, enemyType[row]); // 敵オブジェクトの生成

		enemy_[i]->SetPos(col * 55.0f + ENEMY_X_OFFSET, row * 50.0f); // 敵の初期位置を設定

	}
	hBackground = LoadGraph("Assets/sbg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	// ここに当たり判定
	std::vector<Bullet*>bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		for(auto& b : bullets)
		{
			// 発射されていない状態だったら抜けだす
			if (b->IsFired() && e->IsAlive())
			{
				// 当たり判定
				if (IntersectRect(e->GetRect(), b->GetRect()))
				{
					// 弾が発射されていたら描画されるため
					// 発射されていない状態にする
					// 敵も同様で敵も生きていない状態にすることで描画されない
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
