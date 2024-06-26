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
	//画像の読み込み
	//金のテキの画像
	animation[0] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki2.png");
	animation[2] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki3.png");
	animation[3] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki4.png");
	animation[4] = LoadGraph("Resource/Images/teki/kinnoteki/kinnoteki5.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ハーピーの画像がありません\n");
	}

	//敵のタイプ
	object_type = KIN;

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 30.0f;

	//初期画像の設定
	image = animation[0];

	//進行方向の設定
	if (location.x <= 0)
	{
		velocity = Vector2D(1.5f, 0.5f);
	}
	else if (location.x >= 640)
	{
		velocity = Vector2D(-1.5f, 0.5f);
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

	Score_Point = 1500;
}

//更新処理
void Kinteki::Update()
{
	Movement();

	AnimationControl();

	//Bomに当たった時に透過させる為の値変更処理
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

//描画処理
void Kinteki::Draw() const
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

//移動処理
void Kinteki::Movement()
{
	location.x += velocity.x;
}

//アニメーション処理
void Kinteki::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 40)
	{
		if (animation_image_count > 5)
		{
			animation_image_count = 0;
		}
		//カウントのリセット
		animation_count = 0;

		for (animation_image_count; animation_image_count < 5;)
		{
			image = animation[animation_image_count];
			break;
		}
		animation_image_count++;
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