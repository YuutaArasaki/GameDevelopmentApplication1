#include "Pinky.h"

void Pinky::Initialize()
{
	enemy_state = idle;
	teritory_panel[0] = Vector2D(6, 1);
	teritory_panel[1] = Vector2D(1, 5);
}

void Pinky::Move_Chase(Vector2D location, Vector2D p_location)
{

}