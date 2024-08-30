#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	bool direction_flag;
	int f[4] = { 0,0,0,0 };
	int mini;
	int teritory_panel[4][2] = { {26,1},
								 {26,5},
								 {21,1},
								 {21,5} };//エネミーの縄張り位置格納配列
public:
	void Initialize() override;

private:
	void Move_Teritory(float delta_second) override;
	void Move_Chase(float delta_second) override;
	void AnimationControl(float delta_second);
	void SetPlayer(Player* p);
};

