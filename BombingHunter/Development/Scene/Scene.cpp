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
Scene::Scene() : objects(), back_scene(), count(5)
{
	//X���W�̐ݒ�
	Location_X[0] = 0.0f;
	Location_X[1] = 640.0f;

	//Y���W�̐ݒ�
	Location_Y[0] = 200.0f;
	Location_Y[1] = 270.0f;
	Location_Y[2] = 350.0f;
	Location_Y[3] = 440.0f;


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

}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//for (int i = 0; i < objects.size(); i++)
	//{

	//		//�����蔻��`�F�b�N����
	//		HitCheckObject(objects[0], objects[i]);
	//	
	//}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}
	

	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		
		//�G�𐶐�����
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

//�`�揈��
void Scene::Draw() const
{
	DrawRotaGraphF(320, 260, 0.73, 0, back_scene, TRUE);

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
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}