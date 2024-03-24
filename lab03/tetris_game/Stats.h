#pragma once
#include <memory>
#include "Figure.h"

class Stats
{
public:
	Stats();

	void AddReachedLines(unsigned count);
	void UpdateNextFigure();

	unsigned GetLinesLeft();
	unsigned GetLevel();
	unsigned GetScores();
	std::shared_ptr<Figure> GetNextFigure();
private:
	unsigned m_scores;
	unsigned m_level;
	unsigned m_linesLeft;
	std::shared_ptr<Figure> m_nextFigure;
};