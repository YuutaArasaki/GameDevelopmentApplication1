#include "Bom.h"

void Bom::Animation()
{
	int i = 0;

	//�摜�̐؂�ւ�
	for (count = 1; count < 4; count++)
	{
		animation_count++;
		if (animation_count >= 60)
		{
			i++;
			//�J�E���g�̃��Z�b�g
			animation_count = 0;

			if (count < 4)
			{
				if (image == bom_image[0])
				{
					image = bom_image[1];
				}
				else if (image == bom_image[1])
				{
					image = bom_image[2];
				}
				else if (image == bom_image[2])
				{
					image = bom_image[3];
					delete_object = 1;
				}
			}
		}
	}
}