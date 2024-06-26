#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet() : animation_count(0),player(0)
{
	for (int i = 0; i < 4; i++)
	{
		Bullet_image[i] = NULL;
	}
}


Bullet::~Bullet()
{

}

//初期化処理
void Bullet::Initialize()
{
	Bullet_image[0] = LoadGraph("Resource/Images/teki/hakoteki/Bullet1.png");
	Bullet_image[1] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff1.png");
	Bullet_image[2] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff2.png");
	Bullet_image[3] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff3.png");

	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (Bullet_image[i] == -1)
		{
			throw ("Bulletの画像がありません\n");
		}
	}
	
	//オブジェクトタイプ
	object_type = BULLET;

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさ
	scale = 20.0f;

	//画像の初期設定
	image = Bullet_image[0];

	//移動量の設定
	velocity = 0.0f;
	
	if (player!=nullptr)
	{
		player_location = player->GetLocation();
		velocity = GetDirection(player_location, this->location);
	}

}

//更新処理
void Bullet::Update()
{
	Movement();

	if (Hit == TRUE)
	{
		Animation();
	}
}

//描画処理
void Bullet::Draw() const
{
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	//デバック用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了処理
void Bullet::Finalize()
{
	DeleteGraph(Bullet_image[0]);
	DeleteGraph(Bullet_image[1]);
	DeleteGraph(Bullet_image[2]);
	DeleteGraph(Bullet_image[3]);
}

//当たり判定通知処理
void Bullet::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == PLAYER)
	{
		Hit = TRUE;
	}
	
}

//移動処理
void Bullet::Movement()
{
	if (location.y < 0)
	{
		delete_object = 1;
	}

	if (Hit != TRUE)
	{
		location += velocity;
	}
	
}

//アニメーション処理
void Bullet::Animation()
{
	animation_count++;

	if (animation_count >= 5)
	{
		animation_count = 0;

		if (image == Bullet_image[0])
		{
			image = Bullet_image[1];
		}
		else if (image == Bullet_image[1])
		{
			image = Bullet_image[2];
		}
		else if (image == Bullet_image[2])
		{
			image = Bullet_image[3];
		}
		else if (image == Bullet_image[3])
		{
			delete_object = 1;
		}
	}
}

//プレイヤーのポインタ取得処理
void Bullet::SetPlayer(Player* p)
{
	player = p;
}
