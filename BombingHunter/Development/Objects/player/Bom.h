#pragma once
#include "../GameObject.h"
#include <math.h>

class Bom : public GameObject
{
private:
	int bom_image;			//�{���̉摜
	int animation_count;	//�A�j���[�V�����J�E���g
	Vector2D velocity;
	bool left;
	bool right;
	

public:
	Bom();
	~Bom();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	
	void Movement();
	Vector2D SetLocation();
	
	
};

