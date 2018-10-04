#include "SceneManager.h"
#include "LevelOne.h"
#include "Sprite.h"
#include "clock.h"
#include "MenuLevel.h"
#include "EndLevel.h"


std::shared_ptr<SceneManager> SceneManager::s_pInstance;

std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = std::shared_ptr<SceneManager>(new SceneManager());
	}
	return s_pInstance;
}

void SceneManager::DestroyInstance()
{
	s_pInstance.reset();
	//s_pSceneManager = nullptr;
}

SceneManager::SceneManager()
{
	m_pLevelOneScene = std::make_shared<LevelOne>();
	m_pMenuLevelScene = std::make_shared<MainMenu>();
	m_pEndLevelScene = std::make_shared<EndLevel>();

	//Initializing the input manager
	Input::GetInstance()->Initialize();
	m_pClock = CClock::GetInstance();
	m_pClock->Initialise();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RenderCurrentScene()
{
	switch (m_eCurrentScene)
	{
	case MENU_SCENE:
	{
		m_pMenuLevelScene->Render();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_pLevelOneScene->RenderObjects();
		break;
	}
	case END_SCENE: {
		m_pEndLevelScene->Render();
		break;
	}
	default:break;
	}
}

void SceneManager::UpdateCurrentScene()
{
	m_pClock->Process();
	float fDeltaTick = m_pClock->GetDeltaTick() / 1000.0f;
	switch (m_eCurrentScene) {
	case MENU_SCENE:
	{
		m_pMenuLevelScene->ProcessLevel();
		break;
	}
	case LEVEL1_SCENE: 
	{
		m_pLevelOneScene->ProcessLevel(fDeltaTick);
		break;
	}
	case END_SCENE: {
		m_pEndLevelScene->ProcessLevel();
	}
	default:break;
	}
	
}

void SceneManager::RestartLevelOne()
{
	m_pLevelOneScene.reset();
	m_pLevelOneScene = std::make_shared<LevelOne>();
	m_pLevelOneScene->InitializeObjects();

}

void SceneManager::SetWinner(unsigned int _WinningPlayer)
{
	m_pEndLevelScene->SetWinner(_WinningPlayer);
}

void SceneManager::SetCurrentScene(SceneState _scene)
{
	m_eCurrentScene = _scene;
}

void SceneManager::InitializeScene(SceneState _scene)
{
	// Create the objects for the specified scene
	switch (_scene)
	{
		case MENU_SCENE:
		{
			m_pMenuLevelScene->Init();
			break;
		}
		case LEVEL1_SCENE:
		{
			m_pLevelOneScene->InitializeObjects();
			break;
		}
		case END_SCENE: {
			m_pEndLevelScene->Init();
		}
	default:break;
	}	
}
