#pragma once

#include "../Utility/Vector2D.h"

#define HANE (0);
#define HAKO (1);
#define HAPI (2);
#define KIN  (3);
#define Enemy_Type (4);


//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;		//位置情報
	Vector2D scale;			//大きさ
	double radian;			//向き
	int image;				//描画する画像
	int sound;				//再生する音源
	int enemy_type;


public:
	GameObject();
	~GameObject();
	virtual void Initialize();	//初期化設定
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//終了処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	virtual int GetType();

	//位置情報取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);
	//当たり判定の大きさ取得処理
	Vector2D GetBoxSize() const;
};

