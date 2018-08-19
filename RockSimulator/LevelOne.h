#pragma once
#include "Utilities.h"
#include "XboxControllerInput.h"
#include "Dependencies\Box2D\Box2D.h"

class Entity;
class PlayerCharacter;
class Camera;
class Sprite;
class Input;
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
	std::vector<std::shared_ptr<Entity>> m_EntityVec;
	std::shared_ptr<PlayerCharacter> m_PlayerOne;
	std::shared_ptr<PlayerCharacter> m_PlayerTwo;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;

	//BOOTLEGGING CONTROLLER INPUT RIGHT NOW -- CHANGE

	std::vector<std::shared_ptr<XBOXController>> CurrentPlayers;

	// Physics Shit - jasper
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	b2World world = b2World(gravity);
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
};

