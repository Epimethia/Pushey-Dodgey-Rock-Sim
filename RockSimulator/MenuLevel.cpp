#include "MenuLevel.h"
#include "TextLabel.h"

MainMenu::MainMenu() {

}

MainMenu::~MainMenu()
{
	for (auto& it : MenuOptions) {
		it.reset();
	}
	MenuOptions.clear();
}

void MainMenu::Init()
{
	MenuTitle->SetText("Pushey Dodgey Rock Simulator");
	MenuTitle->SetPosition(glm::vec2(50.0f, 50.0f));
	MenuTitle->SetScale(10.0f);
}

void MainMenu::Render()
{
	MenuTitle->Render();
}

void MainMenu::Process()
{
	ProcessPlayerInput();
}

void MainMenu::AddOption()
{
}

void MainMenu::ProcessPlayerInput()
{
}
