#include "MenuLevel.h"
#include "TextLabel.h"
#include "Sprite.h"
#include "KeyboardInput.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Option.h"
#include "clock.h"



MainMenu::MainMenu()
{
	m_pBackground = std::make_shared<Sprite>();

	m_iCurrentOpt = 0;
	m_pBackground->Initialize("Resources/Images/MenuBackground.png");

	m_pMenuTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 800.0f));
	m_pMenuTitle->SetScale(1.6f);

	//creating the buttons
	m_pOptionArr[0] = std::make_shared<Option>("Play", glm::vec2(715.0f, 620.0f), glm::vec2(690.0f, 610.0f));
	m_pOptionArr[1] = std::make_shared<Option>("Option", glm::vec2(680.0f, 430.0f), glm::vec2(640.0f, 420.0f));
	m_pOptionArr[2] = std::make_shared<Option>("Quit", glm::vec2(715.0f, 240.0f), glm::vec2(690.0f, 230.0f));

	m_pPlayerOneController = std::make_shared<XBOXController>(1);
}

MainMenu::~MainMenu()
{
	for (auto& it : m_pOptionArr)
	{
		it.reset();
	}
	m_pMenuTitle.reset();
	//m_pBackground.reset();
}

void MainMenu::Init()
{
	for (auto it : m_pOptionArr) {
		if (it->m_bSelected) {
			it->ToggleActive();
		}
	}
	m_pOptionArr[0]->ToggleActive();
	m_iCurrentOpt = 0;
}

void MainMenu::Render()
{
	
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);

	m_pMenuTitle->Render();

	//rendering option buttons
	for (int i = 0; i < 3; i++) {
		m_pOptionArr[i]->Render();
	}
}

void MainMenu::ProcessLevel()
{
	//Handling key input for the menu
	if (!SceneManager::GetInstance()->GetState())
	{
		if (INPUT_FIRST_PRESS == Input::m_iSpecialKeyState[GLUT_KEY_UP] || INPUT_FIRST_PRESS == Input::m_iKeyState['w'] || 0.6f < m_pPlayerOneController->normalizedLY)
		{
			if (m_bControllerMoved == false) {
				SoundManager::GetInstance()->SoundMenuMove();
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				if (m_iCurrentOpt == 0) {
					m_iCurrentOpt = 2;
				}
				else m_iCurrentOpt--;
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				m_bControllerMoved = true;
			}
			
		}
		else if (INPUT_FIRST_PRESS == Input::m_iSpecialKeyState[GLUT_KEY_DOWN] || INPUT_FIRST_PRESS == Input::m_iKeyState['s'] || -0.6f > m_pPlayerOneController->normalizedLY)
		{
			if (m_bControllerMoved == false) {
				SoundManager::GetInstance()->SoundMenuMove();
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				if (m_iCurrentOpt == 2) {
					m_iCurrentOpt = 0;
				}
				else m_iCurrentOpt++;
				m_pOptionArr[m_iCurrentOpt]->ToggleActive();
				m_bControllerMoved = true;
			}
			
		}
		else if (INPUT_FIRST_PRESS == Input::m_iKeyState['\r'] || INPUT_FIRST_PRESS == Input::m_iKeyState[32] || INPUT_FIRST_PRESS == m_pPlayerOneController->ControllerButtons[BOTTOM_FACE_BUTTON])
		{
			SoundManager::GetInstance()->SoundMenuClose();
			switch (m_iCurrentOpt)
			{
			case 0:
			{
				SoundManager::GetInstance()->StopBGM();
				SceneManager::GetInstance()->SetTransitioning(true);
				break;
			}
			case 1:
			{
				SceneManager::GetInstance()->SetTransitioning(true);
				SceneManager::GetInstance()->InitializeScene(OPTION_SCENE);
				break;
			}
			case 2:
			{
				glutLeaveMainLoop();
				break;
			}
			default:break;
			}
		}
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
				if (m_iCurrentOpt == 0) {
					SceneManager::GetInstance()->RestartLevelOne();
					SceneManager::GetInstance()->InitializeScene(LEVEL1_SCENE);
					SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);
					SoundManager::GetInstance()->StartLevelBGM();
				}
				else {
					//SceneManager::GetInstance()->RestartLevelOne();
					SceneManager::GetInstance()->SetCurrentScene(OPTION_SCENE);
				}
								
			}
		}
	}
	Input::Update();
	if (m_pPlayerOneController->normalizedLY < 0.5f && m_pPlayerOneController->normalizedLY > -0.5f) {
		m_bControllerMoved = false;
	}
	m_pPlayerOneController->Update();
}

