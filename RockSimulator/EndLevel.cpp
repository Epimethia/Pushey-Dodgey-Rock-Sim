#include "EndLevel.h"
#include "Sprite.h"
#include "KeyboardInput.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Option.h"

EndLevel::EndLevel()
{
	m_pBackground = std::make_shared<Sprite>();
	CurrentOpt = 0;
}

EndLevel::~EndLevel()
{
	for (auto& it : OptArr) {
		it.reset();
	}
	m_pBackground.reset();
}

void EndLevel::Init()
{
	m_pBackground->Initialize("Resources/Images/MenuBackground2.png");
	EndTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 800.0f));
	EndTitle->SetScale(1.6f);
	
	WinnerTitle = std::make_shared<TextLabel>("<Winning Player>", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 600.0f));	
	WinnerTitle->SetScale(1.6f);

	OptArr[0] = std::make_shared<Option>("Play Again", glm::vec2(630.0f, 430.0f), glm::vec2(565.0f, 420.0f));
	OptArr[1] = std::make_shared<Option>("Main Menu", glm::vec2(630.0f, 240.0f), glm::vec2(590.0f, 230.0f));
	OptArr[0]->ToggleActive();
}

void EndLevel::Render()
{
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);
	EndTitle->Render();
	WinnerTitle->Render();
	for (int i = 0; i < 2; i++) {
		OptArr[i]->Render();
	}
}

void EndLevel::ProcessLevel()
{
	if (Input::m_iSpecialKeyState[GLUT_KEY_UP] == INPUT_FIRST_PRESS || Input::m_iKeyState['w'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		OptArr[CurrentOpt]->ToggleActive();
		if (CurrentOpt == 0) {
			CurrentOpt = 1;
		}
		else CurrentOpt--;
		OptArr[CurrentOpt]->ToggleActive();
	}
	else if (Input::m_iSpecialKeyState[GLUT_KEY_DOWN] == INPUT_FIRST_PRESS || Input::m_iKeyState['s'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		OptArr[CurrentOpt]->ToggleActive();
		if (CurrentOpt == 1) {
			CurrentOpt = 0;
		}
		else CurrentOpt++;
		OptArr[CurrentOpt]->ToggleActive();
	}
	else if (Input::m_iKeyState['\r'] == INPUT_FIRST_PRESS || Input::m_iKeyState[32] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuClose();
		switch (CurrentOpt) {
		case 0: {
			SceneManager::GetInstance()->InitializeScene(LEVEL1_SCENE);
			SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);
			break;
		}
		case 1: {
			SceneManager::GetInstance()->InitializeScene(MENU_SCENE);
			SceneManager::GetInstance()->SetCurrentScene(MENU_SCENE);
		}
		default:break;
		}
	}
	Input::Update();
}

void EndLevel::SetWinner(unsigned int _WinningPlayer)
{
	if (_WinningPlayer == 0) {
		WinnerTitle->SetText("Player One Won!");
	}
	else {
		WinnerTitle->SetText("Player Two Won!");
	}
}
