#include "GameObject.h"
#include "DxLib.h"
#include "math.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	scale(0.0),
	radian(0.0),
	image(0),
	sound(0),
	object_type(0),
	delete_object(0),
	Hit(FALSE),
	count(0),
	Score_Point(0),
	SE(NULL)
{
}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/Images/haneteki1.png");
}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{

}

//�I������
void GameObject::Finalize()
{

}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	
}

//�ʒu���@�擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location += location;
}

//�����蔻��傫���擾����
Vector2D GameObject::GetBoxSize() const
{
	return scale;
}

//�I�u�W�F�N�g�̃^�C�v�擾����
int GameObject::GetType()
{
	return object_type;
}

//�����I�u�W�F�N�g���ǂ����̔��菈��
int GameObject::DeleteObject()
{
	return delete_object;
}

//Hit�擾����
bool GameObject::GetHit()
{
	return Hit;
}

//�G�̒e��Player�܂Ŕ�΂����߂̏���
Vector2D GameObject::GetDirection(Vector2D location_p, Vector2D location_b)
{
	float x = 0;
	float y = 0;
	float z = 0;
	Vector2D direction;

	x = ((location_p.x - location_b.x) * (location_p.x - location_b.x));
	y = ((location_p.y - location_b.y) * (location_p.y - location_b.y));
	z = sqrt(x + y);
	x = (location_p.x - location_b.x) / z;
	y = (location_p.y - location_b.y) / z;

	direction = Vector2D(x, y);
	return direction;
}

int GameObject::GetScorePoint()
{
	return Score_Point;
}

