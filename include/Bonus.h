#pragma once
#include "DrawMeshCube.h"



class Bonus
{
public:
	Bonus(void);
	~Bonus(void);

	void DrawBonus();
	bool EatBonus();
	void GetPosBonus(glm::vec3 PosBonus);

private:

	bool isEat;
	float s;
	glm::vec3 PosBonus;
};

