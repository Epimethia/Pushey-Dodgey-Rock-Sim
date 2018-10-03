#pragma once
//	Library includes.
#include "Utilities.h"
#include "XboxControllerInput.h"


//	Local includes.


//	Class prototypes.
class Asteroid;
class Entity;
class PlayerCharacter;
class Camera;
class Sprite;
class Input;
class MyContactListener;
class CClock;
class TextLabel;
class C_HealthBar;


class LevelOne	
{
public:
	LevelOne();
	~LevelOne();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);
	void SpawnAsteroids(float _DeltaTick);
	void OffscreenCleanup();
	void MoveAsteroids(float _DeltaTick);
	void CheckPlayerDeaths();
	void ProcessPlayerInput(float _DeltaTick);

private:		
	std::vector<std::shared_ptr<Asteroid>> m_vpAsteroidVec;
	std::vector<std::shared_ptr<Entity>> m_vpEntityVec;
	std::shared_ptr<PlayerCharacter> m_pPlayerOne;
	std::shared_ptr<PlayerCharacter> m_pPlayerTwo;
	std::shared_ptr<C_HealthBar> m_pP1HealthBar;
	std::shared_ptr<C_HealthBar> m_pP2HealthBar;
	std::shared_ptr<XBOXController> m_pPlayerOneController;
	std::shared_ptr<XBOXController> m_pPlayerTwoController;
	std::shared_ptr<Sprite> m_pBackground;
	std::shared_ptr<Camera> m_pCamera;
	MyContactListener* m_pContactListener;
	float m_fSpawnTime;	
	CClock* m_pClock{ nullptr };
	short m_sDeathCount[2]{ 0, 0 };
	float m_fTimer{ 94.0f };	
	std::shared_ptr<TextLabel> m_P1Score;
	std::shared_ptr<TextLabel> m_P2Score;
	short m_sRoundCounter{ 1 };

};

