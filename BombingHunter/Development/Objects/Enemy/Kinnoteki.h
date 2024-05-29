#pragma once
#include "Enemy.h"

class Kinnoteki : public Enemy
{
	private:
		int animation_image_count; //アニメーション画像カウント
		int animation[5];	//アニメーション画像
		int animation_count;	//アニメーション時間
		Vector2D velocity;		//進行方向

	public:
		Kinnoteki();
		~Kinnoteki();

		//初期化処理
		virtual void Initialize() override;
		//更新処理
		virtual void Update() override;
		//描画処理
		virtual void Draw() const override;
		//終了処理
		virtual void Finalize() override;

		//当たり判定通知処理
		virtual void OnHitCollision(GameObject * hit_object) override;

	private:
		//移動処理
		void Movement();
		//アニメーション制御
		void AnimationControl();
};

