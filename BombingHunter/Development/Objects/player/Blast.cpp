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
	//爆風の画像読み込み
	blast_image[0] = LoadGraph("Resource/Images/bom/bakufuu1.png");
	blast_image[1] = LoadGraph("Resource/Images/bom/bakufuu2.png");
	blast_image[2] = LoadGraph("Resource/Images/bom/bakufuu3.png");

	//SE読み込み
	SE = LoadSoundMem("Resource/Sound/SE/explosion.wav");

	//爆風のSE再生
	PlaySoundMem(SE, DX_PLAYTYPE_BACK, TRUE);

	//エラーチェック
	for (int i = 0; i < 3; i++)
	{
		if (blast_image[i] == -1)
		{
			throw("爆弾の画像がありません\n");
		}
	}

	//爆風の初期画像設定
	image = blast_image[0];

	//タイプ
	object_type = BLAST;
}

void Blast::Update()
{
	Animation();
}

void Blast::Draw() const
{
	  DrawRotaGraphF(location.x, location.y, 0.6, DX_PI_F / 2, image, TRUE,FALSE);
}

void Blast::Finalize()
{
	DeleteGraph(blast_image[0]);
	DeleteGraph(blast_image[1]);
	DeleteGraph(blast_image[2]);
}

void Blast::Animation()
{

	animation_count++;
	
	//画像の切り替え
	if (animation_count >= 20)
	{
		
		//カウントのリセット	
		animation_count = 0;
		
		if (image == blast_image[0])
		{
			image = blast_image[1];
		}
		else if (image == blast_image[1])
		{
			image = blast_image[2];
		}
		else if (image == blast_image[2])
		{
			delete_object = 1;
		}
			
		
	}
			
}
		
