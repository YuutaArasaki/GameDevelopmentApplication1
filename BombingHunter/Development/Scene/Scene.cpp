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
Scene::Scene() : objects(), back_scene(), count(0),enemy_Max(10),
bom_Max(1),GameTime(60),ones_place(0),tens_place(6),Score(0),
S_ones_place(0),S_tens_place(0),S_hundreds_place(0),S_thousands_place(0)
{
	//X���W�̐ݒ�
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y���W�̐ݒ�
	Location_Y[0] = 340.0f;
	Location_Y[1] = 280.0f;
	Location_Y[2] = 220.0f;
	Location_Y[3] = 140.0f;
	Location_Y[4] = 400.0f;

	//�e�G�̍ő�o����
	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 2;
	enemy_count[HAPI] = 2;

	for (int i = 0; i < 10; i++)
	{
		Font[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		Font_Sentence[i] = NULL;
	}

	for (int i = 0; i < 3; i++)
	{
		UI_image[i] = NULL;
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
	//�v���C���[�𐶐�����
	p=CreateObject<Player>(Vector2D(320.0f, 50.0f));
	
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
	LoadDivGraph("Resource/images/Score/Font_Sentence.png", 4, 1, 4, 800, 330, Font_Sentence);
	

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
		if (bom_Max > 0)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_Max--;
		}
	}
		
		
	//�G�̒e��������
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
		


	//�G�̐�������
	if (enemy_Max > 0 && GameTime <= 60)
	{
		
		//�n�l�e�L�𐶐����鏈��
		if (enemy_count[HANE] > 0 && GetRand(100) < 50)
		{
			CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(3)]));
			enemy_count[HANE]--;
			enemy_Max--;
		}
		
		//�n�R�e�L�𐶐����鏈��
		if (enemy_count[HAKO] > 0 && GetRand(100) < 20)
		{
			CreateObject<Hako>(Vector2D(Location_X[GetRand(1)], Location_Y[4]));
			enemy_count[HAKO]--;
			enemy_Max--;
		}
		
		//�n�[�s�[�𐶐����鏈��
		if (enemy_count[HAPI] > 0 && GetRand(100) < 40)
		{
			CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[GetRand(2)]));
			enemy_count[HAPI]--;;
			enemy_Max--;
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
				if (type < EnemyType /*&& type != BOM && type != BLAST && type != BULLET*/)
				{
					enemy_Max++;
					enemy_count[objects[i]->GetType()]++;
					objects.erase(objects.begin() + i);
				}		
			}

			//�I�u�W�F�N�g����������
			if (objects[i]->DeleteObject() == 1)
			{
				int type = objects[i]->GetType();

				//�e�L����������
				if (type != BOM && type != BLAST && type != BULLET)
				{
					Score += objects[i]->GetScorePoint();
					if (Score <= 0)
					{
						Score = 0;
					}
					enemy_Max++;
					enemy_count[type]++;
				}
				else if (type == BOM)	//���e���e�L���ʉ��ɐG�ꂽ�Ƃ��A���̏ꏊ�ɔ����𐶐����鏈��
				{
					CreateObject<Blast>(objects[i]->GetLocation());
					bom_Max++;
				}
	
				objects.erase(objects.begin() + i);
			}
		}

		//�X�R�A�ɉ����ăt�H���g��ς���ׂ̏���
		S_ones_place = Score % 10;
		S_tens_place = Score % 100 / 10;
		S_hundreds_place = Score % 1000 / 100;
		S_thousands_place = Score % 10000 / 1000;
	
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
	DrawRotaGraphF(190, 460, 1.7, 0, UI_image[1], TRUE);
	//��̈�
	DrawExtendGraph(325, 445, 355, 480, Font[S_ones_place], TRUE);
	//�\�̈�
	DrawExtendGraph(295, 445, 325, 480, Font[S_tens_place], TRUE);
	//�S�̈�
	DrawExtendGraph(265, 445, 295, 480, Font[S_hundreds_place], TRUE);
	//��̈�
	DrawExtendGraph(235, 445, 265, 480, Font[S_thousands_place], TRUE);

	
	//�I�����̃X�R�A�ɂ���ĕ]���t�H���g��`�悷�鏈��
	if (GameTime <= 0)
	{
		if (3000 <= Score)
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[3], TRUE);
		}
		else if (1500 <= Score)
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[2], TRUE);
		}
		else if (1000 <= Score)
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[1], TRUE);
		}
		else if (1000 > Score)
		{
			DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[0], TRUE);
		}
	}
	


	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}


//�I��������
void Scene::Finalize()
{
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

	if (3000 <= Score)
	{
		DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[3], TRUE);
	}
	else if (1500 <= Score)
	{
		DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[2], TRUE);
	}
	else if (1000 <= Score)
	{
		DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[1], TRUE);
	}
	else if (1000 > Score)
	{
		DrawRotaGraphF(320, 220, 0.6, 0, Font_Sentence[0], TRUE);
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

