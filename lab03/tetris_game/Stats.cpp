#include "Stats.h"

constexpr unsigned LINES_TO_NEXT_LEVEL = 10;
constexpr Vec2d NEXT_FIGURE_POS = {13, 10};

Stats::Stats()
	: m_scores(0)
	, m_level(1)
	, m_linesLeft(LINES_TO_NEXT_LEVEL)
	, m_nextFigure(std::make_shared<Figure>(GetRandomFigureType(), NEXT_FIGURE_POS, GenerateRandomColor3d()))
{}

void Stats::AddReachedLines(unsigned count)
{
	if (count == 1)
	{
		m_scores += 10;
	}
	if (count == 2)
	{
		m_scores += 30;
	}
	if (count == 3)
	{
		m_scores += 70;
	}
	if (count == 4)
	{
		m_scores += 150;
	}

	if (count >= m_linesLeft)
	{
		m_linesLeft = LINES_TO_NEXT_LEVEL;
		m_level++;
	}
	else
	{
		m_linesLeft -= count;
	}
}

void Stats::UpdateNextFigure()
{
	*m_nextFigure = Figure(GetRandomFigureType(), NEXT_FIGURE_POS, GenerateRandomColor3d());
}

std::shared_ptr<Figure> Stats::GetNextFigure()
{
	return m_nextFigure;
}

unsigned Stats::GetLinesLeft()
{
	return m_linesLeft;
}

unsigned Stats::GetLevel()
{
	return m_level;
}

unsigned Stats::GetScores()
{
	return m_scores;
}