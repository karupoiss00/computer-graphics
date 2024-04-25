#include "pch.h"
#include "MainMenu.h"

constexpr double MENU_WIDTH = 200;
constexpr double MENU_HEIGHT = 70;

constexpr double BUTTON_WIDTH = 190;
constexpr double BUTTON_HEIGHT = 50;

MainMenu::MainMenu(
    IScreenProvider const& screenProvider,
    std::function<void()> onGameStart
)
	: m_onGameStartFn(onGameStart)
    , m_screenProvider(screenProvider)
{}

void MainMenu::DrawUI()
{
    auto windowSize = m_screenProvider.GetScreenSize();
    auto menuPos = ImVec2(
        windowSize.x / 2 - MENU_WIDTH / 2,
        windowSize.y / 2 - MENU_HEIGHT / 2
    );

    ImGui::SetNextWindowPos(menuPos);
    ImGui::SetNextWindowSize(ImVec2(MENU_WIDTH, MENU_HEIGHT));

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    if (!ImGui::Begin("MainMenu", nullptr,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoMove
    ))
    {
        ImGui::End();
        return;
    }
    
    bool startGame = ImGui::Button("Start", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT));

    ImGui::End();

    ImGui::PopStyleColor(2);

    if (startGame)
    {
        m_onGameStartFn();
    }
}