#include "D:\\Движки\freeglut-2.8.1\include\GL\freeglut.h"
#include "include/glm/gtc/matrix_transform.hpp"
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>
#include "include/Font.h"
#include "include/Snake.h"
#include "include/Fruct.h"
#include "include/Game.h"
#include "include/AddTexture.h"
#include "include/Quad.h"
#include "include/DrawMeshCube.h"
#include "include\glm\glm.hpp"
#include "include\Bonus.h"
#include "Stone.h"

#pragma comment(lib,"/freeglut.lib")
#pragma comment(lib,"/sfml-audio-d.lib")



struct GameData
{
  int Score;
  int lifes;
  int level;
  int FructOnLevel[2];
};

HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;
HINSTANCE hPrevInstance;
Font *ourtext;
sf::SoundBuffer collisionBuff,eatBuff,moveBuff,gameoverBuff,collisionTailBuff;
sf::Sound collisionSound,eatSound,moveSound,gameoverSound,collisionTail;
sf::Music backMusic;

 bool DEMO = false;

GameData *pGameData;
Texture    *pTexturePack[6];

Stone *pStone;
Bonus *pBonus;
Fruct *pFruct;
Snake *pSnake;
Game  *pGame;
Quad  *pLdrTexture;

bool turn(false);
bool PlayMusicOn(false);
HDC  hDC;

int static deltaTime(360);

const int StartTime(1);
int NowTime(0);
int OldTime(0);
int frame(0);
const int LOGO = 1;
const int GAME = 2;
const int LEVELCOMPLETE = 3;
const int GAMEOVER = 4;
const int STARTMENU = 5;
const int ENDGAME   = 6;

bool StartGame(false);
bool GameOver(false);

int State(GAME);
int TimeDraw(0);
int IntervalBonus(60);

int N=30,M=20;
int Scale=25;

int w = Scale*N;
int h = Scale*M;

static float i(1.0f);
static float j(1.0f);
glm::vec3 posHead,posBonus;

