#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"

//エネミー状態
enum eEnemyState
{
	idle,		//待機状態
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

enum eEnemyDirection
	{
		up,
		right,
		down,
		left,
		none
	};

class EnemyBase : public GameObject
{

protected:
	Player* player;					//プレイヤーのポインタ
	float speed;					//エネミースピード
	eEnemyState enemy_state;		//エネミー状態
	eEnemyType enemy_type;			//エネミーの種類
	Vector2D velocity;					//移動量
	eEnemyDirection direction;			//移動方向
	bool direction_flag;		//移動方向変更フラグ
	Vector2D teritory_panel[2];//エネミーの縄張り位置
	
private:
	std::vector<int> move_animation;	//移動アニメーション画像
	std::vector<int> eye_animation;		//目のアニメーション画像
	
	float animation_time;				//アニメーション時間
	int animation_count;				//アニメーション添字
	int flash_count;					//点滅カウント
	bool flash_flag;
	float state_time;					//エネミー状態時間
	int enemy_level;					//エネミーレベル
	const int animation_num[2] = { 0, 1, };
	float mini;
	float f[4] = { 0, 0, 0, 0 };

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
	void SetEnemyType(int t);
	EnemyBase* EnemyType();

private:
	void Movement(float delta_second);			//移動処理
	void Move_Idle();
	void Move_Fear(float delta_second);			//イジケ状態の移動処理
	void Move_Die(float delta_second);			//死亡状態の移動処理
	void AnimationControl(float delta_second);	//アニメーション処理
	void State_Change(float delta_second);		//状態の変更処理
	eEnemyType Get_EnemyType();					//エネミーのタイプを取得する
	float Enemy_Speed();						//エネミーのスピードを設定する処理
	eEnemyDirection ShortRoute(Vector2D tg);
	void SetDirection(eEnemyDirection d);
	void Set_TeritoryPanel();

protected:
	virtual void Move_Chase(Vector2D location);	//追跡状態の移動処理
	virtual void Move_Teritory();		//縄張り状態の移動処理
};