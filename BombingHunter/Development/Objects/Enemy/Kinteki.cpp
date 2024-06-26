#include "Kinteki.h"
#include "DxLib.h"

Kinteki::Kinteki() : animation_count(0), velocity(0.0f), animation_image_count()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Kinteki::~Kinteki()
{

}

void Kinteki::Initialize()
{
	//�摜�̓ǂݍ���
	//���̃e�L�̉摜
	animation[0] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki2.png");
	animation[2] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki3.png");
	animation[3] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki4.png");
	animation[4] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki5.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�n�[�s�[�̉摜������܂���\n");
	}

	//�G�̃^�C�v
	object_type = KIN;

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 30.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�i�s�����̐ݒ�
	if (location.x <= 0)
	{
		velocity = Vector2D(1.5f, 0.5f);
	}
	else if (location.x >= 640)
	{
		velocity = Vector2D(-1.5f, 0.5f);
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

	Score_Point = 1500;
}

//�X�V����
void Kinteki::Update()
{
	Movement();

	AnimationControl();

	//Bom�ɓ����������ɓ��߂�����ׂ̒l�ύX����
	if (Hit == TRUE)
	{
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
void Kinteki::Draw() const
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
void Kinteki::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//
void Kinteki::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOM)
	{
		Hit = TRUE;
		velocity = 0.0f;
	}
}

//�ړ�����
void Kinteki::Movement()
{
	location.x += velocity.x;
}

//�A�j���[�V��������
void Kinteki::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 40)
	{
		if (animation_image_count > 5)
		{
			animation_image_count = 0;
		}
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		for (animation_image_count; animation_image_count < 5;)
		{
			image = animation[animation_image_count];
			break;
		}
		animation_image_count++;
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