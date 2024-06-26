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
Scene::Scene() : objects(), back_scene(), count(0),enemy_Max(10),enemy_timecount(),bom_Max(1),GameTime(60),ones_place(0),tens_place(6)
{
	//X座標の設定
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y座標の設定
	Location_Y[0] = 340.0f;
	Location_Y[1] = 280.0f;
	Location_Y[2] = 220.0f;
	Location_Y[3] = 140.0f;
	Location_Y[4] = 400.0f;

	//各敵の最大出現数
	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 2;
	enemy_count[HAPI] = 2;

	time_image = NULL;

	for (int i = 0; i < 10; i++)
	{
		Font[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		Font_Sentence[i] = NULL;
	}

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
	
	//背景画像
	back_scene = LoadGraph("Resource/images/backscene.png");

	//タイマー画像
	time_image = LoadGraph("Resource/images/Score/timer-03.png");

	LoadDivGraph("Resource/images/Score/Font_Score.png", 10, 5, 2, 160, 214, Font);

	LoadDivGraph("Resource/images/Score/Font_Sentence.png", 4, 1, 4, 800, 307, Font_Sentence);
	if (Font_Sentence[0] == -1)
	{
		throw ("フォント画像がありません\n");
	}
}

//更新処理
void Scene::Update()
{
	
	//制限時間カウント処理
		
		count++;
		if (count >= 60)
		{
			if (GameTime > 0)
			{
				count = 0;
				GameTime--;
				tens_place = GameTime / 10;
				ones_place = GameTime % 10;
			}
			
		}

		//制限時間が０秒になったら終了
		if (GameTime <= 0)
		{
			Finalize();
		}


	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//爆弾生成処理
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bom_Max > 0)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_Max--;
		}
	}
		
		
	//敵の弾生成処理
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() == HAKO)
		{
			if (GetRand(100) > 99)
			{
				b = CreateObject<Bullet>(Vector2D(objects[i]->GetLocation()));
				b->SetPlayer(p);
				b->Initialize();
			}
		}
	}
		


	//敵の生成処理
	if (enemy_Max > 0 && GameTime < 60)
	{
		
		//ハネテキを生成する処理
		if (enemy_count[HANE] > 0 && GetRand(100) < 50)
		{
			CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(3)]));
			enemy_count[HANE]--;
			enemy_Max--;
		}
		
		//ハコテキを生成する処理
		if (enemy_count[HAKO] > 0 && GetRand(100) < 20)
		{
			CreateObject<Hako>(Vector2D(Location_X[GetRand(1)], Location_Y[4]));
			enemy_count[HAKO]--;
			enemy_Max--;
		}
		
		//ハーピーを生成する処理
		if (enemy_count[HAPI] > 0 && GetRand(100) < 40)
		{
			CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(2)]));
			enemy_count[HAPI]--;;
			enemy_Max--;
		}
	
	}

	
	
	//オブジェクトの当たり判定チェック処理
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i+ 1; j < objects.size(); j++)
		{	
			if (objects[i]->GetHit() != TRUE && objects[j]->GetHit() != TRUE)
			{
				HitCheckObject(objects[i], objects[j]);	
			}
				
		}

	}

		for (int i = 1; i < objects.size(); i++)
		{
			//テキが画面端に当たると消す処理
			if ((objects[i]->GetLocation().x < 0.0f) || (objects[i]->GetLocation().x > 640.0f))
			{
				int type = objects[i]->GetType();
				if (type < EnemyType /*&& type != BOM && type != BLAST && type != BULLET*/)
				{
					enemy_Max++;
					enemy_count[objects[i]->GetType()]++;
					objects.erase(objects.begin() + i);
				}		
			}

			//オブジェクトを消す処理
			if (objects[i]->DeleteObject() == 1)
			{
				int type = objects[i]->GetType();

				//テキを消す処理
				if (type != BOM && type != BLAST && type != BULLET)
				{
					enemy_Max++;
					enemy_count[type]++;
				}
				else if (type == BOM)	//爆弾がテキや画面下に触れたとき、その場所に爆風を生成する処理
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
	//背景画像描画処理
	DrawRotaGraphF(320, 220, 0.73, 0, back_scene, TRUE);
	DrawRotaGraphF(50, 462, 0.7, 0, time_image, TRUE);
	DrawExtendGraph(100,445,130, 480, Font[ones_place], TRUE);
	DrawExtendGraph(75, 445, 105, 480, Font[tens_place], TRUE);

	DrawExtendGraph(320, 240, 500, 320, Font_Sentence[2], TRUE);


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

//当たり判定チェック処理
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

