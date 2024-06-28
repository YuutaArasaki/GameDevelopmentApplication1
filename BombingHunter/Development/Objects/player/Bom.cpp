#include "Bom.h"
#include "../../Utility/InputControl.h"
#include "Blast.h"
#include "Player.h"
#include "DxLib.h"

Bom::Bom() : animation_count(0), bom_image(),left(false),right(false)
{
	
}

Bom::~Bom()
{

}

void Bom::Initialize()
{
	//�{���̉摜�ǂݍ���
	image = LoadGraph("Resource/Images/bom/bom.png");

	//SE�ǂݍ���
	SE = LoadSoundMem("Resource/Sound/SE/pan.wav");
	

	PlaySoundMem(SE, DX_PLAYTYPE_BACK, TRUE);

	if (image == -1)
	{
		throw("���e�̉摜������܂���\n");
	}

	
	object_type = BOM;

	//�����̐ݒ�
	radian = DX_PI_F/2;

	//�����蔻��̑傫����ݒ�
	scale = Vector2D(50.0f);

	velocity = Vector2D(2.5f, 2.0f);

	if (InputControl::GetKeyDown(KEY_INPUT_SPACE) && (InputControl::GetKey(KEY_INPUT_LEFT)))
	{
		left = true;
	}
	else if (InputControl::GetKeyDown(KEY_INPUT_SPACE) && (InputControl::GetKey(KEY_INPUT_RIGHT)))
	{
		right = true;
	}

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

Blast blast;

void Bom::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() < EnemyType)
	{
		velocity.y = 0.0f;
		delete_object = 1;
	}
	
}

void Bom::Movement()
{
	radian = DX_PI_F / 2;

	if (location.y < 410)
	{
		location.y += velocity.y;
	}	
	else
	{
		blast.Animation();
		velocity = 0.0f;
		delete_object = 1;
	}
	
	if (left == true && location.x > 0)
	{
		radian = DX_PI_F / 1.5;
		location.x -= velocity.x;
	}
	else if (right == true && location.x < 640)
	{
		radian = DX_PI_F / 3;
		location.x += velocity.x;
	}
	
}
