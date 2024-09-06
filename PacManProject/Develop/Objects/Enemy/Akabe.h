#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	int f[4] = { 0,0,0,0 };
	int mini;
	int tp_x; //�꒣���X���W
	int tp_y; //�꒣���Y���W
	

public:
	void Initialize() override;

private:
	void Move_Teritory() override;		//�꒣�菈��
	virtual void Move_Chase(Vector2D location,Vector2D p_location) override;	//�ǐՏ����I����
	void SetDirection(eEnemyDirection d);		//�����ݒ菈��

};

