#include "Enemy.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"

Enemy::Enemy() : animation_count(0), velocity(0.0f),alpha(255),count(0), flip_flag(0)
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
	//�n�l�e�L�̉摜
	animation[0] = LoadGraph("Resource/Images/teki/haneteki/haneteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/haneteki/haneteki2.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (animation[i] == -1)
			{
				throw ("�n�l�e�L�̉摜������܂���\n");
			}
	}
	
	//�G�̃^�C�v�ݒ�
	object_type = HANE;

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 50.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�X�s�[�h�ݒ菈��
	Plus_Speed[0] = Vector2D(2.0f, 0.5f);
	Plus_Speed[1] = Vector2D(1.4f, 0.5f);
	Plus_Speed[2] = Vector2D(0.8f, 0.5f);
	Minus_Speed[0] = Vector2D(-2.0f, 0.5f);
	Minus_Speed[1] = Vector2D(-1.4f, 0.5f);
	Minus_Speed[2] = Vector2D(-0.8f, 0.5f);

	//�i�s�����̐ݒ�
	if (location.x <= 0)
	{
		velocity = Vector2D(Plus_Speed[GetRand(2)]);
	}
	else if (location.x >= 640)
	{
		velocity = Vector2D(Minus_Speed[GetRand(2)]);
	}

	//�`�悷��G�̌���
	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}
}

//�X�V����
void Enemy::Update()
{
	Movement();

	AnimationControl();

	//Bom�ɓ����������ɓ��߂�����ׂ̒l�ύX����
	if (Hit == TRUE)
	{
		count++;
		if (count >= 30)
		{
			alpha -= 51;
			count = 0;
		}

	}
	if (alpha < 0)
	{
		delete_object = 1;
	}
}

//�`�揈��
void Enemy::Draw() const
{
	//Bom�ɓ����������̕`�揈��
	if (Hit == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
	}


	__super::Draw();

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

//�I������
void Enemy::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOM)
	{
		Hit = TRUE;
		velocity = 0.0f;
	}
}

//�ړ�����
void Enemy::Movement()
{
	location.x += velocity.x;

}

//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 30 && Hit != TRUE)
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

	//Bom�ɓ����������̃A�j���[�V����
	if (Hit == TRUE)
	{
		if (animation_count == 15 || animation_count == 45)
		{
			location.x += 4;
			location.y += 0.5;
		}

		if (animation_count == 30 || animation_count == 60)
		{
			location.x += -4;
			location.y += 0.5;
			animation_count = 0;
		}
	}
	
}

