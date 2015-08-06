#pragma once
#include "D:\\Движки\freeglut-2.8.1\include\GL\freeglut.h"
#include "glm\glm.hpp"

 extern GLfloat  NormalArraySnake[200];
 extern GLfloat  NormalArrayApple[2];

 void boxSnake(float x1, float y1, float x2, float y2);
 void boxApple(float x1, float y1, float x2, float y2);
 void   boxFon(float x1, float y1, float x2, float y2);
 void     oval(float x1, float y1, float x2, float y2);
 glm::vec3 computeNormal( glm::vec3 const & a,glm::vec3 const & b,glm::vec3 const & c );

 