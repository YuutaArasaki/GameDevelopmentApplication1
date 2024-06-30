#pragma once
#include "../../Objects/GameObject.h"
#include "../player/Player.h"


class Bullet : public GameObject
{
	Player* player;
	int Bullet_image[4];		//�e�̉摜
	int animation_count;		//�e�̃A�j���[�V�����t���[���J�E���g
	Vector2D velocity;			//�e�̈ړ���
	Vector2D player_location;	//�v���C���[�i�g���p�C���b�g�j�̈ʒu���W
	


public:
	Bullet();		//�R���X�g���N�^
	~Bullet();		//�f�X�g���N�^

	//����������
	virtual void  Initialize();

	//�X�V����
	virtual void Update();

	//�`�揈��
	virtual void Draw() const;
	
	//�I������
	virtual void Finalize();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�v���C���[�̃|�C���^�擾����
	void SetPlayer(Player* p);

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void Animation();

};

