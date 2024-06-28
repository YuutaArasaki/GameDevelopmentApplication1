#include "ResultScene.h"
#include "DxLib.h"

ResultScene::ResultScene() : Sound_flag()
{
	for (int i = 0; i < 5; i++)
	{
		Result_image[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		SE[i] = NULL;
	}
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	LoadDivGraph("Resource/images/Score/Resulte_image.png", 5, 1, 5, 800, 318, Result_image);

	SE[0] = LoadSoundMem("Resource/Sound/ResultSE/SE_bad.wav");
	SE[1] = LoadSoundMem("Resource/Sound/ResultSE/SE_ok.wav");
	SE[2] = LoadSoundMem("Resource/Sound/ResultSE/SE_good.wav");
	SE[3] = LoadSoundMem("Resource/Sound/ResultSE/SE_perfect.wav");
}

void ResultScene::Draw()
{
	if (object_type = BAD)
	{
		DrawRotaGraphF(320, 220, 0.6, 0, Result_image[1], TRUE);
		PlaySoundMem(SE[0], DX_PLAYTYPE_NORMAL, TRUE);
	}
}