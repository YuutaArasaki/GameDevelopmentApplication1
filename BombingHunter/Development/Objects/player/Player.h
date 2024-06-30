#pragma once

#include "../GameObject.h"
#include "../../Scene/Scene.h"

class Player  :  public GameObject
{
private:
	Scene* scene;
	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int filp_flag;			//���]�t���O
	int time;
	


public:
	Player();
	~Player();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	
	Vector2D GetLocation();
	

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();

	

	
};

