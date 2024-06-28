#pragma once
#include "../GameObject.h"
#include <math.h>

class Bom : public GameObject
{
private:
	int bom_image;			//�{���̉摜
	int animation_count;	//�A�j���[�V�����J�E���g
	Vector2D velocity;		//�i�s����
	bool left;				//���e�̕����i�E�j
	bool right;				//���e�̕����i���j
	

public:
	Bom();		//�R���X�g���N�^
	~Bom();		//�f�X�g���N�^

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I������
	virtual void OnHitCollision(GameObject* hit_object) override;	//�����蔻��ʒm����
	
	void Movement();		//�ړ�����
};

