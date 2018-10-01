#include "SceneManager.h"
#include "LevelOne.h"
#include "Sprite.h"
#include "clock.h"
#include "MenuLevel.h"


std::shared_ptr<SceneManager> SceneManager::s_pSceneManager;

std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
	if (!s_pSceneManager)
	{
		s_pSceneManager = std::shared_ptr<SceneManager>(new SceneManager());
	}
	return s_pSceneManager;
}

void SceneManager::DestroyInstance()
{
	s_pSceneManager.reset();
	//s_pSceneManager = nullptr;
}

SceneManager::SceneManager()
{
	m_pLevelOneScene = std::make_shared<LevelOne>();
	m_pMenuLevel = std::make_shared<MainMenu>();

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
	switch (m_iCurrentScene)
	{
	case MENU_SCENE:
	{
		m_pMenuLevel->Render();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_pLevelOneScene->RenderObjects();
		break;
	}
	}
}

void SceneManager::UpdateCurrentScene()
{
	m_pClock->Process();
	float fDeltaTick = m_pClock->GetDeltaTick() / 1000.0f;
	switch (m_iCurrentScene) {
	case MENU_SCENE:
	{
		m_pMenuLevel->Process();
		break;
	}
	case LEVEL1_SCENE: 
	{
		m_pLevelOneScene->ProcessLevel(fDeltaTick);
		break;
	}
	default:break;
	}
}

void SceneManager::SetCurrentScene(SceneState _scene)
{
	m_iCurrentScene = _scene;
}

void SceneManager::InitializeScene(SceneState _scene)
{
	// Create the objects for the specified scene
	switch (_scene)
	{
	case MENU_SCENE:
	{
		m_pMenuLevel->Init();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_pLevelOneScene->InitializeObjects();
		break;
	}
	}	
}
