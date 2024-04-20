#include <glm/glm.hpp>
#include "PlayerState.h"

PlayerState::PlayerState(Player const& player)
	: m_player(player)
{

}

void PlayerState::Render(bool& opened) const
{
    if (!opened)
    {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(320, 60));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.3f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    if (!ImGui::Begin("Player", nullptr,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
    ))
    {
        ImGui::End();
        return;
    }

    auto position = m_player.GetPosition();
    auto velocity = m_player.GetVelocity();

    ImGui::TextColored(
        ImVec4(1, 0, 0, 1), 
        "Position: [ %03f, %03f, %03f ]",
        position.x, position.y, position.z
    );
    ImGui::TextColored(
        ImVec4(1, 0, 0, 1),
        "Velocity: [ %03f, %03f, %03f ]",
        velocity.x, velocity.y, velocity.z
    );
    ImGui::TextColored(
        ImVec4(1, 0, 0, 1),
        "Jumping: %01d",
        m_player.IsJumping()
    );
    ImGui::End();

    ImGui::PopStyleColor(2);
}