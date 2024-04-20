#include <iostream>
#include "pch.h"
#include "GetFPS.h"
#include "RenderStats.h"

RenderStats::RenderStats()
{
}

void RenderStats::Render(bool& opened) const
{
    if (!opened)
    {
        return;
    }

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(70, 30));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    if (!ImGui::Begin("Render", nullptr, 
          ImGuiWindowFlags_NoResize 
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoMove
    ))
    {
        ImGui::End();
        return;
    }

    ImGui::TextColored(ImVec4(1, 0, 0, 1), "FPS: %03d", GetFPS());
    ImGui::End();

    ImGui::PopStyleColor(2);
}


