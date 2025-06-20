#include "StartScene.h"
#include "DxLib.h"
#include "globals.h"

StartScene::StartScene()
{
	bImage_ = LoadGraph("Assets/2Dshoot.png");
	hBackground = LoadGraph("Assets/sbg.png");
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{

}

void StartScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackground, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(500, 500, "Push K", GetColor(255,255,255));
	DrawExtendGraph(212, 200, 812, 350, bImage_, TRUE);
}
