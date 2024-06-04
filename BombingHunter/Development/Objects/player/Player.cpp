#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Player::Player() : animation_count(0), filp_flag(FALSE), boomimage()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Tri_pilot1.png");
	animation[1] = LoadGraph("Resource/Images/Tri_pilot2.png");
	boomimage = LoadGraph("Resource/Images/bom/bom.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || boomimage == -1)
	{
		throw("�g���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Player::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);

	//�f�o�b�N�p
	#if _DEBUG
		//�����蔻��̉���
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale/ 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
{
	
}

//�ړ�����
void Player::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y += -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 1.0f;
		filp_flag = FALSE;
	}
	
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Player::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}

Vector2D Player::GetLocation()
{
	return location;
}

//void Player::PlayerBoom()
//{
//	int Boomlocation = location.y;
//
//	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
//	{
//		DrawFormatString(320, 240, GetColor(255, 255, 255), "�{���̍��W%d\n", Boomlocation, TRUE);
//		DrawRotaGraph(location.x, Boomlocation, 1.0, radian, boomimage, TRUE, filp_flag);
//	}
//
//	Boomlocation += -1.0f;
//
//}