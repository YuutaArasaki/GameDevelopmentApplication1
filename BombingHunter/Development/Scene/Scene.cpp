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
#include "ResultScene.h"


Player* p;
Bullet* b;
ResultScene r;

//コンストラクタ
Scene::Scene() : objects(), back_scene(), count(0),enemy_max(10),
bom_Max(1),GameTime(5),ones_place(0),tens_place(6),Score(0),
S_ones_place(0),S_tens_place(0),S_hundreds_place(0),S_thousands_place(0),
Soundflag(0)
{
	//X座標の設定
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y座標の設定
	Location_Y[0] = 340.0f;
	Location_Y[1] = 280.0f;
	Location_Y[2] = 220.0f;
	Location_Y[3] = 140.0f;
	Location_Y[4] = 340.0f;

	//各敵の最大出現数
	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 2;
	enemy_count[HAPI] = 2;
	enemy_count[KIN] = 1;

	//フォント用変数の初期化
	for (int i = 0; i < 10; i++)
	{
		Font[i] = NULL;
	}

	//リザルト画像用の変数の初期化
	for (int i = 0; i < 4; i++)
	{
		Result_image[i] = NULL;
	}

	//UI画像用変数の初期化
	for (int i = 0; i < 3; i++)
	{
		UI_image[i] = NULL;
	}

	//BGM用変数の初期化
	for (int i = 0; i < 2; i++)
	{
		BGM[i] = NULL;
	}

	//SE用の初期化
	for (int i = 0; i < 4; i++)
	{
		SE[i] = NULL;
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
	UI_image[0] = LoadGraph("Resource/images/Score/timer-03.png");

	//スコアフォント画像
	UI_image[1] = LoadGraph("Resource/images/Score/font-Score.png");

	//ハイスコアフォント画像
	UI_image[2] = LoadGraph("Resource/images/Score/font-HighScore.png");

	//０～９のフォント画像
	LoadDivGraph("Resource/images/Score/Font_numbers.png", 10, 5, 2, 160, 214, Font);

	//スコア評価のフォント画像
	LoadDivGraph("Resource/images/Score/Resulte_image.png", 5, 1, 5, 800, 315, Result_image);
	
	//BGM読み込み
	BGM[0] = LoadSoundMem("Resource/Sound/BGM/BGM_arrows.wav");
	BGM[1] = LoadSoundMem("Resource/Sound/BGM/BGM_timeup.wav");

	//BGMの再生
	PlaySoundMem(BGM[0], DX_PLAYTYPE_LOOP, TRUE);

	//リザルトSE読み込み
	SE[0] = LoadSoundMem("Resource/Sound/ResultSE/SE_bad.wav");
	SE[1] = LoadSoundMem("Resource/Sound/ResultSE/SE_ok.wav");
	SE[2] = LoadSoundMem("Resource/Sound/ResultSE/SE_good.wav");
	SE[3] = LoadSoundMem("Resource/Sound/ResultSE/SE_perfect.wav");

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
		if (bom_Max > 0 && GameTime > 0)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_Max--;
		}
	}
	
	//弾の生成確率
	float probability;

	//敵の弾生成処理
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() == HAKO)
		{
			probability = GameTime / 20;

			if (count >= 59)
			{
				if (GetRand(10) < probability)
				{
					b = CreateObject<Bullet>(Vector2D(objects[i]->GetLocation()));
					b->SetPlayer(p);
					b->Initialize();
				}
			}
		}
	}
		


	//敵の生成処理
	if (enemy_max > 0 && GameTime <= 60)
	{
		//ハネテキを生成する処理
		if (enemy_count[HANE] > 0 && GetRand(100) < 50)
		{
			CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(3)]));
			enemy_count[HANE]--;
			enemy_max--;
		}
		
		//ハコテキを生成する処理
		if (enemy_count[HAKO] > 0 && GetRand(100) < 20)
		{
			CreateObject<Hako>(Vector2D(Location_X[GetRand(1)], Location_Y[4]));
			enemy_count[HAKO]--;
			enemy_max--;
		}
		
		//ハーピーを生成する処理
		if (enemy_count[HAPI] > 0 && GetRand(100) < 40)
		{
			CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(2)]));
			enemy_count[HAPI]--;
			enemy_max--;
		}

		//金のテキを生成する処理
		if (enemy_count[KIN] > 0 && GameTime < 30 - GetRand(10))
		{
			CreateObject<Kinteki>(Vector2D(Location_X[GetRand(1)],400.0f));
			enemy_count[KIN]--;
			enemy_max--;
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
					enemy_max++;
					if (type != KIN)
					{
						enemy_count[type]++;
					}
					
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
					Score += objects[i]->GetScorePoint();
					if (Score <= 0)
					{
						Score = 0;
					}
					enemy_max++;
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

		//スコアに沿ってフォントを変える為の処理
		S_ones_place = Score % 10;
		S_tens_place = Score % 100 / 10;
		S_hundreds_place = Score % 1000 / 100;
		S_thousands_place = Score % 10000 / 1000;

	
}

//描画処理
void Scene::Draw() const
{
	int f;

	//背景画像描画処理
	DrawRotaGraphF(320, 220, 0.73, 0, back_scene, TRUE);

	//タイマー画像描画処理
	DrawRotaGraphF(30, 462, 0.7, 0, UI_image[0], TRUE);

	//制限時間描画処理
	//一の位
	DrawExtendGraph(85, 445, 115, 480, Font[ones_place], TRUE);
	//十の位
	DrawExtendGraph(55, 445, 85, 480, Font[tens_place], TRUE);

	//スコア描画処理
	DrawRotaGraphF(190, 460, 1.7, 0, UI_image[1], TRUE);
	//一の位
	DrawExtendGraph(325, 445, 355, 480, Font[S_ones_place], TRUE);
	//十の位
	DrawExtendGraph(295, 445, 325, 480, Font[S_tens_place], TRUE);
	//百の位
	DrawExtendGraph(265, 445, 295, 480, Font[S_hundreds_place], TRUE);
	//千の位
	DrawExtendGraph(235, 445, 265, 480, Font[S_thousands_place], TRUE);	

	//if (GameTime <= 0)
	//{
	//	/*f++;*/
	//	if (3000 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[4], TRUE);
	//		/*PlaySoundMem(SE[3], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1500 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[3], TRUE);
	//		/*PlaySoundMem(SE[2], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1000 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[2], TRUE);
	//		/*PlaySoundMem(SE[1], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1000 > Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[1], TRUE);
	//		PlaySoundMem(SE[0], DX_PLAYTYPE_BACK, TRUE);
	//		
	//	}
	//}

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	
}


//終了時処理
void Scene::Finalize()
{

	StopSoundMem(BGM[0]);

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

	PlaySoundMem(BGM[1], DX_PLAYTYPE_BACK, TRUE);

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

void Scene::ResultDraw(int count)
{
	

	//////終了時のスコアによって評価フォントを描画する処理
	//if (GameTime <= 0)
	//{
	//	if (count < 120)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[0], TRUE);
	//	}
	//	else if (3000 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[4], TRUE);
	//		/*PlaySoundMem(SE[3], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1500 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[3], TRUE);
	//		/*PlaySoundMem(SE[2], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1000 <= Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[2], TRUE);
	//		/*PlaySoundMem(SE[1], DX_PLAYTYPE_BACK, TRUE);*/
	//	}
	//	else if (1000 > Score)
	//	{
	//		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[1], TRUE);
	//		PlaySoundMem(SE[0], DX_PLAYTYPE_NORMAL, TRUE);
	//	}	

	/*}*/
}

int Scene::GetTime()
{
	return GameTime;
}