void ResetGame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor4f(0,0,0,0);


}
void DrawField()
  {
   glColor3f(0.0,0.7,0.0);
   glBegin(GL_LINES);

    for (int i=0; i<w; i+=Scale) 
      {
		  glVertex2f(i,0); glVertex2f(i,h);
	  }
    for (int j=0; j<h; j+=Scale)  
      {
		  glVertex2f(0,j); glVertex2f(w,j);
	  }

    glEnd();
}
std::string GetStr(const char* mess,const float value,const int valueInt=0)
{
	std::string ScoreFloat="";
	std::stringstream StrStream;

	StrStream<<value;
	StrStream>>ScoreFloat;
	ScoreFloat = mess + ScoreFloat ;
	 
	return ScoreFloat;
}
void DrawLife()
{
	//ResetGame();
	//glDisable(GL_BLEND);
	
     glColor4f(0.5f,0.0f,0.9f,1.9f);


  //std::string lev = GetStr("Demo version of the timer is not running ",0);
 // ourtext->put(350, 460, 1.0f, lev.c_str());

  //std::string lev = GetStr("Time: ",lev.c_str());


	 std::string lev = GetStr("Time: ",deltaTime);

	 ourtext->put(550, 460, 1.0f, lev.c_str());

	 std::string score = GetStr("Score: ",pGameData->Score);
	
	 ourtext->put(550, 435, 1.0f, score.c_str());

	 std::string life_ = GetStr("Life: ",pGameData->lifes);
	
	 ourtext->put(550, 410, 1.0f, life_.c_str());

	 
	// std::string posstr = GetStr("FPS: ",frame*1000.0/(NowTime - OldTime));

	 std::string posstr = GetStr("Stone StartX ",pStone->GetStartPosStone().x);
	
	 ourtext->put(550, 360, 1.0f, posstr.c_str());

	std::string posstr2 = GetStr("posHeadEndX ",pSnake->GetPosHeadEnd().x);

	  ourtext->put(550, 330, 1.0f, posstr2.c_str());

	       /* std::string str_fps = GetStr(" ",abs((num-4)-FructOnLevel[0]));
		    glColor4f(1.0f,1.0f,0.3f,0.9f);
	        ourtext->put(350, 485, 1.0f, str_fps.c_str());*/

	/* if (level == 2)
	 {
		    std::string str_fps = GetStr(" ",abs((num-4)-FructOnLevel[1]));
		    glColor4f(1.0f,1.0f,0.3f,0.9f);
	        ourtext->put(350, 485, 1.0f, str_fps.c_str());
	 }*/
}
void ShowGameOver()
{
	 ResetGame();
	 TimeDraw = 3000;
	 backMusic.stop();
	 collisionSound.stop(); 
	 eatSound.stop();
	 gameoverSound.play(); 
	 gameoverSound.stop();

     glColor4f(1.0f,0.0f,0.0f,0.9f);

	 std::string ScoreStr = GetStr("Last Score: ",pGame->GetScore());
	 ourtext->put(300, 350, 1.0f, ScoreStr.c_str());
	
	 ourtext->put(300, 300, 1.0f, "End Level, retry again");

	 glColor4f(0.0f,1.0f,0.0f,0.9f);
	 ourtext->put(300, 250, 1.0f, "Press <g> to Start or <Esc> to Exit...");

	 deltaTime = 60;
	 
	
	
}
void ShowMenu()
{
	glEnable(GL_BLEND);
	float FonMenuX(200.0f),FonMenuY(90.0f),FonMenuX2(550.0f),FonMenuY2(450.0f);
	float WidthMenu(350.0f);
	float HeightMenu(360.0f);
	float StartButtonX(220.0f); float StartButtonY(350.0f); float StartButtonX2(530.0f); float StartButtonY2(400.0f);
	float WidthButtonStart(310.0f); float HeightButtonStart(50.0f);

    	/*-------------------
	       фон рамка меню
	       ------------------*/
	glColor4f(0.5f,0.5f,0.5f,0.5f);
	glRectf(FonMenuX, FonMenuY, FonMenuX + WidthMenu, FonMenuY + HeightMenu);
	/*-------------------
	       кнопка старт
	       ------------------*/
	glColor4f(0.0f,1.0f,0.0f,0.3f);
	glRectf(StartButtonX, StartButtonY-20, StartButtonX + WidthButtonStart, StartButtonY + HeightButtonStart); 
	/*-------------------
	       кнопка старт
	       ------------------*/
	/*-------------------
	       текст для кнопки старт
	       ------------------*/
	
     glColor4f(0.0f,0.0f,0.3f,0.9f);
     ourtext->put(290, 365, 1.0f, "Start Game");
	 
}
bool TargetInButton(int x, int y)
{
	float xmin(220.0f); float xmax(530.0f); float ymin(350.0f); float ymax(400.0f);

	if ( x >= xmin && x <= xmax) 
		{
			if ( ((y+260.0f)  >= ymin) && ((y +260.0f) <= ymax))
			{
               return true;
			}
	}

	return false;
}
bool IsLevelComplete()
{
	if ( (pSnake->GetLenBody() - 4) == pGameData->FructOnLevel[0]  )
	{
      // State = LEVELCOMPLETE;
	   pGameData->level += 1;
	   //FructOnLevel[0] = 7;
	   TimeDraw = 30;
	   glColor3f(0.0f,1.0f,0.0f);
	   ourtext->put(300,300,1.0f,"Level is complete...");
	   //LastScore = FructOnLevel[0] * 100;
	   pGameData->FructOnLevel[0] = rand() % 10;
	 //  ShadowFructs = FructOnLevel[0];
       return true;
	   
	}

	//if ( (num - 4) == FructOnLevel[1]  )
	//{
 //     // State = LEVELCOMPLETE;
	//   level = 3;
	//   //FructOnLevel[0] = 7;
	//     glColor3f(0.0f,1.0f,0.0f);
	//   ourtext->put(300,300,1.0f,"Level is complete...");
	//   TimeDraw = 80;
	//   LastScore = FructOnLevel[1] * 100;
 //      return true;
	//   
	//}
	return false;
}
void DrawBack()
{
	
	
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_COLOR, GL_ONE);

	AddTextura(pTexturePack[3]);
	boxFon(0,0,25*30,25*20);
	//free(pBackTexture->imageData);
	
}
void DrawBonus()
{
	   
glPushMatrix();

AddTextura(pTexturePack[4]);

		// glMatrixMode(GL_MODELVIEW);
		// glLoadIdentity();
		
		// glScalef(2.25f,2.25f,0);
		 //glScalef(0.25f,0.25f,0);

pBonus->DrawBonus();
//pBonus->DrawBonus();

		 glPopMatrix();
		
}
void GameLogic()
{
	 if (deltaTime <= 0.1f || pGame->GetStateGame() == GAMEOVER  ) { pGame->SetStateGame(GAMEOVER); ResetGame(); ShowGameOver(); }  

		          posBonus = pBonus->GetPosBonus();
				  posHead = pSnake->GetPosHeadBegin();

				  std::string posstr = GetStr("posHead ",posHead.x);
				  std::string pos_str = GetStr("posBonus ",posBonus.x);

	             ourtext->put(550, 320, 1.0f, pos_str.c_str());
                 ourtext->put(550, 380, 1.0f, posstr.c_str());

				 if ((posBonus.x != 0 && posHead.x != 0) && (posBonus == posHead)) 
				 {
					   /* enable particle system on 5000 ms */

					   pSnake->SetLenBody(4);

					   pBonus->NewBonus();

					   std::string posstr = GetStr("Collision Bonus: ",1);
					   ourtext->put(550, 300, 1.0f, posstr.c_str());
			
				 }

			if (pSnake->CheckCollisionStone(pStone->GetStartPosStone())) { collisionSound.play(); if (pGameData->lifes == 0) { pGame->SetStateGame(GAMEOVER); ShowGameOver(); } else pGameData->lifes -= 1; }
				
	        if (pSnake->GetOutWall() && pGameData->lifes == 0) { pGame->SetStateGame(GAMEOVER);  ResetGame(); ShowGameOver(); }
	        if (pSnake->GetOutWall() && pGameData->lifes != 0) { collisionSound.play(); pGame->SetLife(pGameData->lifes -= 1); pGameData->Score = 0; 
			                                                     pSnake->SetOutWall(false); }					
											
			if (pSnake->IsCollision())       {  eatSound.play(); pGame->SetScore(pGameData->Score += 100); pSnake->SetCollision(false);  }
			if (pSnake->GetIsHeadWithTail()) { pGameData->Score = 0; pSnake->ResetSnake(); pSnake->SetHeadWithTail(false); }	




}
void DrawFruct()
{
	


		//		 glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				// glBlendFunc(GL_SRC_ALPHA, GL_ONE);

				// glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
				// glBlendFunc(GL_SRC_COLOR, GL_ONE);
				 // glBlendFunc(GL_DST_COLOR, GL_ZERO);
				// glBlendFunc(GL_DST_COLOR, GL_ZERO);
				// glBlendFunc(GL_ONE, GL_ONE);
				// glBlendFunc(GL_SRC_COLOR, GL_ONE);
	//glDisable(GL_BLEND);

	             AddTextura(pTexturePack[2]);
				 pFruct->DrawApple(NULL);
}
void ShowSnake()
{
                //   glEnable(GL_BLEND);
				  // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                 //  glBlendFunc(GL_SRC_COLOR, GL_ONE);
	//glDisable(GL_BLEND);

	             AddTextura(pTexturePack[0]);
				 pSnake->DrawHead();  

				 AddTextura(pTexturePack[1]);
				 pSnake->DrawSnake();
}
void DrawStone()
{

	 
	// for(int i=0;i<10;i++)
	//glEnable(GL_BLEND);
AddTextura(pTexturePack[5]);
		 //pStone->DrawStone();
//pStone->DrawApple(&pStone->GetPosStone());
pStone->DrawStone();

}
void display()
{
		turn = true;
	    deltaTime -= 1;
    	pSnake->Tick();
   ResetGame();
  // ChangeProjection(); //for part system
				 	
				 // добавим освещение к голове что бы как фонарик или прожектор светил при движении
			    //  pLight->SetPosLight(pSnake->GetPosHeadX());
			//	DrawBack(); 
				if ( deltaTime % 50 ) { DrawBonus(); }

				 ShowSnake(); 
  DrawLife(); 
				 DrawFruct(); 

               

				 DrawStone();

				// DrawPartSys();
			     GameLogic();		

			 glutPostRedisplay();
			 glutSwapBuffers(); 
	}  
