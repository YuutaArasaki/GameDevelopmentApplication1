#pragma once
#include "../../Utility/Vector2D.h"
#include "../GameObject.h"

class Blast : public GameObject
{
private:
	int image;
	int blast_image[3];
	int animation_count;
	int count;
	


public:
	Blast();
	~Blast();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const override;
	virtual void Finalize();

	
	void Animation();
	
};