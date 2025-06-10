#include "StartScene.h"
#include "DxLib.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{

}

void StartScene::Draw()
{
	DrawString(100, 100, "PlayScene", GetColor(255, 255, 255));
	DrawString(500, 500, "Push K", GetColor(255,255,255));
}
