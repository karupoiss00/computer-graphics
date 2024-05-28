#include "stdafx.h"
#include "Renderer.h"
#include "FrameBuffer.h"

using std::mutex;

CRenderer::~CRenderer(void)
{
	// ������������� ������ �������� ������, ���� �� ��� �� ����������
	Stop();
}

// ����������� �� � ������ ������ ���������� ����������� � ������ �����?
bool CRenderer::IsRendering() const
{
	return m_rendering;
}

// ���������� �� ����, ���������� � ������������� ���������� ������
bool CRenderer::IsStopping() const
{
	// ��������� ���������������� ������� �������� ���������� m_stopping
	return m_stopping;
}

bool CRenderer::SetRendering(bool rendering)
{
	bool expected = !rendering;
	return m_rendering.compare_exchange_strong(expected, rendering);
}

bool CRenderer::SetStopping(bool stopping)
{
	bool expected = !stopping;
	return m_stopping.compare_exchange_strong(expected, stopping);
}

bool CRenderer::GetProgress(unsigned& renderedChunks, unsigned& totalChunks) const
{
	// ����������� ������� �� ����� ������ ������� ������
	std::lock_guard lock(m_mutex);

	// �������� ���������������� ������� �������� ����������
	// m_renderedChunks � m_totalChunks
	renderedChunks = m_renderedChunks;
	totalChunks = m_totalChunks;

	// ��������, ��� �� ����� ����������� ���� ����������
	return (totalChunks > 0) && (renderedChunks == totalChunks);
}

/*
��������� �������� ������ �� ���������� ����������� � ������ �����
*/
void CRenderer::RenderFrame(CFrameBuffer& frameBuffer)
{
	// ���������� ������ � ������ ������ �����, ����� ������ ��� �� ��������
	// ������ ������ CFrameBuffer
	const int width = frameBuffer.GetWidth();
	const int height = frameBuffer.GetHeight();

	/*
	������ ����� ���������� ������ ����������� 
	��� ������ ����������� ����� ���������� 1 ������ ������ �����
	*/
	m_totalChunks = height;

	// ��������� ��� ������ ������ �����
	// ��� ���������� ��������� OpenMP �������� ����� �� ������� �����������
	// ����� ����������� � ������������ �������
#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic)
#endif
	for (int y = 0; y < height; ++y)
	{
		std::uint32_t* rowPixels = nullptr;

		// �������������� ������ � frameBuffer �� ��������������� �������
#ifdef _OPENMP
#pragma omp critical
#endif
		{
			// �������� ����� ������ y-� ������ � ������ �����
			rowPixels = frameBuffer.GetPixels(y);
		}

		// ���� �� ������� ����������� ������, ���� �������� ������ �� ������������
		// �� ��������� ���������� �����������
		// ���������� break ��� ������ �� ����� ����� ������������ ������ (����������� OpenMP)
		if (!IsStopping())
		{
			// ��������� ��� ������� � ������
			for (int x = 0; x < width; ++x)
			{
				// ��������� ���� �������� ������� � ���������� ��� � ����� �����
				rowPixels[size_t(x)] = CalculatePixelColor(x, y, width, height);
			}

			++m_renderedChunks;
		}
	}

	// ���������� ���� ���������
	SetStopping(false);
	// �������� �� ��������� ���������� �����������
	SetRendering(false);
}

// ��������� ������������ ����� � ������ ����� � ������� ������
// ���������� false, ���� ��� �� ���� ��������� ������ ����� ����������� ������
bool CRenderer::Render(CFrameBuffer& frameBuffer)
{
	// �������� ������� � ����� ����������
	if (!SetRendering(true))
	{
		// � ������ ������ ��� ���� ���������� ����������� � ������������ ������
		return false;
	}

	// ��������� ������ � ����� (��� �������� � ��������� ������) ������ ������
	// ������ �� ���������� ������ ������ Render
	std::lock_guard lock(m_mutex);

	// ������� ����� �����
	frameBuffer.Clear();

	// ���������� ���������� ������������ � ����� ���������� ������ �����������
	// ������������ � ���, ��� ��� ������ �� �������
	m_totalChunks = 0;
	m_renderedChunks = 0;

	// ���������� ������ �� ��������� ���������� �����������
	if (SetStopping(false))
	{
		// ���� ��� �� ������� �������� ������ ������ ������ �� ���������,
		// �������, ��������� ���� "���� ���������� �����������"
		SetRendering(false);
		return false;
	}

	// ��������� ����� RenderFrame � ������������ ������, ��������� ���
	// ����������� ����� ����������
	m_thread = std::jthread(
		&CRenderer::RenderFrame, // ����� ������ RenderFrame
		this, // ��������� this
		std::ref(frameBuffer)); // ������ �� frameBuffer

	// �������, ������� � ���, ��� ������� ���������� ����������� �������
	return true;
}

void CRenderer::Stop()
{
	// ���� ���������� ���������� �����������
	if (IsRendering())
	{
		// �������� ������, ������������ ���������� �����������, � �������������
		// ��������� ������
		SetStopping(true);

		// ���������� ��������� ������ �������� ������, ���� �� �� �������� ������
		if (m_thread.joinable())
		{
			m_thread.join();
		}

		// ���������� ���� ���������, ���� ����� �������� ���� ������ �� ������ SetStopping(true)
		SetStopping(false);
	}
}

// ��������� ���� ������� ������ �����
uint32_t CRenderer::CalculatePixelColor(int x, int y, unsigned frameWidth, unsigned frameHeight) const
{
	// ���� ����� � ��� �������� - ����������� ���� ����� �������� ������������
	// (��. ���������)

	// � ���������� ���� ����� ����� ��������� ������ ��� �������������
	// ���� ����, ����������� ����� ������ �������, ������ �����

	double x0 = 2.0 * x / frameWidth - 1.5;
	double y0 = 2.0 * y / frameHeight - 1.0;

	// �����������: ���������, �� �������� �� ������� ����� � ������� ������� ���������
	double rho = sqrt((x0 - 0.25) * (x0 - 0.25) + y0 * y0);
	double theta = atan2(y0, x0 - 0.25);
	double rhoC = 0.5 - 0.5 * cos(theta);
	if (rho <= rhoC)
	{
		return 0x000000;
	}

	double re = 0, im = 0;

	// ������� ���������� �������� "�������� ����� Zi � �������������"
	int iterCount = 10000;
	// ����������� ���������� ������������������ Z(i+1) = (Z(i))^2 + C, ���
	//	Z(0) = 0 + 0*i
	//	C = x0 + y0*i
	while ((iterCount > 0) && (re * re + im * im < 1e18))
	{
		double re1 = re * re - im * im + x0;
		im = 2 * re * im + y0;
		re = re1;
		--iterCount;
	}

	// ������������ ����� �� ������ ���������� ��������
	uint8_t r = static_cast<uint8_t>((iterCount / 3) & 0xff);
	uint8_t g = static_cast<uint8_t>(iterCount & 0xff);
	uint8_t b = static_cast<uint8_t>((iterCount / 2) & 0xff);
	uint8_t a = 0xff;
	return (a << 24) | (r << 16) | (g << 8) | b;
}
