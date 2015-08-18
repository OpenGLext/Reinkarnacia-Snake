#pragma once
#include "DrawMeshCube.h"
 void boxApple(float x1, float y1, float x2, float y2)
{

	glBegin(GL_QUADS);	
			
			glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1); 

			glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);

			glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2); 

			glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2);

			//glNormal3fv(NormalArrayApple);


	glEnd();

}
 void boxSnake(float x1, float y1, float x2, float y2)
{

	glBegin(GL_QUADS);	
			
			glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1); 

			glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);

			glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2);

			glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2); 

			glNormal3fv(NormalArraySnake);

	glEnd();

}
 void oval(float x1, float y1, float x2, float y2)
 {
	 glBegin(GL_QUADS);	
			
			glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2);


	glEnd();
 }
 void boxFon(float x1, float y1, float x2, float y2)
{

	glBegin(GL_QUADS);	
			
			glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1); 

			glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);

			glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2); 

			glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2);

			//glNormal3fv(NormalArrayApple);


	glEnd();

}
 glm::vec3 computeNormal(glm::vec3 const & a,glm::vec3 const & b,glm::vec3 const & c)
{
   return glm::normalize(glm::cross(c - a, b - a));
}