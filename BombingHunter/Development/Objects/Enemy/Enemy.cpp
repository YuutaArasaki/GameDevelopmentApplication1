#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/haneteki1.png");
	animation[1] = LoadGraph("Resource/Images/haneteki2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�n�l�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�i�s�����̐ݒ�
	progress = Vector2D(1.0f, -0.5f);

}
