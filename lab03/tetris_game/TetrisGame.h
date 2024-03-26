#pragma once
#include <memory>
#include "IDrawable.h"
#include "Vec.h"
#include "Figure.h"
#include "Field.h"
#include "Stats.h"

enum class GameState
{
	PLAYING,
	OVER,
	WON,
};

class TetrisGame
{
public:
	TetrisGame();

	void Restart();
	void Update();
	void SetPaused(bool paused);
	void MoveFigureLeft();
	void MoveFigureRight();
	void MoveFigureDown();
	void RotateFigure();

	std::shared_ptr<Field> GetField();
	std::shared_ptr<Figure> GetFigure();
	std::shared_ptr<Stats> GetStats();
	unsigned GetUpdateDelay();
	bool IsGameOver();
	bool IsGameWon();
	bool IsPaused();

private:
	bool GameStopped();
	void UpdateFigure();

	std::shared_ptr<Field> m_field;
	std::shared_ptr<Figure> m_figure;
	std::shared_ptr<Stats> m_stats;
	bool m_paused;
	GameState m_state;
};