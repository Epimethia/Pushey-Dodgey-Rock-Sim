#ifndef __LEVELONE_H__
#define __LEVELONE_H__
//	Library includes.


//	Local includes.
#include "Utilities.h"
#include "XboxControllerInput.h"


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

	void Init();
	void RenderObjects();
	void ProcessLevel(const float& _DeltaTick);
	void ProcessTimer(const float& _DeltaTick);
	void SpawnAsteroids(const float& _DeltaTick);
	void OffscreenCleanup();
	void MoveAsteroids(const float& _DeltaTick);
	void CheckPlayerDeaths(const float& _DeltaTick);
	void UpdateScoreValues();
	void ProcessPlayerInput(const float& _DeltaTick);

private:		
	std::vector<std::shared_ptr<Asteroid>> m_vpAsteroidVec0;
	std::vector<std::shared_ptr<Asteroid>> m_vpAsteroidVec1;
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

	short m_fTimeRemaining;
	float m_fTimerTick;

	std::shared_ptr<Sprite> m_pHUDFrame;

	std::shared_ptr<Sprite> m_pPointsSpriteArr[2];
	std::shared_ptr<Sprite> m_pPOne_OnePoint;
	std::shared_ptr<Sprite> m_pPTwo_OnePoint;
	std::shared_ptr<Sprite> m_pTwoPoints;
	std::shared_ptr<Sprite> m_pZeroPoints;


	std::shared_ptr<TextLabel> m_pTimeDisplay;


};

#endif