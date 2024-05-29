#include "Kinnoteki.h"
#include "DxLib.h"

Kinnoteki::Kinnoteki() : animation_count(0), velocity(0.0f), animation_image_count()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Kinnoteki::~Kinnoteki()
{

}

void Kinnoteki::Initialize()
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

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];

	//進行方向の設定
	velocity = Vector2D(1.0f, -0.5f);
}

void Kinnoteki::Update()
{
	Movement();

	AnimationControl();
}

void Kinnoteki::Draw() const
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


void Kinnoteki::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Kinnoteki::OnHitCollision(GameObject* hit_object)
{
	velocity = 0.0f;
}

void Kinnoteki::Movement()
{
	/*if (((location.x + velocity.x) < scale.x) || (640.0f - scale.x) < (location.x + velocity.x))
	{
		velocity *= -1.0f;
	}*/

	if ((location.x < 0) || (location.x > 640))
	{
		velocity *= -1.0f;
	}

	location.x += velocity.x;
}


void Kinnoteki::AnimationControl()
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

	
}