#include "Player.h"
#include "DxLib.h"
#include "globals.h"
#include "Input.h"
#include "Bullet.h"



namespace
{
	const float PLAYER_INIT_SPEED = 200.0f; // プレイヤーの初期移動速度;
	const int PLAYER_IMAGE_WIDTH = 48; // プレイヤーの画像の幅;
	const int PLAYER_IMAGE_HEIGHT = 48; // プレイヤーの画像の高さ;
	const int PLAYER_BASE_MARGIN = 32; // プレイヤーの基準マージン;

	const float PLAYER_INIT_X = WIN_WIDTH/2 - PLAYER_IMAGE_WIDTH/2; // プレイヤーの初期X座標;
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MARGIN; // プレイヤーの初期Y座標;
	const int BULLET_IMAGE_MARGIN = 17; // 弾の画像のマージン;
	const float BULLET_INTERVAL = 0.2f; // 弾の発射間隔;
	const int PLAYER_BULLET_NUM = 11; // プレイヤーが同時に発射できる弾の数;
}

Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), imageSize_({ PLAYER_IMAGE_WIDTH, PLAYER_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph("Assets\\tiny_ship5.png"); // プレイヤーの画像を読み込む
	if (hImage_ == -1) {
		// 画像の読み込みに失敗した場合のエラーハンドリング
		// エラーを返してゲーム終了
	}
	x_ = PLAYER_INIT_X; // 初期座標
	y_ = PLAYER_INIT_Y; // 初期座標
	speed_ = PLAYER_INIT_SPEED; // 移動速度
	for (int i = 0;i < PLAYER_BULLET_NUM;i++)
	{
		bullets_.push_back(new Bullet()); // 弾のベクターを初期化
	}

	isAlive_ = true;
	AddGameObject(this); // プレイヤーオブジェクトをゲームオブジェクトのベクターに追加
}

Player::~Player()
{
	//画面サイズを解放（あとで書く！）
}

void Player::Update()
{
	Point nextP = { x_, y_ };
	float dt = GetDeltaTime(); // フレーム間の時間差を取得
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT)) {
		nextP.x = x_ - speed_ * dt; // 左に移動
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) {
		nextP.x = x_ + speed_ * dt; // 右に移動
	}

	if (nextP.x >= 0 && nextP.x <= WIN_WIDTH - PLAYER_IMAGE_WIDTH)
	{
		x_ = nextP.x;
		y_ = nextP.y;
	}

	static float bulletTimer = BULLET_INTERVAL; // 弾の発射タイマー

	if (bulletTimer > 0.0f) {
		bulletTimer -= dt; // タイマーを減少
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_SPACE)) {
		if (bulletTimer <= 0.0f) {
			Shoot(); // 弾を発射
			//new Bullet(x_ + BULLET_IMAGE_MARGIN, y_); // 弾の発射
			bulletTimer = BULLET_INTERVAL; // 弾の発射間隔をリセット
		}
	}
}

void Player::Draw()
{
	if (isAlive_ == true)
	{
		DrawExtendGraphF(x_, y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT,
			hImage_, TRUE);
	}
	// プレイヤーの画像を描画(画像の原点は左上)
}
//弾を撃つ関数
void Player::Shoot()
{
	//for (auto& itr: bullets_)
	//{
	//	if (itr->IsFired() == false) // 発射されていない弾を探す
	//	{
	//		itr->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // 弾の位置を設定
	//		itr->SetFired(true); // 発射状態にする
	//		break; // 一つ発射したらループを抜ける
	//	}
	//}

	Bullet* blt = GetActiveBullet();
	if (blt != nullptr) {
		blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // 弾の位置を設定
		blt->SetFired(true); // 発射状態にする
	}
}

Rect Player::GetRect() const
{
	// そのままだと当たり判定がでかすぎるため、少し狭めて猶予を持たせる
	return { x_, y_, PLAYER_IMAGE_WIDTH - 10, PLAYER_IMAGE_HEIGHT - 10 };
}

void Player::playerPosition(float& x, float& y)
{
	x = x_;
	y = y_;
}

Bullet* Player::GetActiveBullet()
{
	for (auto& itr : bullets_)
	{
		if (!itr->IsFired())
		{
			return itr; // 発射されていない弾を返す
		}
	}
	return nullptr;
}
