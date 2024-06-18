#include "Scene.h"
#include "DxLib.h"

#include "../Objects/player/Player.h"
#include "../Objects/player/Bom.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Enemy/Hapi.h"
#include "../Objects/Enemy/Hakoteki.h"
#include "../Objects/Enemy/Kinnoteki.h"




//�R���X�g���N�^
Scene::Scene() : objects(), back_scene(), count(5), StartTime(),delete_count(),enemy_Max(10),time_count(),bom_count(0)
{
	//X���W�̐ݒ�
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y���W�̐ݒ�
	Location_Y[0] = 200.0f;
	Location_Y[1] = 350.0f;
	Location_Y[2] = 270.0f;;
	Location_Y[3] = 440.0f;

	enemy_count[HANE] = 5;
	enemy_count[HAKO] = 3;
	enemy_count[HAPI] = 2;

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
	CreateObject<Player>(Vector2D(320.0f, 100.0f));
	
	back_scene = LoadGraph("Resource/images/backscene.png");

	StartTime = GetNowCount();

}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
		
	}

	//for (int i = 1; i < objects.size(); i++)
	//{
	//	for (int j = i + 1; j < objects.size(); j++)
	//	{
	//		//�����蔻��`�F�b�N����
	//		HitCheckObject(objects[i], objects[j]);
	//	}
	//}
	

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{	
		if (enemy_count[HANE] > 0)
		{
			CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[/*GetRand(1)*/1]));
			enemy_count[HANE]--;
			enemy_Max--;
		}
		
	}

	//time_count++;

	//if (time_count >= 60)
	//{
	//	time_count = 0;
	//	if (enemy_Max > 0)
	//	{
	//		switch (GetRand(3))
	//		{

	//		case 0:
	//			if (enemy_count[HANE] > 0)
	//			{
	//				CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[/*GetRand(1)*/0]));
	//				enemy_count[0]--;
	//				enemy_Max--;
	//			}
	//			break;

	//		case 1:
	//			if (enemy_count[HANE] > 0)
	//			{
	//				CreateObject<Enemy>(Vector2D(Location_X[GetRand(1)], Location_Y[/*GetRand(1)*/1]));
	//				enemy_count[0]--;
	//				enemy_Max--;
	//			}
	//			break;

	//		case 2:
	//			if (enemy_count[HAKO] > 0)
	//			{
	//				CreateObject<Hakoteki>(Vector2D(Location_X[GetRand(1)], 430.0f));
	//				enemy_count[1]--;
	//				enemy_Max--;
	//			}
	//			break;

	//		case 3:
	//			if (enemy_count[HAPI] > 0)
	//			{
	//				CreateObject<Hapi>(Vector2D(Location_X[GetRand(1)], Location_Y[2]));
	//				enemy_count[2]--;;
	//				enemy_Max--;
	//			}
	//			break;

	//		}
	//	}
	//}
	

		for (int i = 1; i < objects.size(); i++)
		{
			if ((objects[i]->GetLocation().x < 0.0f) || (objects[i]->GetLocation().x > 640.0f))
			{
				if (objects[i]->GetType() < Object_Type && objects[i]->GetType() != Bomb)
				{
					delete_count++;
					//enemy_Max++;
					enemy_count[objects[i]->GetType()]++;
					objects.erase(objects.begin() + i);
				}		
			}	

			if (objects[i]->DeleteObject() == 1)
			{
				if (objects[i]->GetType() != Bomb)
				{
					enemy_Max++;
				}
				else if (objects[i]->GetType() == Bomb)
				{
					bom_count--;
				}
				
				objects.erase(objects.begin() + i);	
			}
		}
		

	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bom_count < 1)
		{
			CreateObject<Bom>(Vector2D(objects[0]->GetLocation()));
			bom_count++;
		}
	}
	
}

//�`�揈��
void Scene::Draw() const
{
	DrawRotaGraphF(320, 260, 0.73, 0, back_scene, TRUE);

	DrawFormatString(20, 20, GetColor(255, 255, 255), "���� : %d", time_count);

	DrawFormatString(20, 40, GetColor(255, 255, 255), "�G�̐� �F %d", enemy_count[0]);

	DrawFormatString(20, 60, GetColor(255, 255, 255), "�G�̐� �F %d", enemy_count[1]);

	DrawFormatString(20, 80, GetColor(255, 255, 255), "�G�̐� �F %d", enemy_count[2]);

	DrawFormatString(20, 100, GetColor(255, 255, 255), "�G�̍ő吔 �F %d", enemy_Max);

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

void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//	//�I�u�W�F�N�g�̋������擾
	//	Vector2D Hitlocation = a->GetLocation() - b->GetLocation();
	//	
	//	//�I�u�W�F�N�g�̓����蔻��̑傫�����擾
	//	Vector2D HitBoxSize = a->GetBoxSize() + b->GetBoxSize();
	//
	//	if ((fabs(Hitlocation.x) < HitBoxSize.x) && (fabs(Hitlocation.y) < HitBoxSize.y))
	//	{
	//		a->OnHitCollision(b);
	//		b->OnHitCollision(a);jd
	//	}

	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
 	
		if (a->GetType() == Bomb || b->GetType() == Bomb)
		{
			if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
			{
				//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
				a->OnHitCollision(b);
				b->OnHitCollision(a);
			}
		}
	
}

//void Scene::DeleteObject()
//{
//
//}