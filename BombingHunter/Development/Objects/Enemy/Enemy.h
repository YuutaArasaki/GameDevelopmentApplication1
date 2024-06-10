#pragma once

#include "../GameObject.h"
#include "../player/Bom.h"

class Enemy : public GameObject
{
private:
	int animation[2];	//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	Vector2D velocity;		//�i�s����

public:
	Enemy();
	~Enemy();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I������
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	 Vector2D Location_X();

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

	void Set_Velocity();

};

