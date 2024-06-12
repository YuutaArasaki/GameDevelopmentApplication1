#include "GameObject.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	scale(0.0),
	radian(0.0),
	image(0),
	sound(0),
	enemy_type(0)
{
}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{
	//画像の読み込み
	image = LoadGraph("Resource/Images/haneteki1.png");
}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{

}

//終了処理
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	
}

//位置所法取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//当たり判定大きさ取得処理
Vector2D GameObject::GetBoxSize() const
{
	return scale;
}

int GameObject::GetType()
{
	return enemy_type;
}