#pragma once
#include <math.h>
#include "DrawMeshCube.h"
#include "Quad.h"
#include "glm\glm.hpp"


class Fruct
{
public:
	Fruct(void);
	Fruct(const Fruct& frt);
	~Fruct(void);

	
	void SetPos(glm::vec3 *pos_);
	glm::vec3 GetPos();
	void DrawApple();
	void New();

    

private:
	glm::vec3 m_pos;
	float scale;
	Texture fructTexture;
	
	
};

