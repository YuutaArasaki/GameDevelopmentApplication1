#include "Akabe.h"
#include "math.h"

void Akabe::Initialize()
{
	enemy_state = TERITORY;
	tp_x, tp_y = 0;
	direction_flag = true;
}
void Akabe::Move_Teritory(Vector2D location)
{
	this->location = location;
	int ex = 0;
	int	ey = 0;
	int x, y, h, n = 0;

	int teritory_panel[4][2] = { {21,1},
								 {26,1},
								 {26,5},
								 {21,5} };

	std::map<eAdjacentDirection, ePanelID> panel = StageData::GetAdjacentPanelData(this->location);
	StageData::ConvertToIndex(this->location, ey, ex);

	std::map<eAdjacentDirection, ePanelID> ret = {
		{ eAdjacentDirection::UP, ePanelID::NONE },
		{ eAdjacentDirection::DOWN, ePanelID::NONE},
		{ eAdjacentDirection::LEFT, ePanelID::NONE },
		{ eAdjacentDirection::RIGHT, ePanelID::NONE } };


	if (tp_x == 0 && tp_y == 0)
	{
		tp_x = teritory_panel[0][0];
		tp_y = teritory_panel[0][1];
	}

	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[1][0];
		tp_y = teritory_panel[1][1];
	}
	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[2][0];
		tp_y = teritory_panel[2][1];
	}
	if (tp_x == ex && tp_y == ey)
	{
		tp_x = teritory_panel[3][0];
		tp_y = teritory_panel[3][1];
	}
	else if (tp_x == ex && tp_y == ey)
	{
		tp_x = 0;
		tp_y = 0;
	}
	if (StageData::GetPanelData(this->location) != ePanelID::BRANCH)
	{
		direction_flag = true;
	}
	if (StageData::GetPanelData(this->location) == ePanelID::BRANCH)
	{
		if (panel[UP] == ret[UP] && direction != down)
		{
			ey += -1;
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
			ey += 1;
			f[up] = n + h;
		}
		else
		{
			f[up] = 0;
		}

		if (panel[RIGHT] == ret[RIGHT] && direction != left)
		{
			ex += 1;
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
			ex += -1;
			f[right] = n + h;
		}
		else
		{
			f[right] = 0;
		}

		if (panel[DOWN] == ret[DOWN] && direction != up)
		{
			ey += 1;
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
			ey += -1;
			f[down] = n + h;
		}
		else
		{
			f[down] = 0;
		}

		if (panel[LEFT] == ret[LEFT] && direction != right)
		{
			ex += -1;
			x = (tp_x - ex) * (tp_x - ex);
			y = (tp_y - ey) * (tp_y - ey);
			h = x + y;
			n = (tp_x - ex) + (tp_y - ey);
			ex += 1;
			f[left] = n + h;
		}
		else
		{
			f[left] = 0;
		}

		mini = 0;

		int j;

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

		int x = (int)location.x;
		int y = (int)location.y;
		Vector2D a, b;

		switch (j)
		{
		case up:
			SetDirection(up);
			break;
		case right:
			a.y = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
			b.y = (int)(ey + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
			if (direction_flag == true)
			{
				if (y == a.y || y == b.y)
				{
					direction = right;
					direction_flag = false;
				}
			}
			break;
		case down:
			a.x = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
			b.x = (int)(ex + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
			if (direction_flag == true)
			{
				if (x == a.x || x == b.x)
				{
					direction = down;
					direction_flag = false;
				}
			}
			break;


		case left:
			a.y = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
			b.y = (int)(ey + 1) * D_OBJECT_SIZE + D_OBJECT_SIZE / 2;
			if (direction_flag == true)
			{
				if (y == a.y || y == b.y)
				{
					direction = left;
					direction_flag = false;
				}
			}
			break;
		}
	}

	if (StageData::GetPanelData(this->location) != ePanelID::BRANCH)
	{
		direction_flag = true;
	}

}
void Akabe::Move_Chase(Vector2D location)
{

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
			if (direction_flag == true )
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
