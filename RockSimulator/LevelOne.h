#pragma once
#include "Utilities.h"

class Entity;
class PlayerCharacter;
class Camera;
class Sprite;
class LevelOne	
{
public:
	LevelOne();
	~LevelOne();

	void InitializeObjects();
	void RenderObjects();

private:
	std::vector<std::shared_ptr<PlayerCharacter>> m_PlayerVec;
	std::vector<std::shared_ptr<Entity>> m_EntityVec;
	std::shared_ptr<PlayerCharacter> m_PlayerOne;
	std::shared_ptr<PlayerCharacter> m_PlayerTwo;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;
};

