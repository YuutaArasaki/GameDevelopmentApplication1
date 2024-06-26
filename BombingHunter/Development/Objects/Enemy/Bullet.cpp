#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet() : animation_count(0),player(0)
{
	for (int i = 0; i < 4; i++)
	{
		Bullet_image[i] = NULL;
	}
}


Bullet::~Bullet()
{

}

//����������
void Bullet::Initialize()
{
	Bullet_image[0] = LoadGraph("Resource/Images/teki/hakoteki/Bullet1.png");
	Bullet_image[1] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff1.png");
	Bullet_image[2] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff2.png");
	Bullet_image[3] = LoadGraph("Resource/Images/teki/hakoteki/Bulleteff3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (Bullet_image[i] == -1)
		{
			throw ("Bullet�̉摜������܂���\n");
		}
	}
	
	//�I�u�W�F�N�g�^�C�v
	object_type = BULLET;

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫��
	scale = 20.0f;

	//�摜�̏����ݒ�
	image = Bullet_image[0];

	//�ړ��ʂ̐ݒ�
	velocity = 0.0f;
	
	if (player!=nullptr)
	{
		player_location = player->GetLocation();
		velocity = GetDirection(player_location, this->location);
	}

}

//�X�V����
void Bullet::Update()
{
	Movement();

	if (Hit == TRUE)
	{
		Animation();
	}
}

//�`�揈��
void Bullet::Draw() const
{
	DrawRotaGraph(location.x, location.y, 0.6, radian, image, TRUE);

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I������
void Bullet::Finalize()
{
	DeleteGraph(Bullet_image[0]);
	DeleteGraph(Bullet_image[1]);
	DeleteGraph(Bullet_image[2]);
	DeleteGraph(Bullet_image[3]);
}

//�����蔻��ʒm����
void Bullet::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->GetType() == PLAYER)
	{
		Hit = TRUE;
	}
	
}

//�ړ�����
void Bullet::Movement()
{
	if (location.y < 0)
	{
		delete_object = 1;
	}

	if (Hit != TRUE)
	{
		location += velocity;
	}
	
}

//�A�j���[�V��������
void Bullet::Animation()
{
	animation_count++;

	if (animation_count >= 5)
	{
		animation_count = 0;

		if (image == Bullet_image[0])
		{
			image = Bullet_image[1];
		}
		else if (image == Bullet_image[1])
		{
			image = Bullet_image[2];
		}
		else if (image == Bullet_image[2])
		{
			image = Bullet_image[3];
		}
		else if (image == Bullet_image[3])
		{
			delete_object = 1;
		}
	}
}

//�v���C���[�̃|�C���^�擾����
void Bullet::SetPlayer(Player* p)
{
	player = p;
}
