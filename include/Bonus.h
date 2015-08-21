#pragma once
#include "DrawMeshCube.h"
#include "Fruct.h"



class Bonus : public Fruct
{
public:
	Bonus(void);
	~Bonus(void);
	Bonus::Bonus(const Bonus& bn);

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

