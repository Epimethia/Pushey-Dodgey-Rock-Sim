#include "MenuLevel.h"
#include "TextLabel.h"
#include "Sprite.h"
#include "Camera.h"

MainMenu::MainMenu() {
	m_pBackground = std::make_shared<Sprite>();
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
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
	m_pBackground->Initialize("Resources/Images/MenuBackground.png");
	MenuTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(640.0f, 605.0f));
	MenuTitle->SetScale(2.0f);

}

void MainMenu::Render()
{
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);
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
