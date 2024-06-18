#pragma once
#include "../GameObject.h"
#include <math.h>

class Bom : public GameObject
{
private:
	int bom_image;
	int animation_count;
	int count;
	int Bomcount;
	Vector2D velocity;
	

public:
	Bom();
	~Bom();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	
	void Movement();
	/*void Animation();*/
	Vector2D SetLocation();
	
	
};

