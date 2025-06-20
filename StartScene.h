#pragma once
#include "GameObject.h"

class StartScene : GameObject
{
private:
	int bImage_;
	int hBackground;
public:
	StartScene();
	~StartScene();
	void Update() override;
	void Draw() override;
};