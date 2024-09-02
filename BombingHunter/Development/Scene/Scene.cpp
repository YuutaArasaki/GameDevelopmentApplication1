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

//�R���X�g���N�^
Scene::Scene() : objects(), back_scene(),count(0),enemy_max(10),
bom_max(1),ones_place(0),tens_place(6),Score(0),GameTime(0),
Result_flag(0),hight_Score(0),restart(false)
{
	//X���W�̐ݒ�
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y���W�̐ݒ�
	Location_Y[0] = 320.0f;
	Location_Y[1] = 280.0f;
	Location_Y[2] = 220.0f;
	Location_Y[3] = 140.0f;
	Location_Y[4] = 360.0f;

	for (int i = 0; i < 4; i++)
	{
		enemy_count[i] = 0;
	}

	//�t�H���g�p�ϐ��̏�����
	for (int i = 0; i < 10; i++)
	{
		Font[i] = NULL;
	}

	//���U���g�摜�p�̕ϐ��̏�����
	for (int i = 0; i < 4; i++)
	{
		Result_image[i] = NULL;
	}

	//UI�摜�p�ϐ��̏�����
	for (int i = 0; i < 3; i++)
	{
		UI_image[i] = NULL;
	}

	//BGM�p�ϐ��̏�����
	for (int i = 0; i < 2; i++)
	{
		BGM[i] = NULL;
	}

	//SE�p�̏�����
	for (int i = 0; i < 4; i++)
	{
		SE[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		S_ones_place[i] = 0;
		S_tens_place[i] = 0;
		S_hundreds_place[i] = 0;
		S_thousands_place[i] = 0;
	}
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	 Finalize();
}

//����������
void Scene::Initialize()
{
	GameTime = 60;

	//�v���C���[�𐶐�����
	p=CreateObject<Player>(Vector2D(320.0f, 50.0f));

	//�e�G�̍ő�o����
	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 2;
	enemy_count[HAPI] = 2;
	enemy_count[KIN] = 1;

	enemy_max = 10;

	Score = 0;

	bom_max = 1;
	
	//�w�i�摜
	back_scene = LoadGraph("Resource/images/backscene.png");

	//�^�C�}�[�摜
	UI_image[0] = LoadGraph("Resource/images/Score/timer-03.png");

	//�X�R�A�t�H���g�摜
	UI_image[1] = LoadGraph("Resource/images/Score/font-Score.png");

	//�n�C�X�R�A�t�H���g�摜
	UI_image[2] = LoadGraph("Resource/images/Score/font-HighScore.png");

	//�O�`�X�̃t�H���g�摜
	LoadDivGraph("Resource/images/Score/Font_numbers.png", 10, 5, 2, 160, 214, Font);

	//�X�R�A�]���̃t�H���g�摜
	LoadDivGraph("Resource/images/Score/Resulte_image.png", 5, 1, 5, 800, 317, Result_image);
	
	//BGM�ǂݍ���
	BGM[0] = LoadSoundMem("Resource/Sound/BGM/BGM_arrows.wav");
	BGM[1] = LoadSoundMem("Resource/Sound/BGM/BGM_timeup.wav");

	//BGM�̍Đ�
	PlaySoundMem(BGM[0], DX_PLAYTYPE_LOOP, TRUE);

	//���U���gSE�ǂݍ���
	SE[0] = LoadSoundMem("Resource/Sound/ResultSE/SE_bad.wav");
	SE[1] = LoadSoundMem("Resource/Sound/ResultSE/SE_ok.wav");
	SE[2] = LoadSoundMem("Resource/Sound/ResultSE/SE_good.wav");
	SE[3] = LoadSoundMem("Resource/Sound/ResultSE/SE_perfect.wav");


	//�n�C�X�R�A�ɉ����ăt�H���g��ς���ׂ̏���
	S_ones_place[1] = hight_Score % 10;
	S_tens_place[1] = hight_Score % 100 / 10;
	S_hundreds_place[1] = hight_Score % 1000 / 100;
	S_thousands_place[1] = hight_Score % 10000 / 1000;

	Result_flag = 0;

	restart = false;

}

//�X�V����
void Scene::Update()
{
	//�������ԃJ�E���g����
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


	//�������Ԃ��O�b�ɂȂ�����I��
	if (GameTime <= 0)
	{
		Finalize();
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//���e��������
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bom_max > 0 && GameTime > 0)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_max--;
		}
	}
	
	//�e�̐����m��
	int  probability;

	//�G�̒e��������
	for (int i = 0; i < objects.size(); i++)
	{
		int type = objects[i]->GetType();

		if (type == HAKO)
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

		//�G�̒e�ɓ��������玞�Ԃ����炷����
		if (objects[i]->TimeMinus() == TRUE && type == BULLET)
		{
			GameTime += GameTime / 12 * -1;
		}
	}
		


	//�G�̐�������
	if (enemy_max > 0 && GameTime > 0)
	{
		//�n�l�e�L�𐶐����鏈��
		if (enemy_count[HANE] > 0 && GetRand(100) < 50)
		{
			CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(3)]));
			enemy_count[HANE]--;
			enemy_max--;
		}
		
		//�n�R�e�L�𐶐����鏈��
		if (enemy_count[HAKO] > 0 && GetRand(100) < 20)
		{
			CreateObject<Hako>(Vector2D(Location_X[GetRand(1)], Location_Y[4]));
			enemy_count[HAKO]--;
			enemy_max--;
		}
		
		//�n�[�s�[�𐶐����鏈��
		if (enemy_count[HAPI] > 0 && GetRand(100) < 40)
		{
			CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(2)]));
			enemy_count[HAPI]--;
			enemy_max--;
		}

		//���̃e�L�𐶐����鏈��
		if (enemy_count[KIN] > 0 && GameTime < 30 - GetRand(15))
		{
			CreateObject<Kinteki>(Vector2D(Location_X[GetRand(1)],400.0f));
			enemy_count[KIN]--;
			enemy_max--;
		}
	
	}

	
	
	//�I�u�W�F�N�g�̓����蔻��`�F�b�N����
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
			//�e�L����ʒ[�ɓ�����Ə�������
			if ((objects[i]->GetLocation().x < 0.0f) || (objects[i]->GetLocation().x > 640.0f))
			{
				int type = objects[i]->GetType();
				if (type < EnemyType)
				{
					enemy_max++;
					if (type != KIN)
					{
						enemy_count[type]++;
					}
					
					objects.erase(objects.begin() + i);
				}		
			}

			//�I�u�W�F�N�g����������
			if (objects[i]->DeleteObject() == 1)
			{
				int type = objects[i]->GetType();

				//�e�L����������
				if (type < EnemyType)
				{
					Score += objects[i]->GetScorePoint();
					if (Score <= 0)
					{
						Score = 0;
					}
					enemy_max++;
					enemy_count[type]++;
				}
				else if (type == BOM)	//���e���e�L���ʉ��ɐG�ꂽ�Ƃ��A���̏ꏊ�ɔ����𐶐����鏈��
				{
					CreateObject<Blast>(objects[i]->GetLocation());
					bom_max++;
				}
	
				objects.erase(objects.begin() + i);
			}
		}

		//�X�R�A�ɉ����ăt�H���g��ς���ׂ̏���
		S_ones_place[0] = Score % 10;
		S_tens_place[0] = Score % 100 / 10;
		S_hundreds_place[0] = Score % 1000 / 100;
		S_thousands_place[0] = Score % 10000 / 1000;

}

