#pragma once
#include "GameObject.h"

class EndScene : GameObject
{
private:
	int hBackground;
	int bImage_;
public:
	EndScene();
	~EndScene();
	void Update() override;
	void Draw() override;
};