#include "Stone.h"
#include <time.h>


Stone::Stone(void):s(35)
{
	s = 35;
}
void Stone::SetPos(glm::vec3 pos)
{
	StartPosStone = pos;
}
int Stone::GetWidth()
{
	return s;

}
void Stone::NewStone()
{

	    srand(time(0));



		StartPosStone.x = rand()  % 150;
		StartPosStone.y = rand()  % 150;
		this->SetPos(StartPosStone);

		for(int i=0; i<10;i++)
		onOffStone[i] = true;
	
}
glm::vec3 Stone::GetStartPosStone()
{
	return StartPosStone;

}
glm::vec3 Stone::GetEndPosStone()
{
	return EndPosStone;

}
Stone::~Stone(void)
{
}
void Stone::SetFlagStone(const bool onoff, const int indx)
{
	onOffStone[indx] = onoff;

}
void Stone::DrawStone()
{
	s = 35;
	/*for(int i=0; i<10;i++)
	{
		if (onOffStone[i]) 
		{*/
			
	boxApple(StartPosStone.x , StartPosStone.y ,(EndPosStone.x + 1)+s,(EndPosStone.y + 1)+s);  
	
	   
	/*        
		}
	}*/
}
 void Stone::New()
{

	this->StartPosStone.x = rand() % 250;
	this->StartPosStone.y = rand() % 250;

}
