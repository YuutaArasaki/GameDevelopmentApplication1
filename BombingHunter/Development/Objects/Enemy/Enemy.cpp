#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() : animation_count(0), direction(0.0f)
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
	animation[0] = LoadGraph("Resource/Images/teki/haneteki/haneteki1.png");
	animation[1] = LoadGraph("Resource/Images/teki/haneteki/haneteki2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ハネテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];

	//進行方向の設定
	/*direction = Vector2D(1.0f, -0.5f);*/

}

void Enemy::Update()
{
	Movement();

	AnimationControl();
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);
}

void Enemy::Finalize()
{

}

void Enemy::OnHitCollision(GameObject* hit_object)
{

}

void Enemy::Movement()
{

}

void Enemy::AnimationControl()
{

}