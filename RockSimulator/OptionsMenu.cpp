#include "OptionsMenu.h"
#include "Sprite.h"
#include "Option.h"
#include "KeyboardInput.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TextLabel.h"
#include "clock.h"

OptionsMenu::OptionsMenu()
{
	m_pBackground = std::make_shared<Sprite>();
	m_pBackground->Initialize("Resources/Images/New Background.png");

	m_pOptionTitle = std::make_shared<TextLabel>("Options", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(665.0f, 750.0f));
	m_pEffectLevel = std::make_shared<TextLabel>("Effect level", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(710.0f, 550.0f));
	m_pEffectLevel->SetScale(1.3f);
	m_pBGMLevel = std::make_shared<TextLabel>("BGM level", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(710.0f, 350.0f));
	m_pBGMLevel->SetScale(1.3f);
	m_pOptionTitle->SetScale(1.6f);
	m_iCurrentOpt = 0;

	m_pControlsTutorial = std::make_shared<Sprite>();
	m_pControlsTutorial->Initialize("Resources/Images/Controls.png");

	m_pOptionArr[0] = std::make_shared<Option>("Sound Effects Volume", glm::vec2(480.0f, 630.0f), glm::vec2(345.0f, 620.0f));
	m_pOptionArr[1] = std::make_shared<Option>("Background Music Volume", glm::vec2(425.0f, 450.0f), glm::vec2(300.0f, 440.0f));
	m_pOptionArr[2] = std::make_shared<Option>("Controls", glm::vec2(680.0f, 270.0f), glm::vec2(635.0f, 260.0f));
	m_pOptionArr[3] = std::make_shared<Option>("Main Menu", glm::vec2(680.0f, 125.0f), glm::vec2(620.0f, 140.0f));

	m_pPlayerOneController = std::make_shared<XBOXController>(1);

	m_pEffectLevel->SetText(std::string("-- " + std::to_string(static_cast<int>(SoundManager::GetInstance()->EffectScale * 10.0f)) + " --").c_str());
	m_pBGMLevel->SetText(std::string("-- " + std::to_string(static_cast<int>(SoundManager::GetInstance()->BGMScale * 10.0f)) + " --").c_str());
}

OptionsMenu::~OptionsMenu()
{
	m_pBackground.reset();
	m_pOptionTitle.reset();
	m_pEffectLevel.reset();
	m_pBGMLevel.reset();
}

void OptionsMenu::Init()
{
	for (auto it : m_pOptionArr) {
		if (it->m_bSelected) {
			it->ToggleActive();
		}
	}
	m_pOptionArr[0]->ToggleActive();
	m_iCurrentOpt = 0;
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
	if (m_bViewingTutorial) {
		m_pControlsTutorial->Render(
			glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
			glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
		);
	}
}

void OptionsMenu::ProcessLevel()
{
	if (!SceneManager::GetInstance()->GetState())
	{
		//Left arrow
		if (Input::m_iSpecialKeyState[GLUT_KEY_LEFT] == INPUT_FIRST_PRESS || Input::m_iKeyState['a'] == INPUT_FIRST_PRESS || -0.6f > m_pPlayerOneController->normalizedLX) {
			if (m_bControllerMoved == false) {
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
				m_bControllerMoved = true;
			}
		}
		//Right arrow
		else if (Input::m_iSpecialKeyState[GLUT_KEY_RIGHT] == INPUT_FIRST_PRESS || Input::m_iKeyState['d'] == INPUT_FIRST_PRESS || 0.6f < m_pPlayerOneController->normalizedLX) {
			if (m_bControllerMoved == false) {
				SoundManager::GetInstance()->SoundMenuMove();
				if (m_iCurrentOpt == 0) {
					if (SoundManager::GetInstance()->EffectScale <= 0.9f) {
						SoundManager::GetInstance()->EffectScale += 0.1f;
					}
				}
				else if (m_iCurrentOpt == 1) {
					if (SoundManager::GetInstance()->BGMScale <= 0.9f) {
						SoundManager::GetInstance()->BGMScale += 0.1f;
					}
				}
				m_bControllerMoved = true;
			}

		}
		//Move option up
		else if (Input::m_iSpecialKeyState[GLUT_KEY_UP] == INPUT_FIRST_PRESS || Input::m_iKeyState['w'] == INPUT_FIRST_PRESS || 0.6f < m_pPlayerOneController->normalizedLY) {
			if (m_bControllerMoved == false) {
				SoundManager::GetInstance()->SoundMenuMove();
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				if (m_iCurrentOpt == 0) {
					m_iCurrentOpt = 3;
				}
				else m_iCurrentOpt--;
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				m_bControllerMoved = true;
			}
			
		}

		//Move Option Down
		else if (Input::m_iSpecialKeyState[GLUT_KEY_DOWN] == INPUT_FIRST_PRESS || Input::m_iKeyState['s'] == INPUT_FIRST_PRESS || -0.6f > m_pPlayerOneController->normalizedLY) {
			if (m_bControllerMoved == false) {
				SoundManager::GetInstance()->SoundMenuMove();
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				if (m_iCurrentOpt == 3) {
					m_iCurrentOpt = 0;
				}
				else m_iCurrentOpt++;
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				m_bControllerMoved = true;
			}
		}

		//Select option
		else if (Input::m_iKeyState['\r'] == INPUT_FIRST_PRESS || Input::m_iKeyState[32] == INPUT_FIRST_PRESS || INPUT_FIRST_PRESS == m_pPlayerOneController->ControllerButtons[BOTTOM_FACE_BUTTON]) {
			SoundManager::GetInstance()->SoundMenuClose();
			switch (m_iCurrentOpt) {
			case 2: {
				
				m_bViewingTutorial = !m_bViewingTutorial;
				break;
			}
			case 3: {
				SceneManager::GetInstance()->SetTransitioning(true);
				break;
			}
			default:break;
			}
		}
		Input::Update();
		m_pEffectLevel->SetText(std::string("-- " + std::to_string(static_cast<int>(SoundManager::GetInstance()->EffectScale * 10.0f)) + " --").c_str());
		m_pBGMLevel->SetText(std::string("-- " + std::to_string(static_cast<int>(SoundManager::GetInstance()->BGMScale * 10.0f)) + " --").c_str());
		if ((m_pPlayerOneController->normalizedLY < 0.5f && m_pPlayerOneController->normalizedLY > -0.5f) &&
			m_pPlayerOneController->normalizedLX < 0.5f && m_pPlayerOneController->normalizedLX > -0.5f) {
			m_bControllerMoved = false;
		}
		m_pPlayerOneController->Update();
	}
	else
	{
		// Scene Transition
		if (SceneManager::GetInstance()->GetState())
		{
			// Fade out 
			float fSceneOpacity = SceneManager::GetInstance()->GetOpacity();
			if (0.0f < fSceneOpacity)
			{
				SceneManager::GetInstance()->SetOpacity(fSceneOpacity - (CClock::GetInstance()->GetDeltaTick() / 1000));
			}
			else
			{
				SceneManager::GetInstance()->SetOpacity(1.0f);
				SceneManager::GetInstance()->SetTransitioning(false);
				SceneManager::GetInstance()->InitializeScene(MENU_SCENE);
				SceneManager::GetInstance()->SetCurrentScene(MENU_SCENE);
			}
		}
	}
}
