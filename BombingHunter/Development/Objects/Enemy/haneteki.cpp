#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), velocity(0.0f)
{
	for (int i = 0; i < 10; i++)
	{
		animation[i] = NULL;
	}

	for (int j = 0; j < 3; j++)
	{
		enemy_image[j] = 0;
	}
}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ���
	//�n�l�e�L�̉摜
	animation[0] = LoadGraph("Resource/Images/teki/haneteki/haneteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/haneteki/haneteki2.png");
	//�n�[�s�[�̉摜
	animation[2] = LoadGraph("Resource/Images/teki/ha-pi-/ha-pi-1.png");
	animation[3] = LoadGraph("Resource/Images/teki/ha-pi-/ha-pi-2.png");
	//�n�R�e�L�̉摜
	animation[4] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki1.png");
	animation[5] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki2.png");
	//���̃e�L�̉摜
	/*animation[6] = LoadGraph("Resource/Images/teki/haneteki/Ha-pi-1.png");
	animation[7] = LoadGraph("Resource/Images/teki/Hapi/Ha-pi-2.png");*/


	//�G���[�`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (animation[i] == -1)
			{
				throw ("�e�L�̉摜������܂���\n");
			}
	}
	

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	enemy_image[0] = animation[0];
	enemy_image[1] = animation[2];

	//�i�s�����̐ݒ�
	velocity = Vector2D(1.0f, -0.5f);

}

void Enemy::Update()
{
	Movement();

	AnimationControl();
}

void Enemy::Draw() const
{
	int flip_flag = TRUE;

	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}
	DrawRotaGraphF(location.x, location.y, 0.6, radian, enemy_image[0], TRUE, flip_flag);
	DrawRotaGraphF(location.x, location.y, 0.6, radian, enemy_image[1], TRUE, flip_flag);
	__super::Draw();
	
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Enemy::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	velocity = 0.0f;
}

void Enemy::Movement()
{
	if (((location.x + velocity.x) < scale.x)||(640.0f - scale.x)< (location.x + velocity.x))
	{
		velocity *= -1.0f;
	}

	location.x += velocity.x;
}

void Enemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (enemy_image[0] == animation[0])
		{
			enemy_image[0] = animation[1];
		}
		else
		{
			enemy_image[0] = animation[0];
		}
	}

}