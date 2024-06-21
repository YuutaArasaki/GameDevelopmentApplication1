#pragma once
#include "../../Objects/GameObject.h"
#include "../player/Player.h"


class Bullet : public GameObject
{
	Player* player;
	int Bullet_image[4];
	int animation_count;
	Vector2D velocity;
	Vector2D player_location;

public:
	Bullet();
	~Bullet();

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

	void SetPlayer(Player* p);

private:
	void Movement();

	void Animation();

	/*Vector2D GetDirection(Vector2D location_p, Vector2D location_b);*/
};

