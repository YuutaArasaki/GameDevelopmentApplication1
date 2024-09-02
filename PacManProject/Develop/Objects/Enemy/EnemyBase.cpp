#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "Akabe.h"
#include "Pinky.h"
#include "Aosuke.h"
#include "Guzuta.h"
#include "math.h"

EnemyBase::EnemyBase() : speed(40.0f),enemy_state(eEnemyState::TERITORY),player(nullptr),
velocity(0.0f),direction(eEnemyDirection::left),animation_time(0.0f),
animation_count(0),flash_count(0),flash_flag(false),state_time(0.0f),enemy_level(0),
enemy_type(),mini(0),direction_flag(true),tp_x(0),tp_y(0)
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
	
	int px, py, ex, ey = 0;

	StageData::ConvertToIndex(player->GetLocation(), py, px);
	if (enemy_type == AKABE)
	{
		StageData::ConvertToIndex(this->GetLocation(), ey, ex);
		DrawFormatString(200, 40, 0xffffff, "EX : %d EY : %d", ex,ey);
	}
	

	DrawFormatString(10, 40, 0xffffff, "PX : %d PY : %d", px, py);
	
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
		Move_Chase(delta_second);
		break;

	case FEAR:
		Move_Fear(delta_second);
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
	

	switch (enemy_type)
	{
	case AKABE:
		int teritory_panel[4][2] = { {21,1},
									 {26,1},
									 {26,5},
									 {21,5} };
		break;

	case PINKY:
		int teritory_panel[4][2] = { {21,1},
									 {26,1},
									 {26,5},
									 {21,5} };
		break;
	}
	

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);
	StageData::ConvertToIndex(this->location, ey, ex);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE } };


	if (tp_x == 0 && tp_y == 0)
	{
		tp_x = teritory_panel[0][0];
		tp_y = teritory_panel[0][1];
	}

	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[1][0];
		tp_y = teritory_panel[1][1];
	}
	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[2][0];
		tp_y = teritory_panel[2][1];
	}
	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[3][0];
		tp_y = teritory_panel[3][1];
	}
	else if (tp_x == ex && tp_y == ey)
	{
		tp_x = 0;
		tp_y = 0;
	}
	
	if (StageData::GetPanelData(this->location) == ePanelID::BRANCH)
	{
		if (panel[UP] == ret[UP] && direction != down)
		{
			ey += -1;
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
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
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
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
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
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
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
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

void EnemyBase::Move_Chase(Vector2D location)
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

}

void EnemyBase::Move_Fear(float delta_second)
{
	/*int a, x, y = 0;
	Vector2D TG;

	teritory_location = player->GetLocation() * -1;

	x = (location.x - teritory_location.x) * (location.x - teritory_location.x);
	y = (location.y - teritory_location.y) * (location.y - teritory_location.y);
	a = sqrt(x + y);
	x = (location.x - teritory_location.x) / a;
	y = (location.y - teritory_location.y) / a;

	TG = Vector2D(x, y);

	velocity = TG;*/
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
		if (state_time >= (delta_second * 60) * 4.5)
		{
			/*state_time = 0;
			enemy_state = CHASE;*/
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
		/*EnemyType()->Initialize();*/
		break;

	case 2:
		enemy_type = AOSUKE;
		/*EnemyType()->Initialize();*/
		break;
		
	case 3:
		enemy_type = GUZUTA;
		/*EnemyType()->Initialize();*/
		break;

	default:
		enemy_type = AKABE;
		EnemyType()->Initialize();
		break;
	}
	
}

EnemyBase* EnemyBase:: EnemyType()
{
	switch (enemy_type)
	{
	case AKABE:
		return dynamic_cast<EnemyBase*>(new Akabe());
		break;

	case PINKY:
		return dynamic_cast<EnemyBase*>(new Pinky());
		break;

	case AOSUKE:
		return dynamic_cast<EnemyBase*>(new Aosuke());
		break;

	case GUZUTA:
		return dynamic_cast<EnemyBase*>(new Guzuta());
		break;
	}
}

void EnemyBase::Set_TeritoryPanel()
{
	switch(enemy_type)
	{
	case AKABE:
		
		break;
		
	case PINKY:
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
			if (x == a.x || x == b.x)
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

void EnemyBase::ShortRoute()
{
	int px, py, ex, ey, x, y, h, n, j = 0;

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(location);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	StageData::ConvertToIndex(player->GetLocation(), py, px);
	StageData::ConvertToIndex(this->GetLocation(), ey, ex);

	if (panel[UP] == ret[UP] && direction != down)
	{
		ey += -1;
		x = (px - ex) * (px - ex);
		y = (py - ey) * (py - ey);
		h = x + y;
		n = (px - ex) + (py - ey);
		f[up] += n + h;
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
		f[right] += n + h;
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
		n += (px - ex) + (py - ey);
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
		f[left] += n + h;
		ex += 1;
	}
	else
	{
		f[left] = 0;
	}
}

Vector2D EnemyBase::Set_location()
{
	return location;
}