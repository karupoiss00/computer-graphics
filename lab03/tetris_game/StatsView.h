#pragma once
#include <memory>
#include <string>
#include "Drawer.h"
#include "IDrawable.h"
#include "CellView.h"
#include "Vec.h"
#include "Stats.h"
#include "FigureView.h"

class StatsView : public IDrawable
{
public:
	StatsView(std::shared_ptr<Stats> stats)
		: m_stats(stats)
		, m_nextFigureView(stats->GetNextFigure())
	{}

	void Draw()
	{
		glColor3d(0.1, 0.1, 0.1);
		glBegin(GL_POLYGON);
		glVertex2d(10, 0);
		glVertex2d(20, 0);
		glVertex2d(20, 20);
		glVertex2d(10, 20);
		glEnd();

		std::string countStr = "Scores: " + std::to_string(m_stats->GetScores());
		std::string levelStr = "Level: " + std::to_string(m_stats->GetLevel());
		std::string linesLeftStr = "Lines left: " + std::to_string(m_stats->GetLinesLeft());
		std::string nextFigure = "Next figure: ";

		glColor3d(0.8, 0.8, 0.8);
		DrawString(13, 5, countStr.data());
		DrawString(13, 6, levelStr.data());
		DrawString(13, 7, linesLeftStr.data());
		DrawString(13, 8, nextFigure.data());

		m_nextFigureView.Draw();
	}
private:
	FigureView m_nextFigureView;
	std::shared_ptr<Stats> m_stats;
};