#include "EndScene.h"
#include "DxLib.h"
#include "globals.h"

EndScene::EndScene()
{
	hBackground = LoadGraph("Assets/sbg.png");
	bImage_ = LoadGraph("Assets/end.png");
}

EndScene::~EndScene()
{
}

void EndScene::Update()
{
}

void EndScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawExtendGraph(162, 200, 862, 500, bImage_, TRUE);
	DrawString(500, 500, "Push K", GetColor(255, 255, 255));
}
