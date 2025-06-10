#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include "EnemyBeam.h"
#include "Effect.h"

namespace
{
	const int ENEMY_IMAGE_WIDTH = 48; // 敵の画像の幅;
	const int ENEMY_IMAGE_HEIGHT = 48; // 敵の画像の高さ;

	const float ENEMY_INIT_X = 100; // 敵の初期X座標;
	const float ENEMY_INIT_Y = 100; // 敵の初期Y座標;
	const float ENEMY_INIT_SPEED = 1.5f; // 敵の初期移動速度;

	const float ENEMY_CENTER_X = WIN_WIDTH / 2 - 120; // 敵の中央線
	const float ENEMY_MOVE_X = 200; // 敵の左右のブレ
}


Enemy::Enemy()
	:GameObject(), 
	 hImage_(-1), 
	 x_(0), y_(0), 
	 oddspeed_(0), evenspeed_(0), cenx_(0), moveID_(0)
{
	hImage_ = LoadGraph("Assets\\tiny_ship10.png"); // 敵の画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = ENEMY_INIT_X; // 初期座標
	y_ = ENEMY_INIT_Y; // 初期座標
	oddspeed_ = ENEMY_INIT_SPEED; // 移動速度
}

Enemy::Enemy(int id, ETYPE type, int moveID)
	:GameObject(),
	hImage_(-1),
	x_(ENEMY_INIT_X), y_(ENEMY_INIT_Y),
	oddspeed_(ENEMY_INIT_SPEED),evenspeed_(-ENEMY_INIT_SPEED),
	ID_(id), type_(type), cenx_(ENEMY_CENTER_X),moveID_(moveID)
{	
	//ETYPE::ZAKO =>  "Assets/tiny_ship10.png"
	//ETYPE::MID = > "Assets/tiny_ship18.png"
	//ETYPE::KNIGHT = > "Assets/tiny_ship16.png"
	//ETYPE::BOSS = > "Assets/tiny_ship9.png"
	// 画像の読み込み
	std::string imagePath[MAX_ETYPE] = {
		"Assets\\tiny_ship10.png", // ZAKO
		"Assets\\tiny_ship18.png", // MID
		"Assets\\tiny_ship16.png", // KNIGHT
		"Assets\\tiny_ship9.png"   // BOSS
	};

	hImage_ = LoadGraph( imagePath[type_].c_str() ); // 敵の画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = ENEMY_INIT_X; // 初期座標
	y_ = ENEMY_INIT_Y; // 初期座標
	AddGameObject(this); // 敵オブジェクトをゲームオブジェクトのベクターに追加
}

Enemy::~Enemy()
{
	new Effect({ x_, y_ });
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_); // 画像のハンドルを解放  
	}
}

void Enemy::Update()
{
	static float beamTimer = 3.0f; // 弾の発射タイマー

	if (moveID_ == 0)
	{
		x_ += oddspeed_;
	}
	else if (moveID_ == 1)
	{
		x_ += evenspeed_;
	}
	// 基準点最初に設定してそれ基準で動くようにする
	cenx_ += oddspeed_;
	if (cenx_ >= ENEMY_CENTER_X + ENEMY_MOVE_X || cenx_ <= ENEMY_CENTER_X)
	{
		if (moveID_ == 0)
		{
			oddspeed_ = -oddspeed_;
		}
		if (moveID_ == 1)
		{
			evenspeed_ = -evenspeed_;
		}
	}
	
	beamTimer -= GetDeltaTime();
	if (beamTimer < 0)
	{
		// 弾を発射
		new EnemyBeam(x_ + ENEMY_IMAGE_WIDTH / 2, y_ + ENEMY_IMAGE_HEIGHT);
		beamTimer = 3.0f;
	}

}

void Enemy::Draw()
{
	//画面の左上に敵画像を表示
	DrawExtendGraphF(x_, y_, x_ + ENEMY_IMAGE_WIDTH,
		y_ + ENEMY_IMAGE_HEIGHT,
		hImage_, TRUE);

	DrawFormatString(300, 300, GetColor(255,255,255), "%f", oddspeed_);
	DrawFormatString(500, 300, GetColor(255,255,255), "%f", evenspeed_);
}

Rect Enemy::GetRect() const
{
	return { x_, y_, ENEMY_IMAGE_WIDTH, ENEMY_IMAGE_HEIGHT };
}
