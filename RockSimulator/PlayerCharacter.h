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
	void SetPosition(b2Vec2 _position);
	float GetVibrateRate() { return m_fVibrationRate; };	
	void Initialize();

private:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Scale;	
	glm::vec3 m_RotationAxis;
	float m_fVibrationRate;

	// Physics
	b2BodyDef m_bodyDef;
	b2Body* m_body;		
};

