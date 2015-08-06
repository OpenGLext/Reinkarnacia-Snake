#include "Light.h"

Light::Light(void)
{
	 
GLfloat LightAmbient[]={ 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]={ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]={ 0.0f, 0.0f, 0.0f, 1.0f };


}
Light::~Light(void)
{
}
void Light::SetPosLight( int pos)
{
	glLighti(GL_LIGHT0, GL_POSITION, pos); 
}
bool Light::GetOnOff() const
{
	return this->m_onoff;
}
void Light::OnOffLight(const bool on_)
{
	if (on_) 
	{
		this->m_onoff = on_;

		glEnable(GL_LIGHTING);
		//glClearDepth(-1.0f);	
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);	

		glEnable(GL_LIGHT1);
	

		//glEnable(GL_COLOR_MATERIAL);

		//glColorMaterial(GL_FRONT,GL_AMBIENT);

	//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	//	glLightiv( GL_LIGHT1, GL_POSITION, light0_direction ); 

	//	glLightfv(GL_LIGHT1,GL_DIFFUSE,light0_diffuse);

	}
	else 
	{ 
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT1);
		//glDisable(GL_LIGHT1);
	}
}
void Light::SetPosLight(const glm::vec3 *pos)
{
	m_pos[0] = pos->x; m_pos[1] = pos->y; m_pos[2] = 1.0;
	glLightfv(GL_LIGHT0, GL_POSITION, m_pos); 
}
