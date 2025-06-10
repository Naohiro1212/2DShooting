#pragma once
#include "GameObject.h"
#include "globals.h"

enum ETYPE 
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};

class Enemy :
	public GameObject
{
	int hImage_;  //敵の画像ハンドル
	float x_, y_; //敵の座標
	float oddspeed_; //奇数行敵の移動速度
	float evenspeed_; // 偶数行敵の移動速度
	float cenx_;  // 中央線を記憶しておくもの

	int moveID_; // 奇数列が左、偶数列が右に動く
	int ID_; //敵のID
	ETYPE type_; //敵の種類
public:
	Enemy(int id, ETYPE type, int moveID);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x; y_ = y; } //敵の座標を設定
	Rect GetRect() const;// 弾の矩形を取得
};