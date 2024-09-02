#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	int f[4] = { 0,0,0,0 };
	int mini;
	int tp_x; //縄張りのX座標
	int tp_y; //縄張りのY座標

	int teritory_panel[4][2] = { {21,1},
								 {26,1},
								 {26,5},
								 {21,5} };//エネミーの縄張り位置格納配列
public:
	void Initialize() override;

private:
	void Move_Teritory() override;
	virtual void Move_Chase(Vector2D location) override;
	void AnimationControl(float delta_second);
	void SetPlayer(Player* p);
	void Set_Direction(eEnemyDirection d);
};

