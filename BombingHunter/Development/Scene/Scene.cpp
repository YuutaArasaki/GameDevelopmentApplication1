#include "Scene.h"
#include "DxLib.h"

#include "../Objects/player/Player.h"
#include "../Objects/Enemy/Enemy.h"

//�R���X�g���N�^
Scene::Scene() : objects(), back_scene()
{

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
	//�G�𐶐�����
	CreateObject<Enemy>(Vector2D(320.0f, 400.0f));

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