#pragma once

class Stats
{
public:
	Stats();

	void AddReachedLines(unsigned count);

	unsigned GetLinesLeft();
	unsigned GetLevel();
	unsigned GetScores();
private:
	unsigned m_scores;
	unsigned m_level;
	unsigned m_linesLeft;
};