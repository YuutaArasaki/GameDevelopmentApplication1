#include "Pinky.h"

void Pinky::Initialize()
{
	enemy_type = PINKY;
	enemy_state = TERITORY;
	teritory_location = Vector2D(0.0f, 0.0f);
}

void Pinky::Move_Chase(float delta_second)
{

}