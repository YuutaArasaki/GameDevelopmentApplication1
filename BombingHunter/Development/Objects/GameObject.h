#pragma once

#include "../Utility/Vector2D.h"

typedef enum
{
	HANE,
	HAKO,
	HAPI,
	KIN,
	EnemyType,
	BOM,
	PLAYER,
	BLAST,
	BULLET,
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
	int object_type;		//�I�u�W�F�N�g�̎��
	int delete_object;		//�I�u�W�F�N�g�̏���
	bool Hit;				//�I�u�W�F�N�g��Hit�������ǂ���
	int count;				//�t���[���J�E���g
	int Score_Point;		//�e�G�̃X�R�A
	int Score_image;		//�G��|�����Ƃ��ɕ\������X�R�A�摜
	int SE;					//SE

public:
	GameObject();
	~GameObject();
	virtual void Initialize();	//�������ݒ�
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�I�u�W�F�N�g�̃^�C�v�擾
	virtual int GetType();

	//�I�u�W�F�N�g�̃q�b�g�擾
	virtual bool GetHit();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫���擾����
	Vector2D GetBoxSize() const;

	//�����I�u�W�F�N�g���ǂ����̔��菈��
	int DeleteObject();

	//�e�L�̒e���g���p�C���b�g�̕����ɔ�΂�����
	Vector2D GetDirection(Vector2D location_p,Vector2D location_b);

	//�e�G�̃X�R�A���擾���鏈��
	int GetScorePoint();
	
};

