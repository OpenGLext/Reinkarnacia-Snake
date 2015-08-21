#pragma once
#include "Quad.h"
#include "Fruct.h"
#include "DrawMeshCube.h"
#include "glm\glm.hpp"

class Snake
{
public:
	Snake(void);
	~Snake(void);
	Snake( Fruct& frt);

  void Tick();
  void DrawSnake();
  bool IsCollision() const;
  void SetCollision(const bool setcol);
  void AddElementBody();
  int  GetLenBody();
  void SetLenBody(const int newLen);
  void ResetSnake();
  bool isOutWall();
  void SetOutWall(const bool col);
  bool GetOutWall();
  void SetDir(const int dir_);
  int GetDir() const;
  bool GetIsHeadWithTail() const;
  void SetHeadWithTail(const bool f);
  void CheckHeadWithTail();
  void CheckEatFruct();
  void DrawHead();

  glm::vec3 GetPosHead();
  void GetPosTail(glm::vec3 posTail_);
  void SetPosTail(glm::vec3  posTail_);

  float dx,dy;

private:
	Texture snakeTexture;
	int m_lenbody;
	float Scale;
	int m_dir;
	float speedSnake;
	float stepAnim;
	float oldtime;
	Fruct *pFruct;
	bool m_isCollision;
	bool m_outwall;
	bool m_isHeadWithTail;
	
	glm::vec3 s[100];
    glm::vec3 fructpos;

};

