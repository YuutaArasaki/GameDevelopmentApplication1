#include "Bom.h"

void Bom::BomHit()
{
	animation_count++;

	//画像の切り替え
	if (animation_count >= 30)
	{
		if (count > 4)
		{
			count = 0;
		}
		//カウントのリセット
		animation_count = 0;

		for (count; count < 4;)
		{
			image = bom_image[count];
			break;
		}
		count++;
	}
}