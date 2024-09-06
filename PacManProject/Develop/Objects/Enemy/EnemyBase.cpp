#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "Akabe.h"
#include "Pinky.h"
#include "Aosuke.h"
#include "Guzuta.h"
#include "math.h"
#include "../../Utility/InputManager.h"

EnemyBase::EnemyBase() : speed(49.5f),enemy_state(eEnemyState::TERITORY),player(nullptr),
velocity(0.0f),direction(eEnemyDirection::right),animation_time(0.0f),
animation_count(0),flash_count(0),flash_flag(false),state_time(0.0f),enemy_level(0),
enemy_type(),mini(0),direction_flag(true),state_flag(false),enemy_nest(Vector2D(13,15))
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

	z_layer = 5;

	
	teritory_panel[0] = Vector2D(21,1);
	teritory_panel[1] = Vector2D(26, 5);
	
}

void EnemyBase::Update(float delta_second)
{
	
	AnimationControl(delta_second);
	Movement(delta_second);
	State_Change(delta_second);

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	if (enemy_state != die)
	{
		__super::Draw(screen_offset);
	}
	
	 
	Vector2D graph_location = location + screen_offset;
	
	if (enemy_state == die || enemy_state != FEAR)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
	
}
	

void EnemyBase::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	
	// ���������I�u�W�F�N�g���v���C���[��������
	if (hit_object->GetCollision().object_type == eObjectType::player && enemy_state == FEAR)
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
		velocity.x = 0;
		break;
	case down:
		velocity.y = 1.0f;
		velocity.x = 0;
		break;
	case left:
		velocity.x = -1.0f;
		velocity.y = 0;
		break;
	case right:
		velocity.x = 1.0f;
		velocity.y = 0;
		break;
	default:
		velocity = 0.0f;
		break;
	}

	switch (enemy_state)
	{
	case TERITORY:
		Move_Teritory();
		break;

	case CHASE:
		Move_Chase(this->location,player->GetLocation());
		break;

	case FEAR:
		Move_Fear(delta_second);
		break;

	case idle:
		Move_Idle();
		break;

	case die:
		Move_Die(delta_second);
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

	int i = 0;
	
	location += velocity * speed * delta_second;
}

void EnemyBase::Move_Teritory()
{

	int ex = 0;
	int	ey = 0;
	int x, y, h, n = 0;
	Vector2D tp;

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);
	StageData::ConvertToIndex(this->location, ey, ex);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE } };

	tp = teritory_panel[0];

	if (tp.x == ex && tp.y == ey)
	{
		tp = teritory_panel[1];
	}
	
	if (StageData::GetPanelData(this->location) == ePanelID::BRANCH)
	{
		if (panel[UP] == ret[UP] && direction != down)
		{
			ey += -1;
			x = (tp.x - ex) * (tp.x - ex);
			y = (tp.y - ey) * (tp.y - ey);
			h = x + y;
			n = (tp.x - ex) + (tp.y - ey);
			ey += 1;
			f[up] = n + h;
		}
		else
		{
			f[up] = 0;
		}

		if (panel[RIGHT] == ret[RIGHT] && direction != left)
		{
			ex += 1;
			x = (tp.x - ex) * (tp.x - ex);
			y = (tp.y - ey) * (tp.y - ey);
			h = x + y;
			n = (tp.x - ex) + (tp.y - ey);
			ex += -1;
			f[right] = n + h;
		}
		else
		{
			f[right] = 0;
		}

		if (panel[DOWN] == ret[DOWN] && direction != up)
		{
			ey += 1;
			x = (tp.x - ex) * (tp.x - ex);
			y = (tp.y - ey) * (tp.y - ey);
			h = x + y;
			n = (tp.x - ex) + (tp.y - ey);
			ey += -1;
			f[down] = n + h;
		}
		else
		{
			f[down] = 0;
		}

		if (panel[LEFT] == ret[LEFT] && direction != right)
		{
			ex += -1;
			x = (tp.x - ex) * (tp.x - ex);
			y = (tp.y - ey) * (tp.y - ey);
			h = x + y;
			n = (tp.x - ex) + (tp.y - ey);
			ex += 1;
			f[left] = n + h;
		}
		else
		{
			f[left] = 0;
		}

		mini = 0;

		int j;

		for (int i = 0; i < 4; i++)
		{
			if (mini == 0)
			{
				mini = f[i];
				j = i;
			}

			if (mini > f[i] && f[i] > 0)
			{
				mini = f[i];

				j = i;

			}
		}

		switch (j)
		{
		case up:
			SetDirection(up);
			break;
		case right:
			SetDirection(right);
			break;
		case down:
			SetDirection(down);
			break;
		case left:
			SetDirection(left);
			break;
		}
	}

	if (StageData::GetPanelData(this->location) != ePanelID::BRANCH)
	{
		direction_flag = true;
	}
}

