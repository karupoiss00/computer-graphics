#include "TetrisGame.h"
#include "Rotate.h"

constexpr unsigned MAX_LEVEL = 11;
constexpr unsigned MAX_DELAY = 550;
constexpr unsigned LEVEL_DELAY_STEP = 50;

TetrisGame::TetrisGame()
	: m_field(std::make_shared<Field>())
	, m_stats(std::make_shared<Stats>())
	, m_figure(std::make_shared<Figure>(GetRandomFigureType(), Vec2d{4, 0}, GenerateRandomColor3d()))
	, m_paused(false)
	, m_state(GameState::PLAYING)
{
}

void TetrisGame::Update()
{
	if (IsPaused() || IsGameOver() || IsGameWon())
	{
		return;
	}

	auto pos = m_figure->GetPosition();
	Vec2d nextPos = { pos.x, pos.y + 1 };
	bool canDrop = m_field->CanPutFigure(nextPos, m_figure->GetData());

	if (canDrop)
	{
		m_figure->SetPosition(nextPos);
	}
	else if (pos.y == 0)
	{
		m_state = GameState::OVER;
	}
	else 
	{
		m_field->PutFigure(m_figure->GetPosition(), m_figure->GetData());

		UpdateFigure();

		auto removedLines = m_field->Update();
		m_stats->AddReachedLines(removedLines);

		if (m_stats->GetLevel() == MAX_LEVEL)
		{
			m_state = GameState::WON;
		}
	}
}

unsigned TetrisGame::GetUpdateDelay()
{
	unsigned level = m_stats->GetLevel();

	return MAX_DELAY - LEVEL_DELAY_STEP * level;
}

void TetrisGame::SetPaused(bool paused)
{
	m_paused = paused;
}

bool TetrisGame::IsPaused()
{
	return m_paused;
}

bool TetrisGame::GameStopped()
{
	return IsPaused() || IsGameWon() || IsGameOver();
}

void TetrisGame::UpdateFigure()
{
	double fieldWidth = double(m_field->GetWidth());
	double fieldHeight = double(m_field->GetHeight());
	double startX = fieldWidth / 2 - m_figure->GetData()[0].size() / 2;

	*m_figure = *m_stats->GetNextFigure();
	m_figure->SetPosition({ startX, 0 });

	m_stats->UpdateNextFigure();
}

void TetrisGame::MoveFigureLeft()
{
	if (GameStopped())
	{
		return;
	}

	auto pos = m_figure->GetPosition();
	Vec2d nextPos = { pos.x - 1, pos.y };
	bool canMove = m_field->CanPutFigure(nextPos, m_figure->GetData());

	if (canMove) 
	{
		m_figure->SetPosition(nextPos);
	}
}

void TetrisGame::MoveFigureRight()
{
	if (GameStopped())
	{
		return;
	}

	auto pos = m_figure->GetPosition();
	Vec2d nextPos = { pos.x + 1, pos.y };
	bool canMove = m_field->CanPutFigure(nextPos, m_figure->GetData());

	if (canMove)
	{
		m_figure->SetPosition(nextPos);
	}
}

void TetrisGame::MoveFigureDown()
{
	if (GameStopped())
	{
		return;
	}

	auto pos = m_figure->GetPosition();
	Vec2d nextPos = { pos.x, pos.y + 1 };
	bool canMove = m_field->CanPutFigure(nextPos, m_figure->GetData());

	if (canMove)
	{
		m_figure->SetPosition(nextPos);
	}
}

void TetrisGame::RotateFigure()
{
	if (GameStopped())
	{
		return;
	}

	auto rotatedData = RotateMatrix(m_figure->GetData());

	if (m_field->CanPutFigure(m_figure->GetPosition(), rotatedData))
	{
		m_figure->Rotate();
	}
}

std::shared_ptr<Field> TetrisGame::GetField()
{
	return m_field;
}

std::shared_ptr<Figure> TetrisGame::GetFigure()
{
	return m_figure;
}

std::shared_ptr<Stats> TetrisGame::GetStats()
{
	return m_stats;
}

bool TetrisGame::IsGameOver()
{
	return m_state == GameState::OVER;
}

bool TetrisGame::IsGameWon()
{
	return m_state == GameState::WON;
}

void TetrisGame::Restart()
{
	if (m_state == GameState::PLAYING)
	{
		return;
	}

	m_field->Clear();
	m_stats->Reset();
	m_state = GameState::PLAYING;
	m_paused = false;

	UpdateFigure();
}