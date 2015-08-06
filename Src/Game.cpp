#include "Game.h"

Game::Game(void):m_life(4),m_score(0),m_StateGame(2)
{

}
Game::~Game(void)
{
}
void Game::SetLife(const int life_)
{
	m_life = life_;
}
int Game::GetLife() const
{
	return m_life;
}
 int Game::GetScore() const
{
	return m_score;
}
void Game::SetScore(const int score_)
{
	m_score = score_;
}
int Game::GetStateGame() const
{
	return m_StateGame;
}
void Game::SetStateGame(const int state_)
{
	m_StateGame = state_;

//const int LOGO = 1;
//const int GAME = 2;
//const int LEVELCOMPLETE = 3;
//const int GAMEOVER = 4;
//const int STARTMENU = 5;
//const int ENDGAME   = 6;


}


