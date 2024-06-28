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
	//ボムの画像読み込み
	image = LoadGraph("Resource/Images/bom/bom.png");

	//SE読み込み
	SE = LoadSoundMem("Resource/Sound/SE/pan.wav");
	

	PlaySoundMem(SE, DX_PLAYTYPE_BACK, TRUE);

	if (image == -1)
	{
		throw("爆弾の画像がありません\n");
	}

	
	object_type = BOM;

	//向きの設定
	radian = DX_PI_F/2;

	//当たり判定の大きさを設定
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

	//デバック用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

void Bom::Finalize()
{
	//使用した画像を開放する
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
