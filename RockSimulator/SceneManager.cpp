#include "SceneManager.h"
#include "LevelOne.h"
#include "Sprite.h"

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
	m_LevelOneScene = std::make_shared<LevelOne>();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RenderCurrentScene()
{
	switch (m_CurrentScene)
	{
	case MENU_SCENE:
	{

		break;
	}
	case LEVEL1_SCENE:
	{
		m_LevelOneScene->RenderObjects();
		break;
	}
	}
}

void SceneManager::UpdateCurrentScene()
{
}

void SceneManager::SetCurrentScene(SceneState _scene)
{
	m_CurrentScene = _scene;
}

void SceneManager::InitializeScene(SceneState _scene)
{
	// Create the objects for the specified scene
	switch (_scene)
	{
	case MENU_SCENE:
	{

		break;
	}
	case LEVEL1_SCENE:
	{
		m_LevelOneScene->InitializeObjects();
		break;
	}
	}	
}
