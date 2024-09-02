#pragma once
#include "EnemyBase.h"

class Pinky : public EnemyBase
{
public:
	void Initialize() override;

private:
	virtual void Move_Chase(Vector2D location) override;

};

