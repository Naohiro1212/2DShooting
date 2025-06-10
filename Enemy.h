#pragma once
#include "GameObject.h"
#include "globals.h"

enum ETYPE 
{
	ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};

class Enemy :
	public GameObject
{
	int hImage_;  //“G‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	float x_, y_; //“G‚ÌÀ•W
	float speed_; //“G‚ÌˆÚ“®‘¬“x
	float cenx_;  // ’†‰›ü‚ğ‹L‰¯‚µ‚Ä‚¨‚­‚à‚Ì

	int ID_; //“G‚ÌID
	ETYPE type_; //“G‚Ìí—Ş
public:
	Enemy(int id, ETYPE type);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x; y_ = y; } //“G‚ÌÀ•W‚ğİ’è
	Rect GetRect() const;// ’e‚Ì‹éŒ`‚ğæ“¾
};