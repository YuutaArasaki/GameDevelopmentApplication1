#include "Akabe.h"
#include "math.h"

void Akabe::Initialize()
{
	enemy_state = TERITORY;
	teritory_location = Vector2D(0.0f, 0.0f);
}

void Akabe::Move_Chase(float delta_second)
{
	/*float a, x, y = 0.0f;
	Vector2D tg;

	x = (player->GetLocation().x - location.x) * (player->GetLocation().x - location.x);
	y = (player->GetLocation().y - location.y) * (player->GetLocation().y - location.y);
	a = sqrt(x + y);
	x = (player->GetLocation().x - location.x) / a;
	y = (player->GetLocation().y - location.y) / a;
	tg = Vector2D(x, y);

	velocity = tg;*/

}
