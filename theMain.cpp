#include "DxLib.h"
#include "globals.h"
#include "input.h"
#include <vector>
#include "Stage.h"


namespace
{
	const int BGCOLOR[3] = {0, 0, 0}; // 背景色{ 255, 250, 205 }; // 背景色
	int crrTime;
	int prevTime;
}

std::vector<GameObject*> gameObjects; // ゲームオブジェクトのベクター
std::vector<GameObject*> newObjects; // ゲームオブジェクトのベクター


float gDeltaTime = 0.0f; // フレーム間の時間差

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();
	
	Stage* stage = new Stage(); // ステージオブジェクトの生成


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // キー入力の状態を更新

		crrTime = GetNowCount(); // 現在の時間を取得
		// 前回の時間との差分を計算
		float deltaTime = (crrTime - prevTime) / 1000.0f; // 秒単位に変換
		gDeltaTime = deltaTime; // グローバル変数に保存

		//ここにやりたい処理を書く(ここから）
		//ゲームオブジェクトの追加
		if (newObjects.size() > 0) {
			for (auto& obj : newObjects) {
				gameObjects.push_back(obj); // 新しいゲームオブジェクトを追加	
			}
			newObjects.clear(); // 新しいゲームオブジェクトのベクターをクリア
		}
		//gameObjectsの更新
		for (auto& obj : gameObjects) {
			obj->Update(); // ゲームオブジェクトの更新
		}
		//gameObjectsの描画
		for (auto& obj : gameObjects) {
			obj->Draw(); // ゲームオブジェクトの描画
		}
		
		for (auto it = gameObjects.begin(); it != gameObjects.end();) {
			if (!(*it)->IsAlive()) {
				delete* it; // ゲームオブジェクトを削除
				it = gameObjects.erase(it); // ベクターから削除
			}
			else {
				++it; // 次の要素へ
			}
		}
		//ここにやりたい処理を書く（ここまで）


		//裏画面の描画
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // 現在の時間を前回の時間として保存

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}