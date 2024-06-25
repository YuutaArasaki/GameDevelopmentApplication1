#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"
#include "../Utility/Vector2D.h"



class Scene
{
private:
	std::vector<GameObject*> objects;	
	int back_scene;						//背景画像
	int count;							//ゲームのフレームカウント
	float Location_X[2];				//X座標
	float Location_Y[5];				//Y座標
	int enemy_count[3];					//各敵ごとの最大出現数
	int enemy_Max;						//敵の最大出現数
	int enemy_timecount;				//敵の出現する感覚の秒数カウント
	int bom_Max;						//爆弾の出せる数
	int GameTime;						//ゲームの制限時間
	int Font[10];
	

public:
	Scene();		//コンストラクタ
	~Scene();		//デストラクタ

	void Initialize();	//初期化処理
	void Update();		//更新処理
	void Draw() const;	//描画処理
	void Finalize();	//終了処理

private:

	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//位置情報の設定
		new_object->SetLocation(location);
		//初期化処理
		new_object->Initialize();
		

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};

