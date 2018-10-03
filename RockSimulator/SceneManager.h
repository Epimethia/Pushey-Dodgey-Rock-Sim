#pragma once
#include <vector>
#include <memory>


enum SceneState
{
	MENU_SCENE,
	LEVEL1_SCENE,
	END_SCENE
};

//Forward Declarations
class LevelOne;
class MainMenu;
class EndLevel;
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
	void operator=(SceneManager const&) {};
	SceneManager();
#pragma endregion

public:
	void SetCurrentScene(SceneState);	
	void InitializeScene(SceneState);
	void RenderCurrentScene();
	void UpdateCurrentScene();
	void SetWinner(unsigned int _WinningPlayer);

private:
	SceneState m_iCurrentScene;		
	std::shared_ptr<LevelOne> m_pLevelOneScene;
	std::shared_ptr<MainMenu> m_pMenuLevelScene;
	std::shared_ptr<EndLevel> m_pEndLevelScene;
	//CClock singleton reference
	std::shared_ptr<CClock> m_pClock;
};

