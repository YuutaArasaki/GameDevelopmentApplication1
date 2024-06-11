#include "Enemy.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"

Enemy::Enemy() : animation_count(0), velocity(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//画像の読み込み
	//ハネテキの画像
	animation[0] = LoadGraph("Resource/Images/teki/haneteki/haneteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/haneteki/haneteki2.png");

	//エラーチェック
	for (int i = 0; i < 10; i++)
	{
		if (animation[i] == -1)
			{
				throw ("ハネテキの画像がありません\n");
			}
	}
	

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 50.0f;

	//初期画像の設定
	image = animation[0];

	//スピード設定処理
	Plus_Speed[0] = Vector2D(1.0f, 0.5f);
	Plus_Speed[1] = Vector2D(0.4f, 0.5f);
	Plus_Speed[2] = Vector2D(0.7f, 0.5f);
	Minus_Speed[0] = Vector2D(-1.0f, 0.5f);
	Minus_Speed[1] = Vector2D(-0.4f, 0.5f);
	Minus_Speed[2] = Vector2D(-0.7f, 0.5f);

	//進行方向の設定
	if (location.x <= 0)
	{
		 velocity = Vector2D(Plus_Speed[GetRand(2)]);
	}
	else if (location.x >= 640)
	{
		velocity = Vector2D(Minus_Speed[GetRand(2)]);
	}
	

}

void Enemy::Update()
{
	Movement();

	AnimationControl();
}

void Enemy::Draw() const
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
	/*DrawRotaGraphF(location.x, location.y, 0.6, radian, enemy_image[1], TRUE, flip_flag);*/
	__super::Draw();
	
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Enemy::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	Bom bom;

	if (bom.BomHit() == true)
	{
		velocity = 0;
	}

	
}

void Enemy::Movement()
{
	/*if (((location.x + velocity.x) < scale.x)||(640.0f - scale.x)< (location.x + velocity.x))
	{
		velocity *= -1.0f;
	}
	if (((location.y + velocity.y) < scale.y) || (480.0f - scale.y) < (location.y + velocity.y))
	{
		velocity *= -1.0f;
	}*/

	/*if (location.x < 0 || location.x > 640)
	{
		velocity *= -1.0f;
	}*/
	
	location.x += velocity.x;
}

void Enemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
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

Vector2D Enemy::Location_X()
{
	return location.x;
}

//Vector2D Enemy::Enemy_Location(float location_x, float location_y)
//{
//	switch (GetRand(2))
//	{
//	case 0:
//		return location_x = 0.0f,location_y = 200.0f;
//		
//		break;
//
//	case 1:
//		return location_x = 0.0f,location_y = 270.0f;
//		
//		break;
//
//	case 2:
//		return location_x = 0.0f,location_y = 350.0f;
//		
//		break;
//
//	}
//}