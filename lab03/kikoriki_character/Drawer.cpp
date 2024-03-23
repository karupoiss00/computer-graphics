#define _USE_MATH_DEFINES
#include <cmath>
#include <gl/glut.h>
#include "Drawer.h"

constexpr double APPROX_ELLIPSE_COUNT = 100000;

void DrawFilledEllipse(double x, double y, double rx, double ry)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y);

    for (double i = 0; i <= APPROX_ELLIPSE_COUNT; ++i) 
    {
        double theta = 2.0f * M_PI * i / APPROX_ELLIPSE_COUNT;
        double dx = rx * cos(theta);
        double dy = ry * sin(theta);
        glVertex2d(x + dx, y + dy);
    }

    glEnd();
}

void DrawBezierPolygon(std::vector<std::array<double, 3>> const& points, bool fill, bool drawPoints)
{
	using Point = GLdouble[3];
	// не использовать new и delete, использовать .data() у vecctor
	GLdouble(*ctrlPoints)[3] = new GLdouble[points.size()][3];

	for (size_t i = 0; i < points.size(); ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			ctrlPoints[i][j] = points[i][j];
		}

		if (drawPoints)
		{
			auto p = points[i];
			DrawFilledEllipse(p[0], p[1], 0.1, 0.1);
		}
	}

	glMap1d(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, points.size(), &ctrlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	if (fill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
	}

	// магические числа убрать
	for (int i = 0; i <= 30; i++)
	{
		glEvalCoord1d(i / 30.0);
	}

	glEnd();

	delete[] ctrlPoints;
}