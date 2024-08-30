#include "Akabe.h"
#include "math.h"

void Akabe::Initialize()
{
	enemy_state = TERITORY;
}
void Akabe::Move_Teritory(float delta_second)
{

}
void Akabe::Move_Chase(float delta_second)
{
	ePanelID nel;

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(location);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE }
	};

	int px, py, ex, ey, x, y, h, n, j = 0;
	Vector2D a;

	if (StageData::GetPanelData(location) == ePanelID::BRANCH)
	{

		if (panel[UP] == ret[UP] && direction != down)
		{
			StageData::ConvertToIndex(player->GetLocation(), py, px);
			StageData::ConvertToIndex(this->GetLocation(), ey, ex);
			ey += -1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[up] = n + h;
		}
		else
		{
			f[up] = 0;
		}

		if (panel[RIGHT] == ret[RIGHT] && direction != left)
		{
			StageData::ConvertToIndex(player->GetLocation(), py, px);
			StageData::ConvertToIndex(this->GetLocation(), ey, ex);
			ex += 1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[right] = n + h;
		}
		else
		{
			f[right] = 0;
		}

		if (panel[DOWN] == ret[DOWN] && direction != up)
		{
			StageData::ConvertToIndex(player->GetLocation(), py, px);
			StageData::ConvertToIndex(this->GetLocation(), ey, ex);
			ey += 1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[down] = n + h;
		}
		else
		{
			f[down] = 0;
		}

		if (panel[LEFT] == ret[LEFT] && direction != right)
		{
			StageData::ConvertToIndex(player->GetLocation(), py, px);
			StageData::ConvertToIndex(this->GetLocation(), ey, ex);
			ex += -1;
			x = (px - ex) * (px - ex);
			y = (py - ey) * (py - ey);
			h = x + y;
			n = (px - ex) + (py - ey);
			f[left] = n + h;
		}
		else
		{
			f[left] = 0;
		}

		mini = 0;

		for (int i = 0; i < 4; i++)
		{
			if (mini == 0)
			{
				mini = f[i];
				j = i;
			}

			if (mini > f[i] && f[i] > 0)
			{
				mini = f[i];

				j = i;

			}
		}

		switch (j)
		{
		case up:
			if (direction_flag == true && location.x == a.x)
			{
				direction = up;
				direction_flag = false;

			}
			break;
		case right:
			if (direction_flag == true)
			{
				direction = right;
				direction_flag = false;
			}
			break;
		case down:
			if (direction_flag == true)
			{
				direction = down;
				direction_flag = false;
			}
			break;


		case left:
			if (direction_flag == true)
			{
				direction = left;
				direction_flag = false;
			}
			break;
		}
	}

	if (StageData::GetPanelData(location) != BRANCH)
	{
		direction_flag = true;
	}

}

void Akabe::SetPlayer(Player* p)
{
	player = p;
}
