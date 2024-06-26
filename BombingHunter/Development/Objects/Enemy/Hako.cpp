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

//初期化処理
void Hako::Initialize()
{
	//画像の読み込み
	//ハコテキの画像
	animation[0] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki2.png");

	

	//エラーチェック
	for (int i = 0; i < 2; i++)
	{
		if (animation[i] == -1)
		{
			throw ("ハコテキの画像がありません\n");
		}
	}

	//敵のタイプ設定
	object_type = HAKO;

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 40.0f;

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

	Score_Point = 200;
}

//更新処理
void Hako::Update()
{
	Movement();

	AnimationControl();

	//Bomに当たった時に透過させる為の値変更処理
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

//描画処理
void Hako::Draw() const
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

	//デバック用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

//終了処理
void Hako::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Hako::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == BOM)
	{
		Hit = TRUE;
	velocity = 0.0f;
	}
	
}

//移動処理
void Hako::Movement()
{
	location.x += velocity.x;
}

//アニメーション処理
void Hako::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 30)
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

	//Hitした時のアニメーション
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

