#include "Hako.h"
#include "DxLib.h"


Hako::Hako() : animation_count(0), velocity(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;

	for (int i = 0; i < 4; i++)
	{
		Bullet[i] = NULL;
	}
}

Hako::~Hako()
{

}

//����������
void Hako::Initialize()
{
	//�摜�̓ǂݍ���
	//�n�R�e�L�̉摜
	animation[0] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki2.png");

	Bullet[0] = LoadGraph("Resource/Images/teki/hakoteki/Bullet1.png");
	Bullet[1] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff1.png");
	Bullet[2] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff2.png");
	Bullet[3] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 2; i++)
	{
		if (animation[i] == -1)
		{
			throw ("�n�R�e�L�̉摜������܂���\n");
		}
	}

	for (int j = 0; j < 4; j++)
	{
		if (Bullet[j] == -1)
		{
			throw ("�o���b�g�̉摜������܂���\n");
		}
	}

	//�G�̃^�C�v�ݒ�
	object_type = HAKO;

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 40.0f;

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

}

void Hako::Update()
{
	Movement();

	AnimationControl();

	if (Hit == TRUE)
	{
		scale = 0.0f;

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

void Hako::Draw() const
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

	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Hako::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Hako::OnHitCollision(GameObject* hit_object)
{
	Hit = TRUE;
	velocity = 0.0f;
}

void Hako::Movement()
{
	location.x += velocity.x;
}

void Hako::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 40)
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

	//Hit�������̃A�j���[�V����
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

