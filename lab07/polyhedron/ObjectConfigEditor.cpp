#include "pch.h"
#include "ObjectConfigEditor.h"

ObjectConfigEditor::ObjectConfigEditor(ObjectConfig& cfg)
    : m_config(cfg)
{
}

void ObjectConfigEditor::Render()
{
    ImGui::SetNextWindowSize(ImVec2(400, 160));

    if (!ImGui::Begin("Object Configuration Editor", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
        return;
    }

    SelectedObjectCombo();
    ImGui::SliderFloat("Object size", &m_config.m_size, 0.1f, 2.0f);

    bool needReload = ImGui::Button("Reload");

    ImGui::End();


    if (needReload) {
        m_config.m_onReloadFn();
    }
}


void ObjectConfigEditor::SelectedObjectCombo()
{
    const char* items[] = { "empty", "dodecahedron", "mobius strip", "canabola"};
    auto currentItem = m_config.m_selectedObject.c_str();

    if (ImGui::BeginCombo("selected object", currentItem))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (currentItem == items[n]);
            if (ImGui::Selectable(items[n], is_selected))
            {
                m_config.m_selectedObject = items[n];
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}