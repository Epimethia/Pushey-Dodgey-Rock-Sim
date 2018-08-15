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
	void AddVelocity(float _Speed);
	void AddRotation(float _Angle);
	void Brake();

	void Initialize();

private:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Translate;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;

	glm::vec3 m_Velocity;
	glm::vec3 m_ForwardVector;

	float m_fMaxSpeed = 5.0f;
	float m_fRotation;
};

