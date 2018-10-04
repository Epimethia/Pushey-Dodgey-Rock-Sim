#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
//	Library includes.
#include <vector>
#include <memory>


//	Local includes.


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
public:
	static std::shared_ptr<SceneManager> GetInstance();
	static void DestroyInstance();
	SceneManager();
	~SceneManager();

	void SetCurrentScene(SceneState);	
	void InitializeScene(SceneState);
	void RenderCurrentScene();
	void UpdateCurrentScene();
	void SetWinner(unsigned int _WinningPlayer);

private:
	static std::shared_ptr<SceneManager> s_pInstance;
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;


	SceneState m_eCurrentScene;		
	std::shared_ptr<LevelOne> m_pLevelOneScene;
	std::shared_ptr<MainMenu> m_pMenuLevelScene;
	std::shared_ptr<EndLevel> m_pEndLevelScene;
	std::shared_ptr<CClock> m_pClock;
};

#endif