#include "Bom.h"
#include "../../Utility/InputControl.h"
#include "Player.h"
#include "DxLib.h"

Bom::Bom() : animation_count(0), count(0)
{
	for (int i = 0; i < 4; i++)
	{
		bom_image[i] = NULL;
	}
}

Bom::~Bom()
{

}

void Bom::Initialize()
{
	bom_image[0] = LoadGraph("Resource/Images/bom/bom.png");
	bom_image[1] = LoadGraph("Resource/Images/bom/bakufuu1.png");
	bom_image[2] = LoadGraph("Resource/Images/bom/bakufuu2.png");
	bom_image[3] = LoadGraph("Resource/Images/bom/bakufuu3.png");

	for (int i = 0; i < 4; i++)
	{
		if (bom_image[i] == -1)
			{
				throw("爆弾の画像がありません\n");
			}
	}
	
	//向きの設定
	radian = DX_PI_F/2;

	//当たり判定の大きさを設定
	scale = 64.0f;

	//初期画像の設定
	image = bom_image[0];
}

void Bom::Update()
{
	Movement();

	BomHit();
}

void Bom::Draw() const
{
	
		DrawRotaGraph(location.x, location.y, 0.7, radian, image, TRUE);

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
	DeleteGraph(bom_image[0]);
	DeleteGraph(bom_image[1]);
	DeleteGraph(bom_image[2]);
	DeleteGraph(bom_image[3]);
}

void Bom::OnHitCollision(GameObject* hit_object)
{
	animation_count = 0;
	animation_count++;

	//画像の切り替え
	
		

}

void Bom::Movement()
{
	location.y += 3.0f;
}

void Bom::BomHit()
{
	
}

Vector2D Bom::SetLocation()
{
	return location;
}
