#include "OptionsMenu.h"
#include "Sprite.h"
#include "Option.h"
#include "KeyboardInput.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TextLabel.h"

OptionsMenu::OptionsMenu()
{
	m_pBackground = std::make_shared<Sprite>();
	m_pOptionTitle = std::make_shared<TextLabel>("Options", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(665.0f, 750.0f));
	m_pEffectLevel = std::make_shared<TextLabel>("Effect level", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(665.0f, 750.0f));
	m_pBGMLevel = std::make_shared<TextLabel>("BGM level", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(665.0f, 750.0f));
	m_pOptionTitle->SetScale(1.6f);
	m_iCurrentOpt = 0;
}

OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::Init()
{
	m_pBackground->Initialize("Resources/Images/New Background.png");
	m_pOptionArr[0] = std::make_shared<Option>("Sound Effects Volume", glm::vec2(480.0f, 630.0f), glm::vec2(345.0f, 620.0f));
	m_pOptionArr[1] = std::make_shared<Option>("Background Music Volume", glm::vec2(425.0f, 450.0f), glm::vec2(300.0f, 440.0f));
	m_pOptionArr[2] = std::make_shared<Option>("Controls", glm::vec2(680.0f, 270.0f), glm::vec2(635.0f, 260.0f));
	m_pOptionArr[3] = std::make_shared<Option>("Main Menu", glm::vec2(680.0f, 125.0f), glm::vec2(620.0f, 140.0f));
	m_pOptionArr[0]->ToggleActive();
}

void OptionsMenu::Render()
{
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);
	m_pOptionTitle->Render();
	m_pEffectLevel->Render();
	m_pBGMLevel->Render();
	for (auto it : m_pOptionArr) {
		it->Render();
	}
}

void OptionsMenu::ProcessLevel()
{
	//Move option up
	if (Input::m_iSpecialKeyState[GLUT_KEY_UP] == INPUT_FIRST_PRESS || Input::m_iKeyState['w'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		m_pOptionArr[m_iCurrentOpt]->ToggleActive();
		if (m_iCurrentOpt == 0) {
			m_iCurrentOpt = 3;
		}
		else m_iCurrentOpt--;
		m_pOptionArr[m_iCurrentOpt]->ToggleActive();
	}

	//Move Option Down
	else if (Input::m_iSpecialKeyState[GLUT_KEY_DOWN] == INPUT_FIRST_PRESS || Input::m_iKeyState['s'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		m_pOptionArr[m_iCurrentOpt]->ToggleActive();
		if (m_iCurrentOpt == 3) {
			m_iCurrentOpt = 0;
		}
		else m_iCurrentOpt++;
		m_pOptionArr[m_iCurrentOpt]->ToggleActive();
	}

	//Left arrow
	else if (Input::m_iSpecialKeyState[GLUT_KEY_LEFT] == INPUT_FIRST_PRESS || Input::m_iKeyState['a'] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuMove();
		if (m_iCurrentOpt == 0) {
			if (SoundManager::GetInstance()->EffectScale >= 0.0f) {
				SoundManager::GetInstance()->EffectScale -= 0.1f;
			}
		}
		else if (m_iCurrentOpt == 1) {
			if (SoundManager::GetInstance()->BGMScale >= 0.0f) {
				SoundManager::GetInstance()->BGMScale -= 0.1f;
			}
		}
	}
	//Select option
	else if (Input::m_iKeyState['\r'] == INPUT_FIRST_PRESS || Input::m_iKeyState[32] == INPUT_FIRST_PRESS) {
		SoundManager::GetInstance()->SoundMenuClose();
		switch (m_iCurrentOpt) {
		case 0: {
			SoundManager::GetInstance()->StopBGM();
			SceneManager::GetInstance()->SetTransitioning(true);
			break;
		}
		case 2: {
			glutLeaveMainLoop();
		}
		default:break;
		}
	}
	Input::Update();
}
