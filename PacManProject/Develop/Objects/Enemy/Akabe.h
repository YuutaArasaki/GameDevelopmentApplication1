#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
public:
	void Initialize() override;

private:
	void Move_Chase(float delta_second);
	void AnimationControl(float delta_second);
};

