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
	m_pBackground->Initialize("Resources/Images/MenuBackground2.png");

	m_pMenuTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 800.0f));
	m_pMenuTitle->SetScale(1.6f);

	//creating the buttons
	m_pOptionArr[0] = std::make_shared<Option>("Play", glm::vec2(715.0f, 620.0f), glm::vec2(690.0f, 610.0f));
	m_pOptionArr[1] = std::make_shared<Option>("Option", glm::vec2(680.0f, 430.0f), glm::vec2(640.0f, 420.0f));
	m_pOptionArr[2] = std::make_shared<Option>("Quit", glm::vec2(715.0f, 240.0f), glm::vec2(690.0f, 230.0f));
	m_pOptionArr[0]->ToggleActive();

	//starting up the BGM
	SoundManager::GetInstance()->StartMenuBGM();
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
		if (INPUT_FIRST_PRESS == Input::m_iSpecialKeyState[GLUT_KEY_UP] || INPUT_FIRST_PRESS == Input::m_iKeyState['w'])
		{
			SoundManager::GetInstance()->SoundMenuMove();
			m_pOptionArr[m_iCurrentOpt]->ToggleActive();
			if (m_iCurrentOpt == 0) {
				m_iCurrentOpt = 2;
			}
			else m_iCurrentOpt--;
			m_pOptionArr[m_iCurrentOpt]->ToggleActive();
		}
		else if (INPUT_FIRST_PRESS == Input::m_iSpecialKeyState[GLUT_KEY_DOWN] || INPUT_FIRST_PRESS == Input::m_iKeyState['s'])
		{
			SoundManager::GetInstance()->SoundMenuMove();
			m_pOptionArr[m_iCurrentOpt]->ToggleActive();
			if (m_iCurrentOpt == 2) {
				m_iCurrentOpt = 0;
			}
			else m_iCurrentOpt++;
			m_pOptionArr[m_iCurrentOpt]->ToggleActive();
		}
		else if (INPUT_FIRST_PRESS == Input::m_iKeyState['\r'] || INPUT_FIRST_PRESS == Input::m_iKeyState[32])
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
			case 2:
			{
				glutLeaveMainLoop();
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
				
				SceneManager::GetInstance()->RestartLevelOne();
				SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);					
			}
		}
	}
	Input::Update();
}

