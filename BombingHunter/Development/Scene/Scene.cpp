#include "Scene.h"
#include "DxLib.h"

#include "../Objects/player/Player.h"
#include "../Objects/player/Bom.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Enemy/Hapi.h"
#include "../Objects/Enemy/Hakoteki.h"
#include "../Objects/Enemy/Kinnoteki.h"

//コンストラクタ
Scene::Scene() : objects(), back_scene(), count(5)
{
	//X座標の設定
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y座標の設定
	Location_Y[0] = 200.0f;
	Location_Y[1] = 270.0f;
	Location_Y[2] = 350.0f;
	Location_Y[3] = 440.0f;


}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	 Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 100.0f));
	
	back_scene = LoadGraph("Resource/images/backscene.png");

}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//for (int i = 0; i < objects.size(); i++)
	//{

	//		//当たり判定チェック処理
	//		HitCheckObject(objects[0], objects[i]);
	//	
	//}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}
	

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		
		//敵を生成する
		CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(2)]));
		
		if (count > 2)
		{
			CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[1]));
			/*CreateObject<Hakoteki>(Vector2D(70.0f,430.0f));*/
		}
		if (count > 4)
		{
			CreateObject<Kinnoteki>(Vector2D(Location_X[GetRand(1)], Location_Y[3]));
		}

		count--;
	
	}

	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
	}
}

//描画処理
void Scene::Draw() const
{
	DrawRotaGraphF(320, 260, 0.73, 0, back_scene, TRUE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}


//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//	//オブジェクトの距離を取得
	//	Vector2D Hitlocation = a->GetLocation() - b->GetLocation();
	//	
	//	//オブジェクトの当たり判定の大きさを取得
	//	Vector2D HitBoxSize = a->GetBoxSize() + b->GetBoxSize();
	//
	//	if ((fabs(Hitlocation.x) < HitBoxSize.x) && (fabs(Hitlocation.y) < HitBoxSize.y))
	//	{
	//		a->OnHitCollision(b);
	//		b->OnHitCollision(a);jd
	//	}

	//２つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//２つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}