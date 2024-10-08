#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	int f[4] = { 0,0,0,0 };
	int mini;
	int tp_x; //縄張りのX座標
	int tp_y; //縄張りのY座標
	

public:
	void Initialize() override;

private:
	void Move_Teritory() override;		//縄張り処理
	virtual void Move_Chase(Vector2D location,Vector2D p_location) override;	//追跡処理紀処理
	void SetDirection(eEnemyDirection d);		//方向設定処理

};

