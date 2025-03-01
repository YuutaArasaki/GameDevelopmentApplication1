#pragma once

#include "../Utility/Vector2D.h"

typedef enum
{
	HANE,
	HAKO,
	HAPI,
	KIN,
	EnemyType,
	BOM,
	PLAYER,
	BLAST,
	BULLET,
	Object_Type,
}TYPE;
 


//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;		//位置情報
	Vector2D scale;			//大きさ
	double radian;			//向き
	int image;				//描画する画像
	int sound;				//再生する音源
	int object_type;		//オブジェクトの種類
	int delete_object;		//オブジェクトの消去
	bool Hit;				//オブジェクトがHitしたかどうか
	int count;				//フレームカウント
	int Score_Point;		//各敵のスコア
	int Score_image;		//敵を倒したときに表示するスコア画像
	int SE;					//SE
	bool Time_minus;		//時間を減らすかどうかの判定

public:
	GameObject();
	~GameObject();
	virtual void Initialize();	//初期化設定
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//終了処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//オブジェクトのタイプ取得
	virtual int GetType();

	//オブジェクトのヒット取得
	virtual bool GetHit();

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさ取得処理
	Vector2D GetBoxSize() const;

	//消すオブジェクトかどうかの判定処理
	int DeleteObject();

	//テキの弾をトリパイロットの方向に飛ばす処理
	Vector2D GetDirection(Vector2D location_p,Vector2D location_b);

	//各敵のスコアを取得する処理
	int GetScorePoint();
	
	//時間を減らすかどうかの判定取得 
	bool TimeMinus();
};

