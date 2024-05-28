#pragma once
#include "../GameObject.h"

class Bom : public GameObject
{
private:
	int bom_image[4];
	int animation_count;
	int count;
	

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
	void BomHit();
	
};

