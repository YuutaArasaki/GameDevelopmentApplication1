#pragma once
#include "../GameObject.h"
#include <math.h>

class Bom : public GameObject
{
private:
	int bom_image;			//ボムの画像
	int animation_count;	//アニメーションカウント
	Vector2D velocity;		//進行方向
	bool left;				//爆弾の方向（右）
	bool right;				//爆弾の方向（左）
	

public:
	Bom();		//コンストラクタ
	~Bom();		//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了処理
	virtual void OnHitCollision(GameObject* hit_object) override;	//当たり判定通知処理
	
	void Movement();		//移動処理
};

