#pragma once
#include "../Objects/GameObject.h"
#include "Scene.h"

typedef enum {
	BAD,
	OK,
	GOOD,
	PERFECT,
	FINISH,
}RESULT;

class ResultScene : public GameObject
{
public:
	Scene* scene;
	int Result_image[5];
	int SE[4];
	int Sound_flag;

public:
	ResultScene();
	~ResultScene();

	void Initialize();
	void Draw();


	
};

