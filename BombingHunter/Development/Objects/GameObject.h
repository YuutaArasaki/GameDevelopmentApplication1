#pragma once

#include "../Utility/Vector2D.h"

#define HANE (0);
#define HAKO (1);
#define HAPI (2);
#define KIN  (3);
#define Enemy_Type (4);


//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;		//�ʒu���
	Vector2D scale;			//�傫��
	double radian;			//����
	int image;				//�`�悷��摜
	int sound;				//�Đ����鉹��
	int enemy_type;


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
};

