#include "Hakoteki.h"
#include "DxLib.h"


Hakoteki::Hakoteki() : animation_count(0), velocity(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Hakoteki::~Hakoteki()
{

}

//初期化処理
void Hakoteki::Initialize()
{
	//画像の読み込み
	//ハコテキの画像
	animation[0] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/hakoteki/hakoteki2.png");
	//金のテキの画像
	/*animation[6] = LoadGraph("Resource/Images/teki/haneteki/Ha-pi-1.png");
	animation[7] = LoadGraph("Resource/Images/teki/Hapi/Ha-pi-2.png");*/


	//エラーチェック
	for (int i = 0; i < 10; i++)
	{
		if (animation[i] == -1)
		{
			throw ("ハコテキの画像がありません\n");
		}
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

void Hakoteki::Update()
{
	Movement();

	AnimationControl();
}

void Hakoteki::Draw() const
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

void Hakoteki::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	velocity = 0.0f;
}

void Hakoteki::Movement()
{
	if (((location.x + velocity.x) < scale.x) || (640.0f - scale.x) < (location.x + velocity.x))
	{
		velocity *= -1.0f;
	}

	location.x += velocity.x;
}

void Hakoteki::AnimationControl()
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
