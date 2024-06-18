#include "Blast.h"
#include "DxLib.h"

Blast::Blast() : image(0), count(0), animation_count(0)
{
	for (int i = 0; i < 3; i++)
	{
		blast_image[i] = NULL;
	}
}

Blast::~Blast()
{

}


void Blast::Initialize()
{
	blast_image[0] = LoadGraph("Resource/Images/bom/bakufuu1.png");
	blast_image[1] = LoadGraph("Resource/Images/bom/bakufuu2.png");
	blast_image[2] = LoadGraph("Resource/Images/bom/bakufuu3.png");

	for (int i = 0; i < 3; i++)
	{
		if (blast_image[i] == -1)
		{
			throw("���e�̉摜������܂���\n");
		}
	}

	image = blast_image[0];
}

void Blast::Draw(float location_x, float location_y) const
{
	  DrawRotaGraphF(location_x, location_y, 0.7, DX_PI_F / 2, image, TRUE);
}

void Blast::Finalize()
{
	DeleteGraph(blast_image[0]);
	DeleteGraph(blast_image[1]);
	DeleteGraph(blast_image[2]);
}

void Blast::Animation()
{
	int i = 0;

	//�摜�̐؂�ւ�
	for (count = 1; count < 4; count++)
	{
		animation_count++;
		if (animation_count >= 50)
		{
			i++;
			//�J�E���g�̃��Z�b�g
			animation_count = 0;

			if (count < 4)
			{
				if (image == blast_image[0])
				{
					image = blast_image[1];
				}
				else if (image == blast_image[1])
				{
					image = blast_image[2];
				}
				
			}
		}
	}
}