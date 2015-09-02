#include "Fruct.h"

Fruct::Fruct(const Fruct& frt)
{

}
Fruct::Fruct(void):scale(25.0f)
{
}
Fruct::~Fruct(void)
{
}
void Fruct::SetPos(glm::vec3 *pos_)
{
	m_pos = *pos_;
}
glm::vec3 Fruct::GetPos()
{
	return m_pos;
}
void Fruct::New()
{  

	m_pos.x = rand() % 15;
	m_pos.y = rand() % 15;

	this->SetPos(&m_pos);

}
void Fruct::DrawApple(glm::vec3 *drwpos)
{     
	if ( drwpos == nullptr) 
	{
	   boxApple(m_pos.x * scale, m_pos.y * scale,(m_pos.x + 1)*scale,(m_pos.y + 1)*scale);  
	  
	}
	else
	{
		 boxApple(drwpos->x * scale, drwpos->y * scale,(drwpos->x + 1)*scale,(drwpos->y + 1)*scale);  
	}
		//x*scale,y*scale,(x+1)*scale,(y+1)*scale); 
	//   glDisable(GL_TEXTURE_2D);
}
	
	
