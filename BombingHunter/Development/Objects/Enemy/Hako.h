#include "Enemy.h"

class Hako : public Enemy
{
private:
	int animation[2];	//アニメーション画像
	int animation_count;	//アニメーション時間
	Vector2D velocity;		//進行方向
	int Bullet[4];


public:
	Hako();
	~Hako();

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