#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "Pinky.h"

EnemyBase::EnemyBase() : speed(),enemy_state(eEnemyState::TERITORY),player(nullptr),teritory_location(),
velocity(0.0f),direction(eEnemyDirection::left),animation_time(0.0f),
animation_count(0),flash_count(0),state_time(0.0f),enemy_level(0),enemy_type()
{
}

EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation =rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);


	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	AnimationControl(delta_second);
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}


	// ���������I�u�W�F�N�g���v���C���[��������
	if (hit_object->GetCollision().object_type == eObjectType::player && Get_EnemyType() == FEAR)
	{
		enemy_state = eEnemyState::die;
	}
}

eEnemyState EnemyBase::GetEnemyState()
{
	return enemy_state;
}

void EnemyBase::Set_Player(Player* p)
{
	 player = p;
}

void EnemyBase::Movement(float delta_second)
{
	// �i�s�����̈ړ��ʂ�ǉ�
	switch (direction)
	{
	case up:
		velocity.y = -1.0f;
		break;
	case down:
		velocity.y = 1.0f;
		break;
	case left:
		velocity.x = -1.0f;
		break;
	case right:
		velocity.x = 1.0f;
		break;
	default:
		velocity = 0.0f;
		break;
	}

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
}

void EnemyBase::Move_Teritory(float delta_second)
{

}

void EnemyBase::Move_Chase(float delta_second)
{

}
void EnemyBase::Move_Die(float delta_second)
{

}

void EnemyBase::Move_Fear(float delta_second)
{

}

void EnemyBase::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		int type_num = Get_EnemyType();

		if (0 <= type_num && type_num < 4)
		{
			image = move_animation[(type_num * 2) + animation_num[animation_count]];
		}
	

		switch (direction)
		{
		case up:
			eye_image = eye_animation[up];
			break;
		case right:
			eye_image = eye_animation[right];
			break;
		case down:
			eye_image = eye_animation[down];
			break;
		case left:
			eye_image = eye_animation[left];
			break;
		}

	}

}

void EnemyBase::State_Change(float delta_second)
{

}


eEnemyType EnemyBase::Get_EnemyType()
{
	return enemy_type;
}

float EnemyBase:: Enemy_Speed()
{
	return speed;
}