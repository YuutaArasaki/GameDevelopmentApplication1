#pragma once

#include "../GameObject.h"
#include "../player/Bom.h"

class Enemy : public GameObject
{
protected:
	bool flip_flag;
	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	Vector2D velocity;		//進行方向
	Vector2D Plus_Speed[3];	//右方向への移動速度
	Vector2D Minus_Speed[3];//左方向への移動速度
	int alpha;				//敵の透明度
	int count;				//フレームカウント

public:
	Enemy();
	~Enemy();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;


private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimationControl();

};

