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
	float dx, dy, length; // 敵の弾のベクトル
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
	void SetFired(bool fired) { isFired_ = fired; } // 発射状態を設定
	bool IsFired() const { return isFired_; } // 発射状態を取得
	Rect GetRect() const { return { pos_.x, pos_.y, imageSize_.x, imageSize_.y }; } // 弾のサイズを取得
};