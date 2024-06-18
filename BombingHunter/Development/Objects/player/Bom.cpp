#include "Bom.h"
#include "../../Utility/InputControl.h"
#include "Player.h"
#include "DxLib.h"

Bom::Bom() : animation_count(0), count(0), Bomcount(0), bom_image()
{
	
}

Bom::~Bom()
{

}

void Bom::Initialize()
{
	image = LoadGraph("Resource/Images/bom/bom.png");


		if (image == -1)
			{
				throw("���e�̉摜������܂���\n");
			}

	
	object_type = Bomb;

	//�����̐ݒ�
	radian = DX_PI_F/2;

	//�����蔻��̑傫����ݒ�
	scale = 54.0f;

	velocity = Vector2D(0.0f, 3.0f);
}

void Bom::Update()
{
	Movement();
}

void Bom::Draw() const
{
	
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE);

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

void Bom::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(image);
}

void Bom::OnHitCollision(GameObject* hit_object)
{
	delete_object = 1;
	/*Animation();*/
	/*velocity.y = 0.0f;*/

	/*animation_count++;*/

	////�摜�̐؂�ւ�
	//if (animation_count >= 30)
	//{
	//	if (count > 4)
	//	{
	//		delete_object = 1;
	//	}
	//	//�J�E���g�̃��Z�b�g
	//	animation_count = 0;

	//	if (count < 4)
	//	{
	//		image = bom_image[count];
	//		count++;
	//	}	
	//}
		

}

void Bom::Movement()
{
	if (location.y < 445)
	{
		location.y += velocity.y;
	}	
	else
	{
		velocity = 0.0f;
		/*Animation();*/
	}

}

//void Bom::Animation()
//{
//	animation_count++;
//
//	//�摜�̐؂�ւ�
//	if (animation_count >= 30)
//	{
//		if (count > 4)
//		{
//			delete_object = 1;
//		}
//		//�J�E���g�̃��Z�b�g
//		animation_count = 0;
//
//		if (count < 4)
//		{
//			image = bom_image[count];
//			count++;
//		}
//
//	}
//}

Vector2D Bom::SetLocation()
{
	return location;
}