#pragma once
#include "GameObject.h"

class StartScene : GameObject
{
private:

public:
	StartScene();
	~StartScene();
	void Update() override;
	void Draw() override;
};