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
	void NewBonus();
	void SetPosBonus(glm::vec3 *pos_);
	glm::vec3 PosBonus;

private:

	bool isEat;
	float s;
	
};

