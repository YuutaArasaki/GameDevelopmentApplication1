#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0), filp_flag(FALSE), boomimage()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Tri_pilot1.png");
	animation[1] = LoadGraph("Resource/Images/Tri_pilot2.png");
	boomimage = LoadGraph("Resource/Images/bom/bom.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || boomimage == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);

	//デバック用
	#if _DEBUG
		//当たり判定の可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale/ 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Player::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	
}

//移動処理
void Player::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y += -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 1.0f;
		filp_flag = FALSE;
	}
	
	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Player::AnimeControl()
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

Vector2D Player::GetLocation()
{
	return location;
}

//void Player::PlayerBoom()
//{
//	int Boomlocation = location.y;
//
//	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
//	{
//		DrawFormatString(320, 240, GetColor(255, 255, 255), "ボムの座標%d\n", Boomlocation, TRUE);
//		DrawRotaGraph(location.x, Boomlocation, 1.0, radian, boomimage, TRUE, filp_flag);
//	}
//
//	Boomlocation += -1.0f;
//
//}