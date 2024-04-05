#include "pch.h"
#include "MobiusStrip.h"

constexpr float DELTA = 0.015f;
constexpr unsigned MAXVRT = 10;

MobiusStrip::MobiusStrip(float size)
    : m_size(size)
{

}

void MobiusStrip::Render() const
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.5);

    float x = 0, y = 0, z = 0;

    float r = 0, t = 0;
    for (t = 0; t < (2 * M_PI) + 0.01; t += DELTA / 3)
    {
        glBegin(GL_LINE_STRIP);
        for (r = -1; r <= 1; r += DELTA)
        {
            x = (cosf(t)) * (2 + (r / 2) * cosf(t / 2));
            y = (sinf(t)) * (2 + (r / 2) * cosf(t / 2));
            z = ((r / 2) * sinf(t / 2));

            float rp[3] = { x, y, z };
            auto p = glm::make_vec3(rp);

            glColor3fv(glm::value_ptr(p));

            p *= m_size * 0.5;

            glVertex3fv(glm::value_ptr(p));
        }
        glEnd();

    }
    for (r = -1; r <= 1; r += DELTA / 3)
    {
        glBegin(GL_LINE_STRIP);
        for (t = 0; t < (2 * M_PI) + 0.01; t += DELTA)
        {
            x = (cosf(t)) * (2 + (r / 2) * cosf(t / 2));
            y = (sinf(t)) * (2 + (r / 2) * cosf(t / 2));
            z = ((r / 2) * sinf(t / 2));

            float rp[3] = { x, y, z };
            auto p = glm::make_vec3(rp);

            glColor3fv(glm::value_ptr(p));

            p *= m_size * 0.5;

            glVertex3fv(glm::value_ptr(p));
        }
        glEnd();
    }
}

void MobiusStrip::SetObjectSize(float size)
{
    m_size = size;
}