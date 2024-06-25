#pragma once

#include "../GameObject.h"
#include "../player/Bom.h"

class Enemy : public GameObject
{
protected:
	bool flip_flag;
	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	Vector2D velocity;		//�i�s����
	Vector2D Plus_Speed[3];	//�E�����ւ̈ړ����x
	Vector2D Minus_Speed[3];//�������ւ̈ړ����x
	int alpha;				//�G�̓����x
	int count;				//�t���[���J�E���g

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


private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

};

