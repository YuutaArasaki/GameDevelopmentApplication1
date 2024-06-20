#pragma once
#include "../GameObject.h"
#include <math.h>

class Bom : public GameObject
{
private:
	int bom_image;			//ボムの画像
	int animation_count;	//アニメーションカウント
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