void EnemyBase::Move_Chase(Vector2D location, Vector2D p_location)
{
	
	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	int px, py, ex, ey, x, y, h, n, j = 0;
	Vector2D a,b;
	
	if (StageData::GetPanelData(this->location) == ePanelID::BRANCH)
	{
		StageData::ConvertToIndex(player->GetLocation(), py, px);
		StageData::ConvertToIndex(this->GetLocation(), ey, ex);

		if (panel[UP] == ret[UP] && direction != down)
		{
			ey += -1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[up] = n + h;
			ey += 1;
		}
		else
		{
			f[up] = 0;
		}

		if (panel[RIGHT] == ret[RIGHT] && direction != left)
		{
			ex += 1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[right] = n + h;
			ex += -1;
		}
		else
		{
			f[right] = 0;
		}

		if (panel[DOWN] == ret[DOWN] && direction != up)
		{
			ey += 1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[down] = n + h;
			ey += -1;
		}
		else
		{
			f[down] = 0;
		}

		if (panel[LEFT] == ret[LEFT] && direction != right)
		{
			ex += -1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[left] = n + h;
			ex += 1;
		}
		else
		{
			f[left] = 0;
		}

		mini = 0;

		for (int i = 0; i < 4; i++)
		{
			if (mini == 0)
			{
				mini = f[i];
				j = i;
			}

			if (mini > f[i] && f[i] > 0)
			{
				mini = f[i];

				j = i;

			}
		}

		switch (j)
		{
		case up:
			SetDirection(up);
			break;
		case right:
			SetDirection(right);
			break;
		case down:
			SetDirection(down);
			break;
		case left:
			SetDirection(left);
			break;
		}
	}

	if (StageData::GetPanelData(this->location) != ePanelID::BRANCH)
	{
		direction_flag = true;
	}
	
}
void EnemyBase::Move_Die(float delta_second)
{
	int x, y = 0;
	StageData::ConvertToIndex(this->GetLocation(), y, x);
	SetDirection(StartRoute(enemy_nest));

	if (enemy_nest.x == x && enemy_nest.y == y)
	{
		enemy_state = idle;
	}
}

void EnemyBase::Move_Fear(float delta_second)
{
	
}

