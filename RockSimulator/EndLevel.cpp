#include "EndLevel.h"
#include "Sprite.h"
#include "KeyboardInput.h"
#include "Camera.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Option.h"
#include "clock.h"

EndLevel::EndLevel()
{
	m_pBackground = std::make_shared<Sprite>();
	m_iCurrentOpt = 0;
	m_iWinner = -1;
}

EndLevel::~EndLevel()
{
	for (auto& it : m_pOptArr) {
		it.reset();
	}
	m_pBackground.reset();
}

void EndLevel::Init()
{
	m_pBackground->Initialize("Resources/Images/EndBackground.png");
	m_pEndTitle = std::make_shared<TextLabel>("Pushy Dodgy Rock Simulator", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 800.0f));
	m_pEndTitle->SetScale(1.6f);	
	
	m_pWinnerTitle = std::make_shared<TextLabel>("<Winning Player>", "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", glm::vec2(165.0f, 600.0f));
	m_pWinnerTitle->SetScale(1.6f);


	m_pOptArr[0] = std::make_shared<Option>("Play Again", glm::vec2(630.0f, 430.0f), glm::vec2(565.0f, 420.0f));
	m_pOptArr[1] = std::make_shared<Option>("Main Menu", glm::vec2(630.0f, 240.0f), glm::vec2(590.0f, 230.0f));
	m_pOptArr[0]->ToggleActive();
}

void EndLevel::Render()
{
	m_pBackground->Render(
		glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *
		glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))
	);
	m_pEndTitle->Render();
	m_pWinnerTitle->Render();
	for (int i = 0; i < 2; i++) {
		m_pOptArr[i]->Render();
	}
}

void EndLevel::ProcessLevel()
{
	if (!SceneManager::GetInstance()->GetState())
	{
		if (Input::m_iSpecialKeyState[GLUT_KEY_UP] == INPUT_FIRST_PRESS || Input::m_iKeyState['w'] == INPUT_FIRST_PRESS) {
			SoundManager::GetInstance()->SoundMenuMove();
			m_pOptArr[m_iCurrentOpt]->ToggleActive();
			if (m_iCurrentOpt == 0) {
				m_iCurrentOpt = 1;
			}
			else m_iCurrentOpt--;
			m_pOptArr[m_iCurrentOpt]->ToggleActive();
		}
		else if (Input::m_iSpecialKeyState[GLUT_KEY_DOWN] == INPUT_FIRST_PRESS || Input::m_iKeyState['s'] == INPUT_FIRST_PRESS) {
			SoundManager::GetInstance()->SoundMenuMove();
			m_pOptArr[m_iCurrentOpt]->ToggleActive();
			if (m_iCurrentOpt == 1) {
				m_iCurrentOpt = 0;
			}
			else m_iCurrentOpt++;
			m_pOptArr[m_iCurrentOpt]->ToggleActive();
		}
		else if (Input::m_iKeyState['\r'] == INPUT_FIRST_PRESS || Input::m_iKeyState[32] == INPUT_FIRST_PRESS) {
			SoundManager::GetInstance()->SoundMenuClose();
			switch (m_iCurrentOpt) {
			case 0: {
				SceneManager::GetInstance()->SetTransitioning(true);
				m_iWinner = -1; // reset winner
				break;
			}
			case 1: {				
				SceneManager::GetInstance()->SetTransitioning(true);
				m_iWinner = -1; // reset winner
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
			if (fSceneOpacity > 0.0f)
			{
				SceneManager::GetInstance()->SetOpacity(fSceneOpacity - (CClock::GetInstance()->GetDeltaTick() / 1000));
			}
			else
			{				
				SceneManager::GetInstance()->SetOpacity(1.0f);
				SceneManager::GetInstance()->SetTransitioning(false);

				switch (m_iCurrentOpt) {
				case 0: {
					SceneManager::GetInstance()->RestartLevelOne();
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
		}		
	}

	Input::Update();
}

void EndLevel::SetWinner(unsigned int _WinningPlayer)
{
	m_iWinner = _WinningPlayer;
	if (_WinningPlayer == 0) {
		m_pWinnerTitle->SetText("Player One Won!");
	}
	else if (_WinningPlayer == 1) {
		m_pWinnerTitle->SetText("Player Two Won!");
	}
}

unsigned int EndLevel::GetWinner()
{
	return m_iWinner;
}
