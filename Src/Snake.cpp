#include "Snake.h"

Snake::Snake(void)
{	
	speedSnake = 1.0f;
	dx = 0.1f;
	dy = 0.1f;
	
}
Snake::Snake( Fruct& frt):Scale(25.0f),speedSnake(0.9f),stepAnim(0.1f)
{
	m_lenbody = 4; m_dir = 1; oldtime = 0.0f;

	for(int i=0; i<m_lenbody; i++)
	{
		s[i].x = 0; s[i].y = 0;
	}

	m_isCollision = false;
	m_isHeadWithTail = false;

	pFruct = new Fruct();
	pFruct = &frt;
}
Snake::~Snake(void)
{
	delete pFruct;

}

void Snake::SetLenBody(const int newLen)
{
	m_lenbody = newLen;
}
bool Snake::IsCollision() const
 {
	 return m_isCollision;
 }
void Snake::SetCollision(const bool setcol)
{
	m_isCollision = setcol;
}
void Snake::AddElementBody()
{
	m_lenbody += 1;
}
int  Snake::GetLenBody()
{
	return m_lenbody;
}
void Snake::ResetSnake()
{
	m_lenbody = 4;
	s[0].x = 10;
	s[0].y = 10;
}
bool Snake::isOutWall()
{
	const int leftWall   = 0;
	const int rightWall  = 30;
	const int topWall    = 20;
	const int bottomWall = 0;

	if ( s[0].x < leftWall   ) 
	{ 
		m_outwall = true;
		m_dir = 2;
		return true;
	}
	if ( s[0].x > rightWall  )  
	{ 
		m_outwall = true;
		m_dir = 1;
		return true;
	}
	if ( s[0].y > topWall    ) 
	{ 
		m_outwall = true;
		m_dir = 3;
		return true; 
	}
	if ( s[0].y < bottomWall ) 
	{
		m_outwall = true;
		m_dir = 0;
		return true;
	}

	return false;
}
bool Snake::GetOutWall()
{
	return m_outwall;

}
void Snake::SetDir(const int dir_)
{
	m_dir = dir_;
}
int Snake::GetDir() const
{
	return m_dir;
}
bool Snake::GetIsHeadWithTail() const
{
	return m_isHeadWithTail;
}
void Snake::SetHeadWithTail(const bool f)
{
	m_isHeadWithTail = f;
}
void Snake::CheckHeadWithTail()
{
	/* если столкнулись голова и хвост */
	  for (int i=1;i<m_lenbody;i++)
		  if (s[0].x==s[i].x && s[0].y==s[i].y)  { this->ResetSnake(); m_isHeadWithTail = true; }
}
void Snake::CheckEatFruct()
{
	//fructx = pFruct->GetX(); fructy = pFruct->GetY();
	fructpos = pFruct->GetPos();
	 if ((s[0].x == fructpos.x) && ( s[0].y == fructpos.y)) 
      {
		  m_isCollision = true;
		  this->AddElementBody();
		  pFruct->New();
	  }
}
glm::vec3 Snake::GetPosHead()
  {
	  glm::vec3 poshead;

	  poshead.x = s[0].x;
	  poshead.y = s[0].y;

	  return poshead;
  }
void Snake::GetPosTail(glm::vec3 posTail_)
{
	posTail_.x = s[m_lenbody].x;
	posTail_.y = s[m_lenbody].y;
	
}
void Snake::SetPosTail(glm::vec3  posTail_)
{
	s[m_lenbody].x = posTail_.x;
	s[m_lenbody].y = posTail_.y;
}
void Snake::SetOutWall(const bool col)
{
	m_outwall = false;
}
void Snake::Tick()
 {
	
 for (int i = m_lenbody; i>0; --i)
	 {
		 s[i].x = s[i-1].x;
		 s[i].y = s[i-1].y;
	 }

    // dx += speedSnake + stepAnim;
	// dy += speedSnake + stepAnim;

     /*if (m_dir==0) s[0].y += dy;  
	 if (m_dir==1) s[0].x -= dx;     
	 if (m_dir==2) s[0].x += dx;   
	 if (m_dir==3) s[0].y -= dy;*/

	 if (m_dir==0) s[0].y += 1;  
	 if (m_dir==1) s[0].x -= 1;     
	 if (m_dir==2) s[0].x += 1;   
	 if (m_dir==3) s[0].y -= 1;

	 this->isOutWall();
	this->CheckHeadWithTail();
	this->CheckEatFruct();
}

void Snake::DrawHead()
{
	 
     oval(s[0].x * Scale, s[0].y * Scale, (s[0].x + 0.99) * Scale, ( s[0].y + 0.99) * Scale);

	 glDisable(GL_TEXTURE_2D);
}
void Snake::DrawSnake()
 {  

	 for (int i=1;i<m_lenbody;i++)
     boxSnake(s[i].x * Scale, s[i].y * Scale, (s[i].x + 0.99) * Scale, ( s[i].y + 0.99) * Scale);

	 glDisable(GL_TEXTURE_2D);
 
 }