void EnemyBase::Move_Idle()
{
	int ex, ey = 0;

	Vector2D target = Vector2D(13,11);		//�Q�[�g�̓����̃p�l���ʒu

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);
	StageData::ConvertToIndex(this->GetLocation(), ey, ex);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	//idle��Ԏ��̓����i�㉺�ړ��j
	if (state_flag == false)
	{
		if (panel[UP] != ret[UP])
		{
			 SetDirection(down);
		}
	
		if (panel[DOWN] != ret[DOWN])
		{
			SetDirection(up);
		}
	}


	//��萔�p�b�N�}�����a��H�ׂ�ƃG�l�~�[���O�ɏo�鏈��
	switch (enemy_type)
	{
	case PINKY:
		if (player->GetFoodCount() > 30)
		{
			state_flag = true;

			if (ex == target.x && target.y == ey)
			{
				enemy_state = TERITORY;
			}

			if (ex > target.x)
			{
				SetDirection(left);
			}
			else if (ex < target.x)
			{
				SetDirection(right);
			}

			if (target.x == ex && target.y != ey)
			{
				SetDirection(up);
			}
			else if (target.x == ex && target.y == ey)
			{
				direction = StartRoute(teritory_panel[0]);
				SetDirection(StartRoute(teritory_panel[0]));
			}
			break;

	case AOSUKE:
		if (player->GetFoodCount() > 60)
		{
			state_flag = true;

			if (ex == target.x && target.y == ey)
			{
				enemy_state = TERITORY;
			}

			if (ex > target.x)
			{
				SetDirection(left);
			}
			else if (ex < target.x)
			{
				SetDirection(right);
			}

			if (target.x == ex && target.y != ey)
			{
				SetDirection(up);
			}
			else if (target.x == ex && target.y == ey)
			{
				direction = StartRoute(teritory_panel[0]);
				SetDirection(StartRoute(teritory_panel[0]));
			}
		}
		break;

	case GUZUTA:
		if (player->GetFoodCount() > 90)
		{
			state_flag = true;

			if (ex == target.x && target.y == ey)
			{
				enemy_state = TERITORY;
			}

			if (ex > target.x)
			{
				SetDirection(left);
			}
			else if (ex < target.x)
			{
				SetDirection(right);
			}

			if (target.x == ex && target.y != ey)
			{
				SetDirection(up);
			}
			else if (target.x == ex && target.y == ey)
			{
				direction = StartRoute(teritory_panel[0]);
				SetDirection(StartRoute(teritory_panel[0]));
			}
		}
			break;
		}
	}
	if (StageData::GetPanelData(this->location) != ePanelID::BRANCH)
	{
		direction_flag = true;
	}
}
void EnemyBase::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (enemy_state != FEAR)
	{ 
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
	else
	{
		if (flash_flag == false)
		{	
			//�C�W�P��Ԃ̉摜
			image = move_animation[17];
		}
		else
		{
			if (animation_time >= (delta_second * 144))
			{
				animation_time = 0.0f;
				animation_count++;

				if (animation_count >= 2)
				{
					animation_count = 0;
					flash_count++;	
				}
			
				image = move_animation[17 + animation_num[animation_count]];
			}
		}
			
		if (flash_count > 6)
		{
			flash_flag = false;
		}
			
	}
}


void EnemyBase::State_Change(float delta_second)
{
	state_time += delta_second;

	if (enemy_state == TERITORY)
	{
		//��萔���Ԃ�����State��ύX���鏈��
		if (state_time >= (delta_second * 60) * 4.5)
		{
			state_time = 0;
			enemy_state = CHASE;
		}

		if (player->GetPowerUp() == true)
		{
			state_time = 0;
			enemy_state = FEAR;
		}
	}
	

	if (enemy_state == CHASE)
	{
		if (state_time >= (delta_second * 60) * 15)
		{
			state_time = 0;
			enemy_state = TERITORY;
		}

		if (player->GetPowerUp() == true)
		{
			state_time = 0;
			enemy_state = FEAR;
		}
	}
	

	if (enemy_state == FEAR)
	{
		if (state_time >= (delta_second * 144) * 20 && flash_count < 6)
		{
			flash_flag = true;
		}
		else if(flash_flag == false && flash_count > 6)
		{
			flash_count = 0;
			player->SetPowerDown();
			state_time = 0;
			enemy_state = TERITORY;
		}
	}

}


eEnemyType EnemyBase::Get_EnemyType()
{
	return enemy_type;
}

float EnemyBase:: Enemy_Speed()
{
	return speed;
}

void EnemyBase::SetEnemyType(int t)
{
	switch (t)
	{
	case 1:
		enemy_type = PINKY;
		enemy_state = idle;
		teritory_panel[0] = Vector2D(6, 1);		//�^�C�v�ʂ̃G�l�~�[�̓꒣��ʒu�̐ݒ�
		teritory_panel[1] = Vector2D(1, 5);
		break;

	case 2:
		enemy_type = AOSUKE;
		enemy_state = idle;
		teritory_panel[0] = Vector2D(26, 29);
		teritory_panel[1] = Vector2D(18, 26);
		break;
		
	case 3:
		enemy_type = GUZUTA;
		enemy_state = idle;
		teritory_panel[0] = Vector2D(1, 29);
		teritory_panel[1] = Vector2D(9, 26);
		break;

	}
	
}

