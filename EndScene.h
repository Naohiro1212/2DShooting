#pragma once
#include "GameObject.h"

class EndScene : GameObject
{
private:

public:
	EndScene();
	~EndScene();
	void Update() override;
	void Draw() override;
};