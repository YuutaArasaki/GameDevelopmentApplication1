#pragma once
#include "../../Objects/GameObject.h"
#include "../player/Player.h"


class Bullet : public GameObject
{
	Player* player;
	int Bullet_image[4];		//弾の画像
	int animation_count;		//弾のアニメーションフレームカウント
	Vector2D velocity;			//弾の移動量
	Vector2D player_location;	//プレイヤー（トリパイロット）の位置座標
	


public:
	Bullet();		//コンストラクタ
	~Bullet();		//デストラクタ

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

	//プレイヤーのポインタ取得処理
	void SetPlayer(Player* p);

private:
	//移動処理
	void Movement();

	//アニメーション処理
	void Animation();

};

