#pragma once
class Game
{
public:
	Game(void);
	~Game(void);

	void SetLife(const int life_);
	 int GetLife() const;
	void SetScore(const int score_);
	int  GetScore() const;
	int  GetStateGame() const;
	void SetStateGame(const int state_);

private:
	int m_life;
	int m_score;
	int m_StateGame;

};

