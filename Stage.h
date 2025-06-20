#pragma once
#include "GameObject.h"
#include <vector>

class Player; // 前方宣言
class Enemy; // 前方宣言
class EnemyBeam; // 前方宣言

class Stage :
    public GameObject
{
private:
	Player* player_; // プレイヤーオブジェクト
	std::vector<Enemy *> enemy_; // 敵オブジェクト
	std::vector<EnemyBeam*> ebs_; // 敵の弾オブジェクト
	std::vector<Enemy *> aliveenemys; // 生存している敵オブジェクト
	int hBackground;
	float pX_, pY_; // プレイヤーの位置を取得（敵の弾に渡すため）
	bool isClear_; // 敵を全員倒したか
	int aliveEnemyNum_;

public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	bool IsClear() { return isClear_; }
};

