#pragma once
#include "../../Utility/Vector2D.h"

class Blast
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
	/*virtual void Update();*/
	virtual void Draw(float location_x, float location_y) const;
	virtual void Finalize();

	
	void Animation();
	
};