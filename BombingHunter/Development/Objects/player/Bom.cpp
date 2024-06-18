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
				throw("爆弾の画像がありません\n");
			}

	
	object_type = Bomb;

	//向きの設定
	radian = DX_PI_F/2;

	//当たり判定の大きさを設定
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

void Bom::OnHitCollision(GameObject* hit_object)
{
	delete_object = 1;
	/*Animation();*/
	/*velocity.y = 0.0f;*/

	/*animation_count++;*/

	////画像の切り替え
	//if (animation_count >= 30)
	//{
	//	if (count > 4)
	//	{
	//		delete_object = 1;
	//	}
	//	//カウントのリセット
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
//	//画像の切り替え
//	if (animation_count >= 30)
//	{
//		if (count > 4)
//		{
//			delete_object = 1;
//		}
//		//カウントのリセット
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