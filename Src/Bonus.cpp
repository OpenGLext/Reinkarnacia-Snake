#include "Bonus.h"


Bonus::Bonus(void):s(25)
{
PosBonus.x = 0;
PosBonus.y = 0;
s = 25;
isEat = false;

}



Bonus::Bonus(const Bonus& bn)
{

}


Bonus::~Bonus(void)
{
}

void Bonus::SetPosBonus(glm::vec3 *pos_)
{
	PosBonus = *pos_;
}

void Bonus::NewBonus()
{
        PosBonus.x = rand() % 15;
	    PosBonus.y = rand() % 15;
		this->SetPosBonus(&PosBonus);
}

void Bonus::DrawBonus()
{
		

	 boxApple(PosBonus.x*s,PosBonus.y*s,(PosBonus.x+1)*s,(PosBonus.y+1)*s);
}

bool Bonus::EatBonus()
{

	//return false;
	return true;
}

glm::vec3 Bonus::GetPosBonus()
{
	return PosBonus;
}


