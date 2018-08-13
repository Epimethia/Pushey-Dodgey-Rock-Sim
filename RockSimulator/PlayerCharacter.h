#pragma once
#include "Entity.h"
#include "Utilities.h"

class Sprite;
class PlayerCharacter :
	public Entity
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	// Virtual Functions
	void Render();
	void Update();
	void Initialize();

private:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Translate;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;
	float m_fRotation;
};

