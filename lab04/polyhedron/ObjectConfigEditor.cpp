#include "pch.h"
#include "ObjectConfigEditor.h"

ObjectConfigEditor::ObjectConfigEditor(ObjectConfig& cfg)
    : m_config(cfg)
    , m_opened(true)
{
}

void ObjectConfigEditor::Render()
{
    ImGui::SetNextWindowSize(ImVec2(400, 220));

    if (!ImGui::Begin("Object Configuration Editor", &m_opened, ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
        return;
    }

    ImGui::SliderFloat("Object size", &m_config.m_size, 0.1f, 2.0f);

    ImGui::End();
}
