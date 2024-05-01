#include "GameMenu.h"

constexpr double MENU_WIDTH = 204;
constexpr double MENU_HEIGHT = 120;

constexpr double BUTTON_WIDTH = 190;
constexpr double BUTTON_HEIGHT = 50;


GameMenu::GameMenu(
    IScreenProvider const& screenProvider,
    std::function<void()> onGoToMainMenu
)
    : m_onGoToMainMenu(onGoToMainMenu)
    , m_screenProvider(screenProvider)
{}

void GameMenu::Render(bool& opened) const
{
    if (!opened)
    {
        return;
    }

    auto windowSize = m_screenProvider.GetScreenSize();
    auto menuPos = ImVec2(
        float(windowSize.x / 2 - MENU_WIDTH / 2),
        float(windowSize.y / 2 - MENU_HEIGHT / 2)
    );

    ImGui::SetNextWindowPos(menuPos);
    ImGui::SetNextWindowSize(ImVec2(MENU_WIDTH, MENU_HEIGHT));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1.0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    if (!ImGui::Begin("GameMenu", nullptr,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoMove
    ))
    {
        ImGui::End();
        return;
    }

    bool resume = ImGui::Button("Resume", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT));
    bool exitToMenu = ImGui::Button("Exit to menu", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT));

    ImGui::End();

    ImGui::PopStyleColor(2);

    if (exitToMenu)
    {
        opened = false;
        m_onGoToMainMenu();
    }

    if (resume)
    {
        opened = false;
    }
}