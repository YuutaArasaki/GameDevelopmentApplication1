#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	int f[4] = { 0,0,0,0 };
	int mini;
	int tp_x; //�꒣���X���W
	int tp_y; //�꒣���Y���W

	int teritory_panel[4][2] = { {21,1},
								 {26,1},
								 {26,5},
								 {21,5} };//�G�l�~�[�̓꒣��ʒu�i�[�z��
public:
	void Initialize() override;

private:
	void Move_Teritory() override;
	virtual void Move_Chase(Vector2D location) override;
	void AnimationControl(float delta_second);
	void SetPlayer(Player* p);
	void Set_Direction(eEnemyDirection d);
};

