#include "pch.h"
#include "MobiusStrip.h"

constexpr unsigned MAXVRT = 10;

MobiusStrip::MobiusStrip()
{

}

void MobiusStrip::Render() const
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);

    float x = 0, y = 0, z = 0;

    double r = 0, t = 0;
    for (t = 0; t < (2 * M_PI) + 0.01; t += 0.005)
    {
        glBegin(GL_LINE_STRIP);
        for (r = -1; r <= 1; r += 0.005)
        {
            x = (cos(t)) * (2 + (r / 2) * cos(t / 2));
            y = (sin(t)) * (2 + (r / 2) * cos(t / 2));
            z = ((r / 2) * sin(t / 2));

            glColor3f(abs(x / 2), abs(y / 2), abs(z / 2));
            glVertex3f(x / 2.5, y / 2.5, z / 2.5);

        }
        glEnd();

    }
    for (r = -1; r <= 1; r += 0.005)
    {
        glBegin(GL_LINE_STRIP);
        for (t = 0; t < (2 * M_PI) + 0.01; t += 0.005)
        {

            x = (cos(t)) * (2 + (r / 2) * cos(t / 2));
            y = (sin(t)) * (2 + (r / 2) * cos(t / 2));
            z = ((r / 2) * sin(t / 2));

            glColor3f(abs(x / 2), abs(y / 2), abs(z / 2));
            glVertex3f(x / 2.5, y / 2.5, z / 2.5);
        }
        glEnd();
    }
}