#pragma once
#include <vector>
#include <memory>


enum SceneState
{
	MENU_SCENE,
	LEVEL1_SCENE
};

//Forward Declarations
class LevelOne;
class Input;
class CClock;

class SceneManager
{
#pragma region Singleton
public:
	static std::shared_ptr<SceneManager> GetInstance();
	static void DestroyInstance();
	~SceneManager();
private:
	static std::shared_ptr<SceneManager> s_pSceneManager;
	SceneManager(SceneManager const&);
	void operator=(SceneManager const&);
	SceneManager();
#pragma endregion

public:
	void SetCurrentScene(SceneState);	
	void InitializeScene(SceneState);
	void RenderCurrentScene();
	void UpdateCurrentScene();

private:
	SceneState m_CurrentScene;		
	std::shared_ptr<LevelOne> m_LevelOneScene;
	//CClock singleton reference
	std::shared_ptr<CClock> m_Clock;
};

