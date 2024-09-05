#pragma once
#include "EnemyBase.h"

class Aosuke : public EnemyBase
{
public:
	void Initialize() override;

private:
virtual	void Move_Chase(Vector2D location, Vector2D p_location) override;

};