void EnemyBase::SetDirection(eEnemyDirection d)
{
	int ex, ey = 0;
	StageData::ConvertToIndex(this->GetLocation(), ey, ex);

	int x = (int)location.x;
	int y = (int)location.y;
	Vector2D a,b;

	switch (d)
	{
	case up:
		a.x = (int)(ex + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;	//�p�l���̒��S���W���擾
		b.x = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
		if (direction_flag == true)	//���p�ɋȂ��鏈��
		{
			if (x == a.x || x == b.x)		//�p�l���̒��S���W�ŕ�����ς��鏈��
			{
				direction = up;
				direction_flag = false;
			}
		}
		break;
	case right:
		a.y = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
		b.y = (int)(ey + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
		if (direction_flag == true)
		{
			if (y == a.y || y == b.y)
			{
				direction = right;
				direction_flag = false;
			}
		}
		break;
	case down:
		a.x = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
		b.x = (int)(ex + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
		if (direction_flag == true)
		{
			if (x == a.x || x == b.x)
			{
				direction = down;
				direction_flag = false;
			}
		}
		break;


	case left:
		a.y = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
		b.y = (int)(ey + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
		if (direction_flag == true)
		{
			if (y == a.y || y == b.y)
			{
				direction = left;
				direction_flag = false;
			}
		}
		break;
	}
}

//�G�l�~�[���ҋ@��Ԃ���ڍs�����Ƃ��̃��[�g�����߂鏈��
eEnemyDirection EnemyBase::StartRoute(Vector2D tg)
{
	int ex = 0;
	int	ey = 0;
	int x, y, h, n = 0;
	Vector2D tp;

	

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::WALL},
		{ eAdjacentDirection::DOWN, ePanelID::WALL},
		{ eAdjacentDirection::LEFT, ePanelID::WALL},
		{ eAdjacentDirection::RIGHT, ePanelID::WALL} };


	tp = tg;

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);
	StageData::ConvertToIndex(this->location, ey, ex);

	if (panel[UP] != ret[UP] && direction != down)
	{
		ey += -1;
		x = (tp.x - ex) * (tp.x - ex);
		y = (tp.y - ey) * (tp.y - ey);
		h = x + y;
		n = (tp.x - ex) + (tp.y - ey);
		ey += 1;
		f[up] = n + h;
	}
	else
	{
		f[up] = 0;
	}

	if (panel[RIGHT] != ret[RIGHT] && direction != left)
	{
		ex += 1;
		x = (tp.x - ex) * (tp.x - ex);
		y = (tp.y - ey) * (tp.y - ey);
		h = x + y;
		n = (tp.x - ex) + (tp.y - ey);
		ex += -1;
		f[right] = n + h;
	}
	else
	{
		f[right] = 0;
	} 

	if (panel[DOWN] != ret[DOWN] && direction != up)
	{
		ey += 1;
		x = (tp.x - ex) * (tp.x - ex);
		y = (tp.y - ey) * (tp.y - ey);
		h = x + y;
		n = (tp.x - ex) + (tp.y - ey);
		ey += -1;
		f[down] = n + h;
	}
	else
	{
		f[down] = 0;
	}

	if (panel[LEFT] != ret[LEFT] && direction != right)
	{
		ex += -1;
		x = (tp.x - ex) * (tp.x - ex);
		y = (tp.y - ey) * (tp.y - ey);
		h = x + y;
		n = (tp.x - ex) + (tp.y - ey);
		ex += 1;
		f[left] = n + h;
	}
	else
	{
		f[left] = 0;
	}

mini = 0;

	int j;

	for (int i = 0; i < 4; i++)
	{
		if (mini == 0)
		{
			mini = f[i];
			j = i;
		}

		if (mini > f[i] && f[i] > 0)
		{
			mini = f[i];

			j = i;

		}
	}

	switch (j)
	{
	case 0:
		return up;
		break;

	case 1:
		return right;
		break;

	case 2:
		return down;
		break;

	case 3:
		return left;
		break;
	}
}


