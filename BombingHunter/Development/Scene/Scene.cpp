#include "Scene.h"
#include "DxLib.h"

#include "../Objects/player/Player.h"
#include "../Objects/player/Bom.h"
#include "../Objects/player/Blast.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Enemy/Hapi.h"
#include "../Objects/Enemy/Hako.h"
#include "../Objects/Enemy/Kinteki.h"
#include "../Objects/Enemy/Bullet.h"


Player* p;
Bullet* b;

//コンストラクタ
Scene::Scene() : objects(), back_scene(), count(5),enemy_Max(10),enemy_timecount(),bom_Max(1),bullet(1)
{
	//X座標の設定
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y座標の設定
	Location_Y[0] = 200.0f;
	Location_Y[1] = 350.0f;
	Location_Y[2] = 270.0f;;
	Location_Y[3] = 440.0f;

	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 3;
	enemy_count[HAPI] = 2;

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
	p=CreateObject<Player>(Vector2D(320.0f, 50.0f));
	
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

	

	//for (int i = 1; i < objects.size(); i++)
	//{
	//	for (int j = i + 1; j < objects.size(); j++)
	//	{
	//		//当たり判定チェック処理
	//		HitCheckObject(objects[i], objects[j]);
	//	}
	//}

	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bom_Max > 0)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_Max--;
		}
	}
	
	

	/*if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{*/	
		
		for (int i = 0; i < objects.size(); i++)
		{
			
			if (objects[i]->GetType() == HAKO)
			{
				if (GetRand(100) > 99)
				{
					b = CreateObject<Bullet>(Vector2D(objects[i]->GetLocation()));
					b->SetPlayer(p);
					b->Initialize();

					/*bullet = 1;*/
				}
				

			}
			
			
		}
		
	/*}*/

	/*if (bullet == 1)
	{
		bullet_count++;

		if (bullet_count >= 1)
		{
			bullet_count = 0;
			for (int i = 0; i < objects.size(); i++)
			{
				if (objects[i]->GetType() == BULLET)
				{
					objects[i]->SetLocation(objects[i]->GetDirection(player_location, objects[i]->GetLocation()));
				}

			}
		}
	}*/



	enemy_timecount++;

	if (enemy_timecount >= 60)
	{
		enemy_timecount = 0;
		if (enemy_Max > 0)
		{
			switch (GetRand(3))
			{

			case 0:
				if (enemy_count[HANE] > 0)
				{
					CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[/*GetRand(1)*/0]));
					enemy_count[0]--;
					enemy_Max--;
				}
				break;

			case 1:
				if (enemy_count[HANE] > 0)
				{
					CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[/*GetRand(1)*/1]));
					enemy_count[0]--;
					enemy_Max--;
				}
				break;

			case 2:
				if (enemy_count[HAKO] > 0)
				{
					CreateObject<Hako>(Vector2D(Location_X[GetRand(1)], 430.0f));
					enemy_count[1]--;
					enemy_Max--;
				}
				break;

			case 3:
				if (enemy_count[HAPI] > 0)
				{
					CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[2]));
					enemy_count[2]--;;
					enemy_Max--;
				}
				break;

			}
		}
	}
	
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i+ 1; j < objects.size(); j++)
		{	
			if (objects[i]->GetHit() != TRUE && objects[j]->GetHit() != TRUE)
			{
					//当たり判定チェック処理
					HitCheckObject(objects[i], objects[j]);	
			}
				
		}

	}

		for (int i = 1; i < objects.size(); i++)
		{
			if ((objects[i]->GetLocation().x < 0.0f) || (objects[i]->GetLocation().x > 640.0f))
			{
				int type = objects[i]->GetType();
				if (type < Object_Type && type != BOM && type != BLAST && type != BULLET)
				{
					enemy_Max++;
					enemy_count[objects[i]->GetType()]++;
					objects.erase(objects.begin() + i);
				}		
			}

			if (objects[i]->DeleteObject() == 1)
			{
				int type = objects[i]->GetType();
				if (type != BOM && type != BLAST && type != BULLET)
				{
					enemy_Max++;
					enemy_count[objects[i]->GetType()]++;
				}
				else if (type == BOM)
				{
					CreateObject<Blast>(objects[i]->GetLocation());
					bom_Max++;
				}

				objects.erase(objects.begin() + i);	
			}
		}
		
		
		

	
	
}

//描画処理
void Scene::Draw() const
{
	DrawRotaGraphF(320, 260, 0.73, 0, back_scene, TRUE);

	DrawFormatString(20, 20, GetColor(255, 255, 255), "時間 : %d", enemy_timecount);

	DrawFormatString(20, 40, GetColor(255, 255, 255), "敵の数 ： %d", enemy_count[0]);

	DrawFormatString(20, 60, GetColor(255, 255, 255), "敵の数 ： %d", enemy_count[1]);

	DrawFormatString(20, 80, GetColor(255, 255, 255), "敵の数 ： %d", enemy_count[2]);

	DrawFormatString(20, 100, GetColor(255, 255, 255), "敵の最大数 ： %d", enemy_Max);


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

//void Scene::DeleteObject()
//{
//
//}