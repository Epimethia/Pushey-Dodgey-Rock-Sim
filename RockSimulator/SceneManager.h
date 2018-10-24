#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
//	Library includes.
#include <vector>
#include <memory>


//	Local includes.


enum SceneState
{
	MENU_SCENE,
	OPTION_SCENE,
	LEVEL1_SCENE,
	END_SCENE
};

//Forward Declarations
class MainMenu;
class OptionsMenu;
class LevelOne;
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
	void RestartLevelOne();
	void SetWinner(unsigned int _WinningPlayer);		
	bool GetState() { return m_bTransitioning; }
	void SetOpacity(float _opacity) { m_fOpacity = _opacity; }
	float GetOpacity() { return m_fOpacity; }
	void SetTransitioning(bool _state) { m_bTransitioning = _state; }

private:
	static std::shared_ptr<SceneManager> s_pInstance;
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;


	SceneState m_eCurrentScene;		
	std::shared_ptr<LevelOne> m_pLevelOneScene;
	std::shared_ptr<MainMenu> m_pMenuLevelScene;
	std::shared_ptr<OptionsMenu> m_pOptionLevelScene;
	std::shared_ptr<EndLevel> m_pEndLevelScene;

	std::shared_ptr<CClock> m_pClock;

	// Scene transition stuff
	bool m_bTransitioning{ false };
	float m_fOpacity{ 1.0f };
};

#endif