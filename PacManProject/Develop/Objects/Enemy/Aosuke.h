#pragma once
#include "EnemyBase.h"

class Aosuke : public EnemyBase
{
public:
	void Initialize() override;

private:
	void Move_Chase(float delta_second) override;

};

