#include "Stone.h"
#include <time.h>


Stone::Stone(void)
{
	s = 50;
}

void Stone::SetPos(glm::vec3 pos)
{
	posStone = pos;
}

void Stone::NewStone()
{

	posStone.x = rand()  % 520;
	posStone.y = rand()  % 520;
	this->SetPos(posStone);
}

glm::vec3 Stone::GetPosStone()
{
	return posStone;

}


Stone::~Stone(void)
{
}

void Stone::DrawStone()
{
	boxFon(posStone.x,posStone.y,posStone.x+s,posStone.y+s);
}
