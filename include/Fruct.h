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
     void DrawApple(glm::vec3 *drwpos);
	virtual void New();

    glm::vec3 m_pos;

private:
	
	float scale;
	Texture fructTexture;
	
	
};

