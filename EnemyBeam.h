#pragma once
#include "GameObject.h"
#include "globals.h"
#include "Player.h"

class EnemyBeam : public GameObject
{
private:
	int hImage_; // 弾の画像ハンドル
	Point pos_; // 弾の位置
	float speed_; // 弾の移動速度
	Point imageSize_; // 弾の表示サイズ
	bool isFired_; // 発射されているかどうか
	float pX_, pY_;
	float vX_, vY_;
	float dX_, dY_;
	float length_;
	float angle_;
	Player* player_; // 自機（位置を取得するためのもの）
	
	// やっぱり弾がどっか行く

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
	void SetFired(bool fired) { isFired_ = fired; } // 発射状態を設定
	bool IsFired() const { return isFired_; } // 発射状態を取得
	Rect GetRect() const { return { pos_.x, pos_.y, imageSize_.x - 10, imageSize_.y - 10 }; } // 弾のサイズを取得
};