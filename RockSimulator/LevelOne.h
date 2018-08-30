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


class LevelOne	
{
public:
	LevelOne();
	~LevelOne();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);

private:
	std::vector<std::shared_ptr<PlayerCharacter>> m_PlayerVec;
	std::vector<std::shared_ptr<Asteroid>> m_AsteroidVec;
	std::vector<std::shared_ptr<Entity>> m_EntityVec;
	std::shared_ptr<PlayerCharacter> m_PlayerOne;
	std::shared_ptr<PlayerCharacter> m_PlayerTwo;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;
	MyContactListener* m_pContactListener;
	float m_SpawnTime;


	//BOOTLEGGING CONTROLLER INPUT RIGHT NOW -- CHANGE

	std::vector<std::shared_ptr<XBOXController>> CurrentPlayers;
	
};

