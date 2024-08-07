#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "Akabe.h"
#include "Pinky.h"
#include "Aosuke.h"
#include "Guzuta.h"
#include "math.h"

EnemyBase::EnemyBase() : speed(40.0f),enemy_state(eEnemyState::TERITORY),player(nullptr),teritory_location(),
velocity(0.0f),direction(eEnemyDirection::left),animation_time(0.0f),
animation_count(0),flash_count(0),flash_flag(false),state_time(0.0f),enemy_level(0),
enemy_type()
{
}

EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation =rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);


	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	
}

void EnemyBase::Update(float delta_second)
{
	
	AnimationControl(delta_second);
	Movement(delta_second);
	State_Change(delta_second);

}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
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
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}


	// 当たったオブジェクトがプレイヤーだったら
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
	
	// 進行方向の移動量を追加
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

	Move_Fear(delta_second);

	switch (enemy_state)
	{
	case TERITORY:
		/*Move_Teritory(delta_second);*/
		break;

	case CHASE:
		Move_Chase(delta_second);
		break;
	}
	// 画面外に行ったら、反対側にワープさせる
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

	location += velocity * speed * delta_second;
}

void EnemyBase::Move_Teritory(float delta_second)
{
	direction = right;
}

void EnemyBase::Move_Chase(float delta_second)
{
	/*EnemyType()->Move_Chase(delta_second);*/
	float a, x, y = 0.0f;
	Vector2D tg;

	x = (player->GetLocation().x - location.x) * (player->GetLocation().x - location.x);
	y = (player->GetLocation().y - location.y) * (player->GetLocation().y - location.y);
	a = sqrt(x + y);
	x = (player->GetLocation().x - location.x) / a;
	y = (player->GetLocation().y - location.y) / a;
	tg = Vector2D(x, y);

	velocity = tg;
}
void EnemyBase::Move_Die(float delta_second)
{

}

void EnemyBase::Move_Fear(float delta_second)
{
	int a, x, y = 0;
	Vector2D TG;

	teritory_location = player->GetLocation() * -1;

	x = (location.x - teritory_location.x) * (location.x - teritory_location.x);
	y = (location.y - teritory_location.y) * (location.y - teritory_location.y);
	a = sqrt(x + y);
	x = (location.x - teritory_location.x) / a;
	y = (location.y - teritory_location.y) / a;

	TG = Vector2D(x, y);

	location + TG;
}

void EnemyBase::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
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
			// 画像の設定
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
			//イジケ状態の画像
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
		break;

	case 2:
		enemy_type = AOSUKE;
		break;
		
	case 3:
		enemy_type = GUZUTA;
		break;

	default:
		enemy_type = AKABE;
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