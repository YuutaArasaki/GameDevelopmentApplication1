#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"

//エネミー状態
enum eEnemyState
{
	ible,		//待機状態
	die,		//死亡状態
	TERITORY,	//縄張り状態
	CHASE,		//追跡状態
	FEAR,		//イジケ状態
};

//エネミータイプ
enum eEnemyType
{
	AKABE,
	PINKY,
	AOSUKE,
	GUZUTA,
};

class EnemyBase : public GameObject
{

protected:
	Player* player;					//プレイヤーのポインタ
	float speed;					//エネミースピード
	eEnemyState enemy_state;		//エネミー状態
	Vector2D teritory_location;		//エネミーの縄張り位置
	eEnemyType enemy_type;			//エネミーの種類

private:
	enum eEnemyDirection
	{
		up,
		right,
		down,
		left,
	};

	std::vector<int> move_animation;	//移動アニメーション画像
	std::vector<int> eye_animation;		//目のアニメーション画像
	Vector2D velocity;					//移動量
	eEnemyDirection direction;			//移動方向
	float animation_time;				//アニメーション時間
	int animation_count;				//アニメーション添字
	int flash_count;					//点滅カウント
	float state_time;					//エネミー状態時間
	int enemy_level;					//エネミーレベル
	const int animation_num[2] = { 0, 1, };


public:
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Initialize() override;		//初期化処理
	virtual void Update(float delta_second) override;	//更新処理
	virtual void Draw(const Vector2D& screen_offset) const override;	//描画処理
	virtual void Finalize() override;		//終了処理
	void OnHitCollision(GameObjectBase* hit_object) override;	//当たり判定通知処理
	eEnemyState GetEnemyState();		//エネミーの状態を取得する
	void Set_Player(Player* p);			//プレイヤーのポインタを取得する

private:
	void Movement(float delta_second);			//移動処理
	void Move_Teritory(float delta_second);		//縄張り状態の移動処理
	void Move_Fear(float delta_second);			//イジケ状態の移動処理
	void Move_Die(float delta_second);			//死亡状態の移動処理
	void AnimationControl(float delta_second);	//アニメーション処理
	void State_Change(float delta_second);		//状態の変更処理
	eEnemyType Get_EnemyType();					//エネミーのタイプを取得する
	float Enemy_Speed();						//エネミーのスピードを設定する処理

protected:
	virtual void Move_Chase(float delta_second);	//追跡状態の移動処理
};