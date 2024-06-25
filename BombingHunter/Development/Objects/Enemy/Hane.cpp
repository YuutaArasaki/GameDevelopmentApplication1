#include "Enemy.h"
#include "DxLib.h"
#include "../../Scene/Scene.h"

Enemy::Enemy() : animation_count(0), velocity(0.0f),alpha(255),count(0), flip_flag(0)
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
	
	//敵のタイプ設定
	object_type = HANE;

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 50.0f;

	//初期画像の設定
	image = animation[0];

	//スピード設定処理
	Plus_Speed[0] = Vector2D(2.0f, 0.5f);
	Plus_Speed[1] = Vector2D(1.4f, 0.5f);
	Plus_Speed[2] = Vector2D(0.8f, 0.5f);
	Minus_Speed[0] = Vector2D(-2.0f, 0.5f);
	Minus_Speed[1] = Vector2D(-1.4f, 0.5f);
	Minus_Speed[2] = Vector2D(-0.8f, 0.5f);

	//進行方向の設定
	if (location.x <= 0)
	{
		velocity = Vector2D(Plus_Speed[GetRand(2)]);
	}
	else if (location.x >= 640)
	{
		velocity = Vector2D(Minus_Speed[GetRand(2)]);
	}

	//描画する敵の向き
	if (velocity.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}
}

//更新処理
void Enemy::Update()
{
	Movement();

	AnimationControl();

	//Bomに当たった時に透過させる為の値変更処理
	if (Hit == TRUE)
	{
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

//描画処理
void Enemy::Draw() const
{
	//Bomに当たった時の描画処理
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


	__super::Draw();

	//デバック用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

//終了処理
void Enemy::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOM)
	{
		Hit = TRUE;
		velocity = 0.0f;
	}
}

//移動処理
void Enemy::Movement()
{
	location.x += velocity.x;

}

//アニメーション処理
void Enemy::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 30 && Hit != TRUE)
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

	//Bomに当たった時のアニメーション
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

