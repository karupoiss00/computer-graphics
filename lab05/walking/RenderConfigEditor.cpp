#include "pch.h"
#include "RenderConfigEditor.h"

RenderConfigEditor::RenderConfigEditor(RenderConfig& cfg)
	: m_config(cfg)
{
}

void RenderConfigEditor::Render(bool& opened)
{
    if (!opened)
    {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(400, 260));

    if (!ImGui::Begin("Render Configuration Editor", &opened, ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
        return;
    }

    ImGui::SliderFloat("FOV", &m_config.m_fov, 1.f, 179.f);
    ImGui::SliderFloat("zFar", &m_config.m_zFar, 0.f, 200.f);
    ImGui::SliderFloat("zNear", &m_config.m_zNear, 0.f, 20.f);
    ImGui::ColorEdit3("Background Color", &m_config.m_backgroundColor[0]);
    ImGui::Checkbox("Show FPS", &m_config.m_showStats);

    ImGui::Separator();

    ImGui::Checkbox("Show Sky", &m_config.m_showSky);

    ImGui::Separator();

    ImGui::Checkbox("Show Fog", &m_config.m_showFog);
    ImGui::ColorEdit3("Fog Color", &m_config.m_fogColor[0]);
    ImGui::SliderFloat("Fog Density", &m_config.m_fogDensity, 0.f, 2.f);

    ImGui::End();
}


