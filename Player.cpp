#include "Player.h"
#include "DxLib.h"
#include "globals.h"
#include "Input.h"
#include "Bullet.h"



namespace
{
	const float PLAYER_INIT_SPEED = 200.0f; // �v���C���[�̏����ړ����x;
	const int PLAYER_IMAGE_WIDTH = 48; // �v���C���[�̉摜�̕�;
	const int PLAYER_IMAGE_HEIGHT = 48; // �v���C���[�̉摜�̍���;
	const int PLAYER_BASE_MARGIN = 32; // �v���C���[�̊�}�[�W��;

	const float PLAYER_INIT_X = WIN_WIDTH/2 - PLAYER_IMAGE_WIDTH/2; // �v���C���[�̏���X���W;
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT - PLAYER_BASE_MARGIN; // �v���C���[�̏���Y���W;
	const int BULLET_IMAGE_MARGIN = 17; // �e�̉摜�̃}�[�W��;
	const float BULLET_INTERVAL = 0.2f; // �e�̔��ˊԊu;
	const int PLAYER_BULLET_NUM = 11; // �v���C���[�������ɔ��˂ł���e�̐�;
}

Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), imageSize_({ PLAYER_IMAGE_WIDTH, PLAYER_IMAGE_HEIGHT })
{
	hImage_ = LoadGraph("Assets\\tiny_ship5.png"); // �v���C���[�̉摜��ǂݍ���
	if (hImage_ == -1) {
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�n���h�����O
		// �G���[��Ԃ��ăQ�[���I��
	}
	x_ = PLAYER_INIT_X; // �������W
	y_ = PLAYER_INIT_Y; // �������W
	speed_ = PLAYER_INIT_SPEED; // �ړ����x
	for (int i = 0;i < PLAYER_BULLET_NUM;i++)
	{
		bullets_.push_back(new Bullet()); // �e�̃x�N�^�[��������
	}

	isAlive_ = true;
	AddGameObject(this); // �v���C���[�I�u�W�F�N�g���Q�[���I�u�W�F�N�g�̃x�N�^�[�ɒǉ�
}

Player::~Player()
{
	//��ʃT�C�Y������i���Ƃŏ����I�j
}

void Player::Update()
{
	Point nextP = { x_, y_ };
	float dt = GetDeltaTime(); // �t���[���Ԃ̎��ԍ����擾
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT)) {
		nextP.x = x_ - speed_ * dt; // ���Ɉړ�
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT)) {
		nextP.x = x_ + speed_ * dt; // �E�Ɉړ�
	}

	if (nextP.x >= 0 && nextP.x <= WIN_WIDTH - PLAYER_IMAGE_WIDTH)
	{
		x_ = nextP.x;
		y_ = nextP.y;
	}

	static float bulletTimer = BULLET_INTERVAL; // �e�̔��˃^�C�}�[

	if (bulletTimer > 0.0f) {
		bulletTimer -= dt; // �^�C�}�[������
	}

	if (Input::IsKeepKeyDown(KEY_INPUT_SPACE)) {
		if (bulletTimer <= 0.0f) {
			Shoot(); // �e�𔭎�
			//new Bullet(x_ + BULLET_IMAGE_MARGIN, y_); // �e�̔���
			bulletTimer = BULLET_INTERVAL; // �e�̔��ˊԊu�����Z�b�g
		}
	}
}

void Player::Draw()
{
	if (isAlive_ == true)
	{
		DrawExtendGraphF(x_, y_, x_ + PLAYER_IMAGE_WIDTH, y_ + PLAYER_IMAGE_HEIGHT,
			hImage_, TRUE);
	}
	// �v���C���[�̉摜��`��(�摜�̌��_�͍���)
}
//�e�����֐�
void Player::Shoot()
{
	//for (auto& itr: bullets_)
	//{
	//	if (itr->IsFired() == false) // ���˂���Ă��Ȃ��e��T��
	//	{
	//		itr->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // �e�̈ʒu��ݒ�
	//		itr->SetFired(true); // ���ˏ�Ԃɂ���
	//		break; // ����˂����烋�[�v�𔲂���
	//	}
	//}

	Bullet* blt = GetActiveBullet();
	if (blt != nullptr) {
		blt->SetPos(x_ + BULLET_IMAGE_MARGIN, y_); // �e�̈ʒu��ݒ�
		blt->SetFired(true); // ���ˏ�Ԃɂ���
	}
}

Rect Player::GetRect() const
{
	// ���̂܂܂��Ɠ����蔻�肪�ł������邽�߁A�������߂ėP�\����������
	return { x_, y_, PLAYER_IMAGE_WIDTH - 10, PLAYER_IMAGE_HEIGHT - 10 };
}

void Player::playerPosition(float& x, float& y)
{
	x = x_;
	y = y_;
}

Bullet* Player::GetActiveBullet()
{
	for (auto& itr : bullets_)
	{
		if (!itr->IsFired())
		{
			return itr; // ���˂���Ă��Ȃ��e��Ԃ�
		}
	}
	return nullptr;
}
