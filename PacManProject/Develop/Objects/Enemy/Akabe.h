#pragma once
#include "EnemyBase.h"

class Akabe : public EnemyBase
{
private:
	int f[4] = { 0,0,0,0 };
	int mini;
	int tp_x; //“ê’£‚è‚ÌXÀ•W
	int tp_y; //“ê’£‚è‚ÌYÀ•W
	

public:
	void Initialize() override;

private:
	void Move_Teritory() override;		//“ê’£‚èˆ—
	virtual void Move_Chase(Vector2D location,Vector2D p_location) override;	//’ÇÕˆ—‹Iˆ—
	void SetDirection(eEnemyDirection d);		//•ûŒüİ’èˆ—

};

