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
#include "include/Light.h"
#include "include/model.h"
#include "include/AddTexture.h"
#include "include/Quad.h"
#include "include/DrawMeshCube.h"
#include "include\glm\glm.hpp"
#include "include\Bonus.h"


#pragma comment(lib,"/freeglut.lib")
#pragma comment(lib,"/sfml-audio-d.lib")

//#include <SFML\System.hpp>
//
//#ifdef _DEBUG
//      
//#pragma comment(lib,"sfml-system-d.lib")
//#else
//
//    #pragma comment(lib,"sfml-system.lib")
//  
//#endif


struct GameData
{
  int Score;
  int lifes;
  int level;
  int FructOnLevel[2];
};

Font *ourtext;
sf::SoundBuffer collisionBuff,eatBuff,moveBuff,gameoverBuff,collisionTailBuff;
sf::Sound collisionSound,eatSound,moveSound,gameoverSound,collisionTail;
sf::Music backMusic;




 bool DEMO = false;
 const int countTextures = 20;

GameData *pGameData;
Texture    *snakeTexture;
Texture    *fructTexture;
Texture    *snakeHead;
Texture    *pBackTexture;
Texture    *bonusTexture;
Texture    *partSysTexture;
Texture    *texturePack[countTextures];
GLfloat  NormalArraySnake[200];
GLfloat  NormalArrayApple[2];


Bonus *pBonus;
Fruct *pFruct;
Snake *pSnake;
Game  *pGame;
Light *pLight;
Model *pModel;
Quad  *pLdrTexture;
std::vector<int> face(1);
Vec3f v0;
int  arrayIndex[1];
float pTxt[16];


bool turn(false);
bool PlayMusicOn(false);
HDC  hDC;

float static deltaTime(60);

const int StartTime(150);
const int LOGO = 1;
const int GAME = 2;
const int LEVELCOMPLETE = 3;
const int GAMEOVER = 4;
const int STARTMENU = 5;
const int ENDGAME   = 6;

bool StartGame(false);
bool GameOver(false);

int State(GAME);
int TimeDraw(150);
int StartPartSys(0);

int N=30,M=20;
int Scale=25;

int w = Scale*N;
int h = Scale*M;

static float i(1.0f);
static float j(1.0f);
glm::vec3 posHead,posBonus;

/***  Particle System Data ***/

const int MAX_PARTICLES = 1000;

typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
particles;							// Particles Structure

particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

static GLfloat colors[12][3]=		// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

int depthScreen(-100);
const int stepDepthScreen(5);

bool	keys[256];					// Array Used For The Keyboard Routine
bool	active=TRUE;				// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;			// Fullscreen Flag Set To Fullscreen Mode By Default
bool	rainbow=true;				// Rainbow Mode?
bool	sp;							// Spacebar Pressed?
bool	rp;							// Enter Key Pressed?

float	slowdown=2.0f;				// Slow Down Particles
float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	 zoom = -5;//zoom=-40.0f;				// Used To Zoom Out

GLuint	col;						// Current Color Selection
GLuint	delay;						// Rainbow Effect Delay


/***  Particle System Data ***/

void ResetGame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor4f(0,0,0,0);


}
void InitPartSys()
{
	int loop;

	pLdrTexture->LoadTexture(partSysTexture,"Data\\particle.tga");

	glViewport(0,0,w,h);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,200.0f);

	

glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D,partSysTexture->texID);			// Select Our Texture



	for (loop=0;loop<MAX_PARTICLES;loop++)				// Initials All The Textures
	{
		particle[loop].active=true;								// Make All The Particles Active
		particle[loop].life=1.0f;								// Give All The Particles Full Life
		particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particle[loop].xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg=0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg=-0.8f;								// Set Vertical Pull Downward
		particle[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
	}

}
void DrawPartSys()
{
  int loop;

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();

		gluLookAt(0,0,depthScreen,0,0,0,1,0,0);


	for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			float x=particle[loop].x;						// Grab Our Particle X Position
			float y=particle[loop].y;						// Grab Our Particle Y Position
			float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particle[loop].life<0.0f)					// If Particle Is Burned Out
			{
				particle[loop].life=1.0f;					// Give It New Life
				particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle[loop].x=0.0f;						// Center On X Axis
				particle[loop].y=0.0f;						// Center On Y Axis
				particle[loop].z=0.0f;						// Center On Z Axis
				particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
				particle[loop].r=colors[col][0];			// Select Red From Color Table
				particle[loop].g=colors[col][1];			// Select Green From Color Table
				particle[loop].b=colors[col][2];			// Select Blue From Color Table
			}

						// If Number Pad 8 And Y Gravity Is Less Than 1.5 Increase Pull Upwards
			if (keys[VK_NUMPAD8] && (particle[loop].yg<1.5f)) { particle[loop].yg+=0.01f; keys[VK_NUMPAD8] = false; }

			// If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
			if (keys[VK_NUMPAD2] && (particle[loop].yg>-1.5f)) { particle[loop].yg-=0.01f; keys[VK_NUMPAD2] = false; }

			// If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
			if (keys[VK_NUMPAD6] && (particle[loop].xg<1.5f)) { particle[loop].xg+=0.01f; keys[VK_NUMPAD6] = false; }

			// If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
			if (keys[VK_NUMPAD4] && (particle[loop].xg>-1.5f)) { particle[loop].xg-=0.01f; keys[VK_NUMPAD4] = false; }

			if (keys[VK_F1])
			{
			col++;							// Change The Particle Color
					if (col>11)	col=0;	
					keys[VK_F1] = false;
			}

			if (keys[VK_TAB])										// Tab Key Causes A Burst
			{
				particle[loop].x=0.0f;								// Center On X Axis
				particle[loop].y=0.0f;								// Center On Y Axis
				particle[loop].z=0.0f;								// Center On Z Axis
				particle[loop].xi=float((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
				particle[loop].yi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
				particle[loop].zi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis

				keys[VK_TAB] = false;
			}

		
}
	}
}


