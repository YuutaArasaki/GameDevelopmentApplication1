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
Scene::Scene() : objects(), back_scene(), count(0),enemy_Max(10),enemy_timecount(),bom_Max(1),GameTime(60),ones_place(0),tens_place(6)
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
	time_image = LoadGraph("Resource/images/Score/timer-03.png");

	LoadDivGraph("Resource/images/Score/Font_Score.png", 10, 5, 2, 160, 214, Font);

	LoadDivGraph("Resource/images/Score/Font_Sentence.png", 4, 1, 4, 800, 307, Font_Sentence);
	if (Font_Sentence[0] == -1)
	{
		throw ("�t�H���g�摜������܂���\n");
	}
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
	if (enemy_Max > 0 && GameTime < 60)
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
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�`�揈��
	DrawRotaGraphF(320, 220, 0.73, 0, back_scene, TRUE);
	DrawRotaGraphF(50, 462, 0.7, 0, time_image, TRUE);
	DrawExtendGraph(100,445,130, 480, Font[ones_place], TRUE);
	DrawExtendGraph(75, 445, 105, 480, Font[tens_place], TRUE);

	DrawExtendGraph(320, 240, 500, 320, Font_Sentence[2], TRUE);


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

