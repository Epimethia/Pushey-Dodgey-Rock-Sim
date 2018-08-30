#pragma once
//	Library includes.


//	Local includes.
#include "Entity.h"
#include "Utilities.h"


class Sprite;
class PlayerCharacter :
	public Entity
{
public:
	PlayerCharacter(glm::vec2 _spawnPosition);
	~PlayerCharacter();
	

	// Virtual Functions
	void Render();
	void Update();
	void AddVelocity(float _Speed);
	void AddRotation(float _Angle);
	void SetPosition(b2Vec2 _position);
	void ResetPosition();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	float GetVibrateRate() { return m_fVibrationRate; };	
	float GetHealth() {	return m_fHealthPoints; }
	void PlayerDied();
	void Initialize();


private:	
	float m_fVibrationRate;	
	glm::vec2 m_SpawnPos;	
	float m_fHealthPoints;
};

