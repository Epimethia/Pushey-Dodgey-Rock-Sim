#include "MenuLevel.h"
#include "TextLabel.h"
#include "Sprite.h"
#include "KeyboardInput.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SoundManager.h"


struct Option {
	std::shared_ptr<TextLabel> OptionText;
	glm::vec2 m_vUnselectedPos;
	glm::vec2 m_vSelectedPos;
	bool m_bSelected;

	Option(std::string _Text, glm::vec2 _UnselectedPos, glm::vec2 _SelectedPos) {
		m_vUnselectedPos = _UnselectedPos;
		m_vSelectedPos = _SelectedPos;
		OptionText = std::make_shared<TextLabel>(_Text, "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", m_vUnselectedPos);
		OptionText->SetScale(1.2f);
		m_bSelected = false;
	}

	void Render() {
		OptionText->Render();
	}

	void ToggleActive() {
		m_bSelected = !m_bSelected;

		if (m_bSelected) {
			OptionText->SetPosition(m_vSelectedPos);
			OptionText->SetScale(1.6f);
		}
		else {
			OptionText->SetPosition(m_vUnselectedPos);
			OptionText->SetScale(1.2f);
		}
	}
};

MainMenu::MainMenu() {
	m_pBackground = std::make_shared<Sprite>();
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
	CurrentOpt = 0;
}

MainMenu::~MainMenu()
{
	//for (auto& it : OptArr) {
	//	it.reset();
	//}
	MenuTitle.reset();
}

void MainMenu::Init()
{
	m_pBackground->Initialize("Resources/Images/MenuBackground2.png");
	MenuTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 800.0f));
	MenuTitle->SetScale(1.6f);

	OptArr[0] = std::make_shared<Option>("Play", glm::vec2(715.0f, 620.0f), glm::vec2(690.0f, 610.0f));

	OptArr[1] = std::make_shared<Option>("Option", glm::vec2(680.0f, 430.0f), glm::vec2(640.0f, 420.0f));
	//OptArr[1]->SetScale(1.2f);

	OptArr[2] = std::make_shared<Option>("Quit", glm::vec2(715.0f, 240.0f), glm::vec2(690.0f, 230.0f));
	//OptArr[2]->SetScale(1.2f);
	OptArr[0]->ToggleActive();
	SoundManager::GetInstance()->StartMenuBGM();
}

void MainMenu::Render()
{
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);
	MenuTitle->Render();
	for (int i = 0; i < 3; i++) {
		OptArr[i]->Render();
	}
}

void MainMenu::Process()
{
	if (Input::m_iSpecialKeyState[GLUT_KEY_UP] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		OptArr[CurrentOpt]->ToggleActive();
		if (CurrentOpt == 0) {
			CurrentOpt = 2;
		}
		else CurrentOpt--;
		OptArr[CurrentOpt]->ToggleActive();
	}
	else if (Input::m_iSpecialKeyState[GLUT_KEY_DOWN] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		OptArr[CurrentOpt]->ToggleActive();
		if (CurrentOpt == 2) {
			CurrentOpt = 0;
		}
		else CurrentOpt++;
		OptArr[CurrentOpt]->ToggleActive();
	}
	else if (Input::m_iKeyState['\r'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuClose();
		switch (CurrentOpt) {
		case 0: {
			SoundManager::GetInstance()->StopBGM();
			SceneManager::GetInstance()->InitializeScene(LEVEL1_SCENE);
			SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);
			break;
		}
		default:break;
		}
	}
	ProcessPlayerInput();
}

void MainMenu::AddOption()
{
}

void MainMenu::ProcessPlayerInput()
{
	Input::Update();
}
