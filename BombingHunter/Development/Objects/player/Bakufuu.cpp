#include "Bom.h"

void Bom::BomHit()
{
	animation_count++;

	//�摜�̐؂�ւ�
	if (animation_count >= 30)
	{
		if (count > 4)
		{
			count = 0;
		}
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		for (count; count < 4;)
		{
			image = bom_image[count];
			break;
		}
		count++;
	}
}