//�`�揈��
void Scene::Draw() const
{

	//�w�i�摜�`�揈��
	DrawRotaGraphF(320, 220, 0.73, 0, back_scene, TRUE);

	//�^�C�}�[�摜�`�揈��
	DrawRotaGraphF(30, 462, 0.7, 0, UI_image[0], TRUE);

	//�������ԕ`�揈��
	//��̈�
	DrawExtendGraph(85, 445, 115, 480, Font[ones_place], TRUE);
	//�\�̈�
	DrawExtendGraph(55, 445, 85, 480, Font[tens_place], TRUE);

	//�X�R�A�`�揈��
	DrawRotaGraphF(170, 460, 1.5, 0, UI_image[1], TRUE);
	//��̈�
	DrawExtendGraph(285, 450, 305, 475, Font[S_ones_place[0]], TRUE);
	//�\�̈�
	DrawExtendGraph(260, 450, 280, 475, Font[S_tens_place[0]], TRUE);
	//�S�̈�
	DrawExtendGraph(235, 450, 255, 475, Font[S_hundreds_place[0]], TRUE);
	//��̈�
	DrawExtendGraph(210, 450, 230, 475, Font[S_thousands_place[0]], TRUE);	

	//�n�C�X�R�A�`��
	DrawRotaGraphF(385, 460, 1.5, 0, UI_image[2], TRUE);
	//��̈�
	DrawExtendGraph(520, 450, 540, 475, Font[S_ones_place[1]], TRUE);
	//�\�̈�
	DrawExtendGraph(495, 450, 515, 475, Font[S_tens_place[1]], TRUE);
	//�S�̈�
	DrawExtendGraph(470, 450, 490, 475, Font[S_hundreds_place[1]], TRUE);
	//��̈�
	DrawExtendGraph(445, 450, 465, 475, Font[S_thousands_place[1]], TRUE);

	
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	
}


