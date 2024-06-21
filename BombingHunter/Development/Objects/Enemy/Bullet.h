#pragma once
#include "../../Objects/GameObject.h"
#include "../player/Player.h"


class Bullet : public GameObject
{
	Player* player;
	int Bullet_image[4];
	int animation_count;
	Vector2D velocity;
	Vector2D player_location;

public:
	Bullet();
	~Bullet();

	//初期化処理
	virtual void  Initialize();

	//更新処理
	virtual void Update();

	//描画処理
	virtual void Draw() const;
	
	//終了処理
	virtual void Finalize();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	void SetPlayer(Player* p);

private:
	void Movement();

	void Animation();

	/*Vector2D GetDirection(Vector2D location_p, Vector2D location_b);*/
};