void CalcFPS()
{
	frame++;
 
	NowTime = glutGet(GLUT_ELAPSED_TIME);

	/*if (NowTime - OldTime > (deltaTime % 15))
	               {
		             DrawBonus();
					
					
	                }*/
				
 
	if (NowTime - OldTime > 250) 
	{
		
		display();
		

		OldTime = NowTime;	
		frame = 0;
	}

	glutPostRedisplay();
}
void getkeys_down(unsigned char key,int x,int y)
{
	switch ( key )
	{
	case 'g' : { pGame->SetStateGame(GAME); pGameData->lifes = 3; pGame->SetScore(0); pGameData->Score = 0; pSnake->ResetSnake();  TimeDraw = StartTime; } break;
	case 'm' : pGame->SetStateGame(STARTMENU); ShowMenu(); break;
	case '1' : glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
	case '2' : glBlendFunc(GL_ONE, GL_ONE); break;
	case '3' : glBlendFunc(GL_DST_COLOR, GL_ZERO); break;
	case '4' : glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
	case '5' : glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); break;
    case 'b' : glEnable(GL_BLEND); glBlendFunc(GL_ZERO,  GL_SRC_ALPHA_SATURATE); break;
	case 't' : TimeDraw -= 10.0f; break;
	case 27  : exit(0); break; //State = STARTMENU; ResetGame(); lifes = 3; break;  //exit(0); break;
}
}
void Drawtimer(int = 1)
{
		turn = true;

	    deltaTime -= 1;
    	pSnake->Tick();

    
  
        glutTimerFunc(TimeDraw, Drawtimer, 1);
}
void keyses(int key,int x,int y)
{
	switch (key)
	{
	         case GLUT_KEY_UP : if ( pGame->GetStateGame() == GAME ) { if (pSnake->GetDir() != 3 && turn) {pSnake->SetDir(0); turn = false;}}  break;

		   case GLUT_KEY_DOWN : if ( pGame->GetStateGame() == GAME ) { if (pSnake->GetDir() != 0 && turn) {pSnake->SetDir(3); turn = false;}}  break;

		   case GLUT_KEY_LEFT : if ( pGame->GetStateGame() == GAME ) { if (pSnake->GetDir() != 2 && turn) {pSnake->SetDir(1); turn = false;}}  break;

		  case GLUT_KEY_RIGHT : if ( pGame->GetStateGame() == GAME ) {if (pSnake->GetDir() != 1 && turn) {pSnake->SetDir(2); turn = false;}}  break;

		   case GLUT_KEY_F1 :    TimeDraw -= 0.25f; glutTimerFunc(TimeDraw,Drawtimer,1); break;

           case GLUT_KEY_F2 :    TimeDraw += 0.25f; glutTimerFunc(TimeDraw,Drawtimer,1); break;	

	}
}
void Mouse(int state,int button,int x,int y)
{


	if ( button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
	{
      if (TargetInButton(x, y))
	{
                    // logFile<< LogSpace::color("gray") << LogSpace::color("green") << "Is target in button!!! " <<"x "<< x<<"y "<<y << LogSpace::endl;
			  
		pGame->SetStateGame(GAME);
	}

	}

	
}
void LoadResources()
{
	if ( !backMusic.openFromFile("Data/backmusic.ogg"))
	                                                          {MessageBox(0,L"Not found music file",L"info",MB_OK);}
        
	if (PlayMusicOn ) backMusic.play();
	                  backMusic.setLoop(true);

	 if (!collisionBuff.loadFromFile("Data/collision.wav")) 
	                                                          {MessageBox(0,L"Not found collision.wav file",L"info",MB_OK);}
	 if (!eatBuff.loadFromFile("Data/eat-2.wav"))
	                                                          {MessageBox(0,L"Not found eat.wav file",L"info",MB_OK);}

	 if (!gameoverBuff.loadFromFile("Data/gong.wav"))
	                                                          {MessageBox(0,L"Not found gameover.wav file",L"info",MB_OK);}

	 
	 pLdrTexture->LoadTexture(pTexturePack[0],"Data/head.tga");
	 pLdrTexture->LoadTexture(pTexturePack[1],"Data/body.tga");
     pLdrTexture->LoadTexture(pTexturePack[2],"Data/Apple-2.tga");
     pLdrTexture->LoadTexture(pTexturePack[3],"Data/back.tga"); 
	 pLdrTexture->LoadTexture(pTexturePack[4],"Data/bonus.tga");
	 pLdrTexture->LoadTexture(pTexturePack[5],"Data/stone2.tga");

	  for(int i=0;i<6; i++)
	  {
	     glEnable(GL_TEXTURE_2D);
		 glGenTextures(1, &pTexturePack[i]->texID);

	  }

}
void initGL()
{
  glClearColor(0, 0, 0, 0);
 // glEnable(GL_DEPTH_TEST);
 // glEnable(GL_LIGHTING);
 // glEnable(GL_LIGHT0);
  glEnable(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);



 // glEnable(GL_BLEND);
}
void GameInit()
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ZERO,  GL_SRC_ALPHA_SATURATE);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE);

	   pGameData = new GameData;

