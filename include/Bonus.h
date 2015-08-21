#pragma once
#include "DrawMeshCube.h"



class Bonus
{
public:
	Bonus(void);
	~Bonus(void);

	void DrawBonus();
	bool EatBonus();
	glm::vec3 GetPosBonus();
	void NewBonus();
	void SetPosBonus(glm::vec3 *pos_);
	glm::vec3 PosBonus;

private:

	bool isEat;
	float s;
	
};