//�I��������
void Scene::Finalize()
{

	StopSoundMem(BGM[0]);

	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//�I������BGM
	PlaySoundMem(BGM[1], DX_PLAYTYPE_BACK, TRUE);
	
	//�n�C�X�R�A�X�V���̒l���
	if (Score > hight_Score)
	{
		hight_Score = Score;
	}
	//���I�z��̉��
	objects.clear();
	
}

//�����蔻��`�F�b�N����
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

//���U���g�V�[���ł̉摜�`���SE�Đ�
void Scene::ResultDraw()
{
	
	////�I�����̃X�R�A�ɂ���ĕ]���t�H���g��`�悷�鏈��
	if (GameTime <= 0 && restart != true)
	{
		count++;
		//FINISH�̉摜�`��
		if (count < 180 && Result_flag == 0)
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Result_image[0], TRUE);
		}
		else if (Result_flag == 0)
		{
			Result_flag = 1;
		}

		if (3000 <= Score && Result_flag >= 1)	//Perfect�̉摜�`��
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Result_image[4], TRUE);
			
			if (Result_flag == 1)	//Result_flag���P�̎�����SE���Đ�����iSE��������Đ�����邱�Ƃ�h�����߁j
			{
				Result_flag = 2;
				PlaySoundMem(SE[3], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (1500 <= Score && Result_flag >= 1)	//GOOD�̉摜�`��
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Result_image[3], TRUE);
			
			if (Result_flag == 1)
			{
				Result_flag = 2;
				PlaySoundMem(SE[2], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (1000 <= Score && Result_flag >= 1)	//OK�̉摜�`��
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Result_image[2], TRUE);
			
			if (Result_flag == 1)
			{
				Result_flag = 2;
				PlaySoundMem(SE[1], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		else if (1000 > Score && Result_flag >= 1) //BAD�̉摜�`��
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Result_image[1], TRUE);	
			
			if (Result_flag == 1)
			{
				Result_flag = 2;
				PlaySoundMem(SE[0], DX_PLAYTYPE_BACK, TRUE);
			}
			
		}	

		//���X�^�[�g����
		if (Result_flag == 2)
		{
			SetFontSize(40);

			DrawFormatString(90, 360, GetColor(255,255,255), "R�L�[�������ƃ��X�^�[�g");

			if (InputControl::GetKeyDown(KEY_INPUT_R))
			{
				restart = true;
				StopSoundMem(BGM[1]);
				Initialize();
			}
		}
	}
}
