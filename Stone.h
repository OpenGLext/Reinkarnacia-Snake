#pragma once

#include "DrawMeshCube.h"

class Stone
{
public:
	Stone(void);
	~Stone(void);
	void DrawStone();
	void NewStone();
	void SetPos(glm::vec3 pos);
	glm::vec3 GetPosStone();

private:
	glm::vec3 posStone;
	int s;

};

