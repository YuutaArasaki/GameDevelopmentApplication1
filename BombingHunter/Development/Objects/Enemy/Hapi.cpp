#include "DxLib.h"
#include "Hapi.h"

Hapi::Hapi() : animation_count(0), velocity(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Hapi::~Hapi()
{

}

void Hapi::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/teki/ha-pi-/ha-pi-1.png");
	animation[1] = LoadGraph("Resource/Images/teki/ha-pi-/ha-pi-2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("�n�[�s�[�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�i�s�����̐ݒ�
	velocity = Vector2D(1.0f, -0.5f);
}

void Hapi::Update()
{
	Movement();

	AnimationControl();
}

void Hapi::Draw() const
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
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);

	__super::Draw();

	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}


void Hapi::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Hapi::OnHitCollision(GameObject* hit_object)
{
	velocity = 0.0f;
}

void Hapi::Movement()
{
	if (((location.x + velocity.x) < scale.x) || (640.0f - scale.x) < (location.x + velocity.x))
	{
		velocity *= -1.0f;
	}

	location.x += velocity.x;
}


void Hapi::AnimationControl()
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



