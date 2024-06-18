#pragma once

#include "../Utility/Vector2D.h"

typedef enum
{
	HANE,
	HAKO,
	HAPI,
	KIN,
	Bomb,
	PLAYER,
	BLAST,
	Object_Type, 
}TYPE;
 


//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;		//�ʒu���
	Vector2D scale;			//�傫��
	double radian;			//����
	int image;				//�`�悷��摜
	int sound;				//�Đ����鉹��
	int object_type;			//�I�u�W�F�N�g�̎��
	int delete_object;
	

public:
	GameObject();
	~GameObject();
	virtual void Initialize();	//�������ݒ�
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	virtual int GetType();

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);
	//�����蔻��̑傫���擾����
	Vector2D GetBoxSize() const;

	int DeleteObject();
};