/* добавить флаг вкл системы по нему вкл или выкл эффекты из фу-ии возвращать нужные типы данных создать их локальными что есть правильно */
/* главное не забыть что можем вернуть пустые данные ))) */
void InitMagicParticles()
{

	//#include "platform_win_posix.h"
//#include "mp_wrap.h"

//HM_EMITTER cur=0;

//RECT rect;

//DWORD StartTimePS;
//MP_Emitter* emitter;

		/*GetClientRect(hWnd,&rect);
	int client_wi=rect.right-rect.left;
	int client_he=rect.bottom-rect.top;*/

 //int psw(750),psh(500),bits(32);

	//MP_Device_WRAP device(psw,psh);//client_wi, client_he, hWnd, 32);
	//device.Create();

	//MP_Manager& MP=MP_Manager::GetInstance();

	//MP_Platform* platform=new MP_Platform_WIN_POSIX;
	//#ifdef MAGIC_3D
	//int axis=MAGIC_pXpYpZ;
	//#else
	//int axis=MAGIC_pXnY;
	//#endif
	//MP.Initialization(axis, platform, MAGIC_INTERPOLATION_ENABLE, MAGIC_CHANGE_EMITTER_DEFAULT, 1024, 1024, 1, 1.f, 0.1f, true);

	//// eng: find of all ptc-files in folder
	//// rus: поиск всех ptc-файлов в папке
	//MP.LoadAllEmitters();

	//MP.RefreshAtlas();

	//MP.CloseFiles();

	//MP.Stop();

	//cur=MP.GetFirstEmitter();

	// emitter = MP.GetEmitter(cur);
	//emitter->SetState(MAGIC_STATE_UPDATE);

	//device.SetScene3d();
	//
	//#ifndef MAGIC_3D
	//// eng: locate emitters the same as editor
	//// rus: расставляем эмиттеры также, как они стояли в редакторе
	//HM_EMITTER hmEmitter=MP.GetFirstEmitter();
	//while (hmEmitter)
	//{
	//	Magic_CorrectEmitterPosition(hmEmitter,w,h);//client_wi, client_he);
	//	hmEmitter=MP.GetNextEmitter(hmEmitter);
	//}
	//#endif
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

	 ///
	// std::string posstr = GetStr("PosHeadX: ",pSnake->GetPosHeadX());
	
	// ourtext->put(550, 380, 1.0f, posstr.c_str());

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
 	AddTextura(pBackTexture);
	boxFon(0,0,25*30,25*20);
	//free(pBackTexture->imageData);
	
}
void GameLogic()
{
	 if (deltaTime <= 0.1f || pGame->GetStateGame() == GAMEOVER  ) { pGame->SetStateGame(GAMEOVER); ResetGame(); ShowGameOver(); }  
		         pBonus->GetPosBonus(posBonus);
				 pSnake->GetPosHead(posHead);

	 //if (posHead == posBonus) 
				 //{
					// /* enable particle system on 5000 ms */

					// StartPartSys = deltaTime;
				 //
				 //}


	        if (pSnake->GetOutWall() && pGameData->lifes == 0) { pGame->SetStateGame(GAMEOVER);  ResetGame(); ShowGameOver(); }
	        if (pSnake->GetOutWall() && pGameData->lifes != 0) { collisionSound.play(); pGame->SetLife(pGameData->lifes -= 1); pGameData->Score = 0; 
			                                                     pSnake->SetOutWall(false); }					
											
			if (pSnake->IsCollision())       {  eatSound.play(); pGame->SetScore(pGameData->Score += 100); pSnake->SetCollision(false);  }
			if (pSnake->GetIsHeadWithTail()) { pGameData->Score = 0; pSnake->ResetSnake(); pSnake->SetHeadWithTail(false); }	


}
void DrawFruct()
{
		         AddTextura(fructTexture);
				 pFruct->DrawApple();
}
void ChangeProjection()
{
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);

  //gluLookAt(0,0,0,0,0,0,1,0,0);
}
void ShowSnake()
{
 

	             AddTextura(snakeHead);
				 pSnake->DrawHead();  

				 AddTextura(snakeTexture);
				 pSnake->DrawSnake();
}
//void ShowPartSys(MP_Manager &MP)
//{
//	           MP.UpdateByTimer();
//
//				MP.Render();
//
//				emitter=MP.GetEmitter(cur);
//				if (emitter->GetState()==MAGIC_STATE_STOP)
//				{
//					cur=MP.GetNextEmitter(cur);
//					if (!cur)
//						cur=MP.GetFirstEmitter();
//
//					emitter=MP.GetEmitter(cur);
//					emitter->SetState(MAGIC_STATE_UPDATE);
//				}
//}

void BindAllTextures(int indx,Texture *PointToarray)
{
	addAllTextures(indx,texturePack[0]);
}

