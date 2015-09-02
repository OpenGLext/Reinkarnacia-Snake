#pragma once

#include "DrawMeshCube.h"
#include "Fruct.h"

typedef struct vec2
{
	int x;
	int y;
};

class Stone : public Fruct
{
public:
	Stone(void);
	~Stone(void);

	virtual void New();
	

	void NewStone();
	void DrawStone();
	void SetPos(vec2 pos);
	int GetWidth();
	vec2 GetStartPosStone();
	vec2 GetEndPosStone();
	void SetFlagStone(const bool onoff, const int indx);

	int s;

private:

	
   vec2 StartPosStone,EndPosStone;

	
	bool onOffStone[10];
	

};

