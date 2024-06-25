#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"
#include "../Utility/Vector2D.h"



class Scene
{
private:
	std::vector<GameObject*> objects;	
	int back_scene;						//�w�i�摜
	int count;							//�Q�[���̃t���[���J�E���g
	float Location_X[2];				//X���W
	float Location_Y[5];				//Y���W
	int enemy_count[3];					//�e�G���Ƃ̍ő�o����
	int enemy_Max;						//�G�̍ő�o����
	int enemy_timecount;				//�G�̏o�����銴�o�̕b���J�E���g
	int bom_Max;						//���e�̏o���鐔
	int GameTime;						//�Q�[���̐�������
	int Font[10];
	

public:
	Scene();		//�R���X�g���N�^
	~Scene();		//�f�X�g���N�^

	void Initialize();	//����������
	void Update();		//�X�V����
	void Draw() const;	//�`�揈��
	void Finalize();	//�I������

private:

	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);
		//����������
		new_object->Initialize();
		

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};

