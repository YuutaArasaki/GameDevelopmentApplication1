#include "GameObject.h"
#include "DxLib.h"
#include "math.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	scale(0.0),
	radian(0.0),
	image(0),
	sound(0),
	object_type(0),
	delete_object(0),
	Hit(FALSE),
	count(0),
	Score_Point(0),
	SE(NULL)
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
	this->location += location;
}

//当たり判定大きさ取得処理
Vector2D GameObject::GetBoxSize() const
{
	return scale;
}

//オブジェクトのタイプ取得処理
int GameObject::GetType()
{
	return object_type;
}

//消すオブジェクトかどうかの判定処理
int GameObject::DeleteObject()
{
	return delete_object;
}

//Hit取得処理
bool GameObject::GetHit()
{
	return Hit;
}

//敵の弾をPlayerまで飛ばすための処理
Vector2D GameObject::GetDirection(Vector2D location_p, Vector2D location_b)
{
	float x = 0;
	float y = 0;
	float z = 0;
	Vector2D direction;

	x = ((location_p.x - location_b.x) * (location_p.x - location_b.x));
	y = ((location_p.y - location_b.y) * (location_p.y - location_b.y));
	z = sqrt(x + y);
	x = (location_p.x - location_b.x) / z;
	y = (location_p.y - location_b.y) / z;

	direction = Vector2D(x, y);
	return direction;
}

int GameObject::GetScorePoint()
{
	return Score_Point;
}