void display()
{
   ResetGame();
  // ChangeProjection();
				 	
				 // добавим освещение к голове что бы как фонарик или прожектор светил при движении
			    //  pLight->SetPosLight(pSnake->GetPosHeadX());
			   

				// DrawBack(); // есть утечка кучи!!!
			//	DrawLife(); 

				// ShowSnake(); // есть утечка кучи!!!

				// DrawFruct(); // есть утечка кучи!!!

				 DrawPartSys();

			   //  GameLogic();		

			 glutPostRedisplay();
			 glutSwapBuffers(); 
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
	case 'l' : pLight->OnOffLight(true); break;
	case 'L' : pLight->OnOffLight(false); break;
	case 't' : TimeDraw -= 10.0f; break;

	case 'w' : keys[VK_NUMPAD8] = true; break;
	case 'a' : keys[VK_NUMPAD2] = true; break;
	case 's' : keys[VK_NUMPAD6] = true; break;
	case 'd' : keys[VK_NUMPAD4] = true; break;
	case 'z' : keys[VK_TAB] = true; break;
	case 'q' : keys[VK_F1] = true; break;
	case '+' : if (depthScreen < 0) depthScreen = 100; if (depthScreen > 200) depthScreen = 100;   depthScreen -= stepDepthScreen; break;
	case '-' : if (depthScreen < 0) depthScreen = 100;  depthScreen += stepDepthScreen; break;


			

	case 27  : exit(0); break; //State = STARTMENU; ResetGame(); lifes = 3; break;  //exit(0); break;
}
}
void Drawtimer(int = 1)
{
		turn = true;

		//if (StartPartSys != 0)
		//{
		//	if (deltaTime < (StartPartSys-5000))
		//	{
		//		/* Disable part system */

		//	}
		//}
	    deltaTime -= 0.1f;
    	pSnake->Tick();
       // display();
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

     pLdrTexture->LoadTexture(snakeTexture,"Data/body.tga");
	 pLdrTexture->LoadTexture(fructTexture,"Data/Apple-2.tga");
	 pLdrTexture->LoadTexture(snakeHead,"Data/head.tga");
	 pLdrTexture->LoadTexture(pBackTexture,"Data/back.tga"); 
	 pLdrTexture->LoadTexture(bonusTexture,"Data/bonus.tga"); 


}
void DrawModel()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/* ====================================================== */ 

	/*for (int i=0; i<pModel->nfaces(); i++) 
	{
         face = pModel->face(i);

      for (int j=0; j<3; j++) 
       {
           v0 = pModel->vert(face[j]);

       }
     }
*/

	 // arrayIndex[0] = pModel->face(0);
	  v0 = pModel->vert(face[0]);
	  glColor3f(1.0f,0.0f,0.0f);

	

	  glVertexPointer(3,GL_FLOAT, sizeof(Vec3f)*pModel->nverts(),&pModel->vert(0));
	glDrawElements(GL_TRIANGLES, pModel->nfaces() * 3, sizeof(Vec3f)*12, &pModel->face(0));

	/* ====================================================== */ 
	//glDisableClientState(GL_ARRAY_BUFFER);
	glEnableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glutSwapBuffers();
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
	snakeTexture = new Texture;
	fructTexture = new Texture;
	   snakeHead = new Texture;
    pBackTexture = new Texture;
	bonusTexture = new Texture;
partSysTexture   = new Texture;


         pFruct = new Fruct();
         pSnake = new Snake(*pFruct);
         pGame  = new Game();
         pLight = new Light();
	     pModel = new Model("C:\\mycube.obj");
	pLdrTexture = new Quad();

	for(int i=0;i<countTextures; i++)
	texturePack[i] = new Texture;

	//pLight->OnOffLight(true);
	pFruct->New();

	pSnake->dx = 10; pSnake->dy = 10;
	

	pGameData->FructOnLevel[0] = 5; pGameData->FructOnLevel[1] = 7;
	pGameData->lifes = 4;

	pGame->SetStateGame(GAME);

	 TimeDraw = StartTime;

	 eatSound.setBuffer(eatBuff);
	 collisionSound.setBuffer(collisionBuff);
	 gameoverSound.setBuffer(gameoverBuff);

	LoadResources();

	     pBonus = new Bonus();
		 AddTextura(bonusTexture);
		 pBonus->DrawBonus();
	
		 InitPartSys();

	   //InitMagicParticles();

}


HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;
HINSTANCE hPrevInstance;

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

//glutReshapeFunc(resizeWindow);
glutKeyboardFunc(getkeys_down);
glutSpecialFunc(keyses);
glutDisplayFunc (display);
//glutDisplayFunc(DrawModel);
glutMouseFunc(Mouse);
glutTimerFunc(TimeDraw,Drawtimer,1);
glutMainLoop();
}
