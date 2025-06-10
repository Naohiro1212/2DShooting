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
	int hImage_;  //�G�̉摜�n���h��
	float x_, y_; //�G�̍��W
	float oddspeed_; //��s�G�̈ړ����x
	float evenspeed_; // �����s�G�̈ړ����x
	float cenx_;  // ���������L�����Ă�������

	int moveID_; // ��񂪍��A�����񂪉E�ɓ���
	int ID_; //�G��ID
	ETYPE type_; //�G�̎��
public:
	Enemy(int id, ETYPE type, int moveID);
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void SetPos(float x, float y) { x_ = x; y_ = y; } //�G�̍��W��ݒ�
	Rect GetRect() const;// �e�̋�`���擾
};