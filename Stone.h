#pragma once

#include "DrawMeshCube.h"
#include "Fruct.h"

class Stone : public Fruct
{
public:
	Stone(void);
	~Stone(void);

	virtual void New();
	

	void NewStone(glm::vec3 StartPosStone_);
	void DrawStone();
	void SetPos(glm::vec3 pos);
	int GetWidth();
	glm::vec3 GetStartPosStone();
	glm::vec3 GetEndPosStone();
	void SetFlagStone(const bool onoff, const int indx);

	int s;

private:


	glm::vec3 StartPosStone,EndPosStone;
	bool onOffStone[10];
	

};

