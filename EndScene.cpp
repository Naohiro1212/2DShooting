#include "EndScene.h"
#include "DxLib.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::Update()
{
}

void EndScene::Draw()
{
	DrawString(100, 100, "EndScene", GetColor(255, 255, 255));
	DrawString(500, 500, "Push K", GetColor(255, 255, 255));
}
