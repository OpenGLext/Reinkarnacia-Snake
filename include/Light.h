#pragma once
#include "D:\\Движки\freeglut-2.8.1\include\GL\freeglut.h"
#include "glm\glm.hpp"

class Light
{
public:
	Light(void);
	~Light(void);

	void OnOffLight(const bool on_);
	void SetPosLight(const glm::vec3 *pos); 
	void SetPosLight( int pos);
	bool GetOnOff() const;


private:
	bool  m_onoff;
	float light0_diffuse[3]; 
    int light0_direction[4];
	float ambient[4];
	GLfloat m_pos[4];
	GLfloat LightAmbient[4];
    GLfloat LightDiffuse[4];
    GLfloat LightPosition[4];
};

