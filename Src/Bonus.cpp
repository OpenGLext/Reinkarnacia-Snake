#include "Bonus.h"


Bonus::Bonus(void)
{
PosBonus.x = 0;
PosBonus.y = 0;
s = 25;
isEat = false;
}


Bonus::~Bonus(void)
{
}

void Bonus::DrawBonus()
{
		PosBonus.x = rand() % 15;
	    PosBonus.y = rand() % 15;

	 boxApple(PosBonus.x,PosBonus.y,PosBonus.x+s,PosBonus.y+s);
}

bool Bonus::EatBonus()
{

	//return false;
	return true;
}

void Bonus::GetPosBonus(glm::vec3 PosBonus_)
{
	PosBonus_ = PosBonus;
}
