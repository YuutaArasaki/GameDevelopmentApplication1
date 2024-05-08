#include "GameObject.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0),
	radian(0.0),
	image(0),
	sound(0)
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
	//当たり判定の可視化
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif // D_PIVOT_CENTER
}

//終了処理
void GameObject::Finalize()
{

}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
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