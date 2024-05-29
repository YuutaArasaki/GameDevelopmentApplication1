#pragma once
#include "Enemy.h"

class Kinnoteki : public Enemy
{
	private:
		int animation_image_count; //�A�j���[�V�����摜�J�E���g
		int animation[5];	//�A�j���[�V�����摜
		int animation_count;	//�A�j���[�V��������
		Vector2D velocity;		//�i�s����

	public:
		Kinnoteki();
		~Kinnoteki();

		//����������
		virtual void Initialize() override;
		//�X�V����
		virtual void Update() override;
		//�`�揈��
		virtual void Draw() const override;
		//�I������
		virtual void Finalize() override;

		//�����蔻��ʒm����
		virtual void OnHitCollision(GameObject * hit_object) override;

	private:
		//�ړ�����
		void Movement();
		//�A�j���[�V��������
		void AnimationControl();
};

