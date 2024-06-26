#include "Hako.h"
#include "DxLib.h"


Hako::Hako() : animation_count(0), velocity(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
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

	

	//�G���[�`�F�b�N
	for (int i = 0; i < 2; i++)
	{
		if (animation[i] == -1)
		{
			throw ("�n�R�e�L�̉摜������܂���\n");
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

	//�`�悷��G�̌���
	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	Score_Point = 200;
}

//�X�V����
void Hako::Update()
{
	Movement();

	AnimationControl();

	//Bom�ɓ����������ɓ��߂�����ׂ̒l�ύX����
	if (Hit == TRUE)
	{
		scale = 0.0f;

		count++;
		if (count >= 10)
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
void Hako::Draw() const
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

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

//�I������
void Hako::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Hako::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOM)
	{
		Hit = TRUE;
	velocity = 0.0f;
	}
	
}

//�ړ�����
void Hako::Movement()
{
	location.x += velocity.x;
}

//�A�j���[�V��������
void Hako::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 30)
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