for(int i=0;i<6;i++)
  pTexturePack[i] = new Texture;

         pFruct = new Fruct();
         pSnake = new Snake(*pFruct);
         pGame  = new Game();
	pLdrTexture = new Quad();
         pBonus = new Bonus();
		 pStone = new Stone();

	pGameData->FructOnLevel[0] = 5;
	pGameData->FructOnLevel[1] = 7;
	pGameData->lifes = 4;

	pGame->SetStateGame(GAME);

	TimeDraw = StartTime;
	pFruct->New();  
	pBonus->NewBonus();

	pStone->NewStone();

	LoadResources();

	pSnake->dx = 10;
	pSnake->dy = 10;
	

     eatSound.setBuffer(eatBuff);
	 collisionSound.setBuffer(collisionBuff);
	 gameoverSound.setBuffer(gameoverBuff);
	
	 typedef BOOL (APIENTRY * wglSwapIntervalEXT_Func)(int);
wglSwapIntervalEXT_Func wglSwapIntervalEXT =
  wglSwapIntervalEXT_Func(wglGetProcAddress("wglSwapIntervalEXT"));
if(wglSwapIntervalEXT) wglSwapIntervalEXT(0); // 1 - чтобы включить  vsync

}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR pCmdLine,int nShowCmd)
{
	int argc=0; char** argv=0;

glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_RGB | GLUT_DEPTH );
glutInitWindowSize (w, h);
glutCreateWindow ("Snake v 1.0"); 
hWnd = FindWindow(L"GLUT",L"OpenGL Application");
hDC = GetDC(hWnd);

  ourtext = new Font(hDC,"times",10,15,30); 
  initGL();
  GameInit();
glutKeyboardFunc(getkeys_down);
glutSpecialFunc(keyses);
glutDisplayFunc (CalcFPS);
glutMainLoop();
}
